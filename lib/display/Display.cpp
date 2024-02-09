
#include "Display.h"
using namespace ftxui;
Display::Display(std::vector<std::string> names, int days_stored_, size_t frequency_)
    : days_stored(days_stored_)
    , frequency(frequency_)
    , amount_of_cities(names.size())
{
    cities = new City* [amount_of_cities];
    for (int i = 0; i < amount_of_cities; ++i) {
        cities[i] = new City(names[i], days_stored);
    }
    part_of_day[0] = "Noon";
    part_of_day[1] = "Morning";
    part_of_day[2] = "Mid Day";
    part_of_day[3] = "Evening";
}

Display::~Display() {
    for (int i = 0; i < amount_of_cities; ++i) {
        delete cities[i];
    }
    delete[] cities;
}

auto Display::GenerateDayCard(Day* day, int index, bool is_cur_day = false) {
    if (is_cur_day) {
        return vbox({
                            text("Temperature: " + day->GetTemperature(index)) | center,
                            text("Humidity: " + day->GetHumidity(index)) | center,
                            text("Weather: " + day->GetWeather(index)) | center,
                            text("Wind: " + day->GetWind(index)) | center
                    }) | border;
    }
    return vbox({
        text(part_of_day[index]) | center | bold | border,
        text("Temperature: " + day->GetTemperature(index)) | center,
        text("Humidity: " + day->GetHumidity(index)) | center,
        text("Weather: " + day->GetWeather(index)) | center,
        text("Wind: " + day->GetWind(index)) | center
    }) | border;
}

auto Display::DrawCityScreen() {
    Elements widgets;
    Day* cur_day = cities[current_city]->GetCurDay();
    widgets.push_back(text("Current weather in " + cities[current_city]->GetName() + " is(" + cur_day->GetData() +  "): " ) | bold | center);

    widgets.push_back(GenerateDayCard(cur_day, 0, true));
    for (int i = 0; i < days_stored; ++i) {
        Elements hbox_widgets;
        Day* day = cities[current_city]->GetDay(i);
        for (int j = 0; j < kDaysParts; ++j) {
            hbox_widgets.push_back(GenerateDayCard(day, j) | flex);
        }
        widgets.push_back(text(day->GetData()) | bold | center);
        widgets.push_back(hbox(hbox_widgets));
    }
    return vbox(widgets);
}

void Display::DrawScreen() {
    auto screen = ScreenInteractive::TerminalOutput();
    auto renderer = Renderer([&] {
        ClearScreen();
        return DrawCityScreen();
    });
    renderer |= CatchEvent([&] (const Event& event) {
        std::string cc = event.input();
        if (event == Event::Escape) {
            screen.ExitLoopClosure()();
        }
        if (cc == "p") {
            if (current_city - 1 > -1) {
                current_city -= 1;
                cities[current_city]->GetTemperature();
            }
        }
        if (cc == "n") {
            if (current_city + 1 < amount_of_cities) {
                current_city += 1;
                cities[current_city]->GetTemperature();
            }
        }

        return false;
    });
    Loop loop (&screen, renderer);
    auto start_time = std::chrono::system_clock::now();
    cities[current_city]->GetTemperature();

    while (!loop.HasQuitted()) {
        auto cur_time = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(cur_time - start_time).count() > frequency) {
            start_time = cur_time;
            cities[current_city]->GetTemperature();
            screen.Post(ftxui::Event::Custom);
        }
        loop.RunOnce();
    }
}

void Display::ClearScreen() {
    std::system("cls");
}




