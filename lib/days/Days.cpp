#include "Days.h"
#include <utility>


Day::Day(std::vector<double> temperature_,std::vector<short> relative_humidity_, std::vector<size_t> weather_code_,
         std::vector<double> wind_speed_, const std::string& data_)
         : temperature(std::move(temperature_))
         , weather_code(std::move(weather_code_))
         , wind_speed(std::move(wind_speed_))
         , relative_humidity(std::move(relative_humidity_))
         , data(data_)
         {}

void Day::PrintAll() {
    std::cout << '\n';
    std::cout << data << '\n';
    for (int i = 0; i < temperature.size(); ++i) {
        std::cout << "temp: " << temperature[i];
        std::cout << " weather_code: " << weather_code[i];
        std::cout << " wind: " << wind_speed[i];
        std::cout << " humidity: " << relative_humidity[i];
        std::cout << '\n';
    }
}

double Day::GetTemperature(int index) {
    if (index < kPartsOfDay) {
        return temperature[index];
    }
    return -1;
}

short Day::GetHumidity(int index) {
    if (index < kPartsOfDay) {
        return relative_humidity[index];
    }
    return -1;
}

size_t Day::GetWeather(int index) {
    if (index < kPartsOfDay) {
        return weather_code[index];
    }
    return -1;
}

double Day::GetWind(int index) {
    if (index < kPartsOfDay) {
        return wind_speed[index];
    }
    return -1;
}

std::string Day::GetData() {
    return data;
}

