
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
}

Display::~Display() {
    for (int i = 0; i < amount_of_cities; ++i) {
        delete cities[i];
    }
    delete[] cities;
}

auto Display::GenerateDayCard(double temperature, short humidity, size_t weather, double wind_speed) {
    return vbox({
        text("Temperature: " + std::to_string(temperature)) | center,
        text("Humidity: " + std::to_string(humidity)) | center,
        text("Weather: " + std::to_string(weather)) | center,
        text("Wind: " + std::to_string(wind_speed)) | center
    });
}


auto Display::GenerateDayInfo(Day* cur_day, int timeOfDay) {

    return vbox({});
}

auto Display::DrawCityScreen() {
    Elements widgets;
    widgets.push_back(text("Weather in " + cities[current_city]->GetName() + "is: " ) | bold | center);
    Day* cur_day = cities[current_city]->GetCurDay();
    widgets.push_back(GenerateDayCard(cur_day->GetTemperature(0),
                                      cur_day->GetHumidity(0),
                                      cur_day->GetWeather(0),
                                      cur_day->GetWind(0)));
    return vbox(widgets);
}

void Display::DrawScreen() {
    auto screen = ScreenInteractive::TerminalOutput();
    auto renderer = Renderer([&] {
        return DrawCityScreen();
    });
    renderer |= CatchEvent([&] (const Event& event) {
        if (event == Event::Escape) {
            screen.ExitLoopClosure()();
        }
        if (event == Event::Character('n')) {
            if (current_city + 1 < amount_of_cities) {
                current_city += 1;
            }
        }
        if (event == Event::Character(('p'))) {
            if (current_city - 1 > -1) {
                current_city -= 1;
            }
        }
        return false;
    });
    Loop loop (&screen, renderer);
    auto start_time = std::chrono::system_clock::now();
    while (!loop.HasQuitted()) {
        auto cur_time = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(cur_time - start_time).count() > frequency) {
            start_time = cur_time;
            screen.Post(ftxui::Event::Custom);
        }
        loop.RunOnce();
    }

}




