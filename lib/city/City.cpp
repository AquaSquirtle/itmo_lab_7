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
        delete days[i];
    }
    delete cur_day;
    delete[] days;
}

bool City::GetDays() {
    std::string coords_url = "https://api.api-ninjas.com/v1/city?name=" + name;
    cpr::Response coords_rq = cpr::Get(cpr::Url{coords_url}, cpr::Header{{"X-Api-Key","6ZDgLgxbqAP5Rgo6/GwJhQ==ZZr0UpZ94Apt99rb"}});
    if (!CheckRequestCode(coords_rq)) {
        return false;
    }
    nlohmann::json coords_json = nlohmann::json::parse(coords_rq.text);
    std::pair<double, double> coords = std::make_pair(coords_json[0]["latitude"],coords_json[0]["longitude"]);

    std::string url = "https://api.open-meteo.com/v1/forecast";
    cpr::Response rq = cpr::Get(cpr::Url{url},cpr::Parameters{
        {"latitude", std::to_string(coords.first)},
        {"longitude", std::to_string(coords.second)},
        {"hourly", "temperature_2m,wind_speed_10m,weather_code,relative_humidity_2m"},
        {"current", "temperature_2m,wind_speed_10m,weather_code,relative_humidity_2m"},
        {"forecast_days", std::to_string(days_stored)}
    });
    if (!CheckRequestCode(rq)) {
        return false;
    }
    nlohmann::json rq_json = nlohmann::json::parse(rq.text);
    UpdateDaysInfo(rq_json);
    UpdateCurDayInfo(rq_json);
    return true;
}

void City::UpdateDaysInfo(nlohmann::json data) {
    for (int i = 0; i < days_stored; ++i) {
        std::vector<std::string> temperature {};
        std::vector<int> weather_code {};
        std::vector<std::string> relative_humidity {};
        std::vector<std::string> wind_speed {};
        for (int j = 0; j < kHoursInDay/kHours; ++j) {
            weather_code.push_back(data["hourly"]["weather_code"][i*kHoursInDay + j*kHours].get<short>());
            temperature.push_back(DoubleToString(data["hourly"]["temperature_2m"][i*kHoursInDay + j*kHours].get<double>()));
            wind_speed.push_back(DoubleToString(data["hourly"]["wind_speed_10m"][i*kHoursInDay + j*kHours].get<double>()));
            relative_humidity.push_back(std::to_string(data["hourly"]["relative_humidity_2m"][i*kHoursInDay + j*kHours].get<short>()));
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

void City::UpdateCurDayInfo(nlohmann::json data) {
    std::vector<std::string> temperature {};
    std::vector<int> weather_code {};
    std::vector<std::string> relative_humidity {};
    std::vector<std::string> wind_speed {};
    weather_code.push_back(data["current"]["weather_code"].get<int>());
    temperature.push_back(DoubleToString(data["current"]["temperature_2m"].get<double>()));
    wind_speed.push_back(DoubleToString(data["current"]["wind_speed_10m"].get<double>()));
    relative_humidity.push_back(std::to_string(data["current"]["relative_humidity_2m"].get<short>()));

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

bool City::GetTemperature(int days_stored_) {
    days_stored = days_stored_;
    if (GetDays()) {
        return true;
    }
    return false;
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

std::string City::DoubleToString(double num) {
    std::ostringstream oss;
    oss << std::fixed << num;
    std::string str = oss.str();

    // Удаление ненужных нулей
    str.erase(str.find_last_not_of('0') + 1, std::string::npos);
    if (str.back() == '.') {
        str.pop_back();
    }
    return str;
}


