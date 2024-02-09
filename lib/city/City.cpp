#include "City.h"

City::City(const std::string& name_, int days_stored_)
    : name(name_)
    , days_stored(days_stored_)
    {
        cur_day = nullptr;
        days = new Day*[days_stored];
        for (int i = 0; i < days_stored; ++i) {
            days[i] = nullptr;
        }
    }

City::~City() {
    for (int i = 0; i < days_stored; ++i) {
        if (days[i] != nullptr) {
            delete days[i];
        }
    }
    if (cur_day != nullptr) {
        delete cur_day;
    }
    delete[] days;
}


std::pair<double, double> City::GetCoords() {
    std::string url = "https://api.api-ninjas.com/v1/city?name=" + name;
    cpr::Response rq = cpr::Get(cpr::Url{url}, cpr::Header{{"X-Api-Key","6ZDgLgxbqAP5Rgo6/GwJhQ==ZZr0UpZ94Apt99rb"}});
    if (CheckRequestCode(rq)) {
        auto rq_json = nlohmann::json::parse(rq.text);
        return std::make_pair(rq_json[0]["latitude"],rq_json[0]["longitude"]);
    }
    else {
        std::cout << "Failed to execute\n";
        exit(0);
    }
}

bool City::GetDays(std::pair<double, double> coords) {
    std::string url = "https://api.open-meteo.com/v1/forecast";
    cpr::Response rq = cpr::Get(cpr::Url{url},cpr::Parameters{
        {"latitude", std::to_string(coords.first)},
        {"longitude", std::to_string(coords.second)},
        {"hourly", "temperature_2m,wind_speed_10m,weather_code,relative_humidity_2m"},
        {"current", "temperature_2m,wind_speed_10m,weather_code,relative_humidity_2m"},
        {"forecast_days", std::to_string(days_stored)}
    });
    if (CheckRequestCode(rq)) {
        auto rq_json = nlohmann::json::parse(rq.text);
        UpdateDaysInfo(rq_json);
        UpdateCurDayInfo(rq_json);
        return true;
    }
    return false;
}

void City::UpdateDaysInfo(const auto data) {
    for (int i = 0; i < days_stored; ++i) {
        std::vector<double> temperature {};
        std::vector<size_t> weather_code {};
        std::vector<short> relative_humidity {};
        std::vector<double> wind_speed {};
        for (int j = 0; j < kHoursInDay/kHours; ++j) {
            double temp_t = data["hourly"]["temperature_2m"][i*kHoursInDay + j*kHours];;
            double temp_w = data["hourly"]["wind_speed_10m"][i*kHoursInDay + j*kHours];
            size_t temp_weather = data["hourly"]["weather_code"][i*kHoursInDay + j*kHours];
            short temp_rh = data["hourly"]["weather_code"][i*kHoursInDay + j*kHours];
            weather_code.push_back(temp_weather);
            temperature.push_back(temp_t);
            wind_speed.push_back(temp_w);
            relative_humidity.push_back(temp_rh);
        }
        std::string temp = data["hourly"]["time"][i*kHoursInDay];
        temp = temp.substr(0, 10);
        days[i] = new Day
                ( temperature
                , relative_humidity
                , weather_code
                , wind_speed
                , temp
                );
    }
}

void City::UpdateCurDayInfo(const auto data) {
    std::vector<double> temperature {};
    std::vector<size_t> weather_code {};
    std::vector<short> relative_humidity {};
    std::vector<double> wind_speed {};
    double temp_t = data["current"]["temperature_2m"];
    double temp_w = data["current"]["wind_speed_10m"];
    size_t temp_weather = data["current"]["weather_code"];
    short temp_rh = data["current"]["relative_humidity_2m"];
    weather_code.push_back(temp_weather);
    temperature.push_back(temp_t);
    wind_speed.push_back(temp_w);
    relative_humidity.push_back(temp_rh);

    std::string temp = data["current"]["time"];
    temp = temp.substr(11, 16);
    cur_day = new Day
            ( temperature
                    , relative_humidity
                    , weather_code
                    , wind_speed
                    , temp
            );
}

bool City::CheckRequestCode(const cpr::Response &rq) {
    return rq.status_code == 200;
}

void City::GetTemperature() {
    std::pair<double, double> coords = GetCoords();
    if (GetDays(coords)) {
        std::cout << "success\n";
    }
    else {
        std::cout << "failure\n";
    }
}

void City::PrintAll() {
    for (int i = 0; i < days_stored; ++i) {
        std::cout << " Day: " << i+1;
        days[i]->PrintAll();
        std::cout << '\n';
    }
}

Day* City::GetDay(int index) {
    if (index < days_stored) {
        days[index]->PrintAll();
        return days[index];
    }
    return nullptr;
}

std::string City::GetName() {
    return name;
}

Day *City::GetCurDay() {
    return cur_day;
}


