#include "Days.h"
#include <utility>


Day::Day(std::vector<std::string> temperature_,std::vector<std::string> relative_humidity_, std::vector<int> weather_code_,
         std::vector<std::string> wind_speed_, const std::string& data_)
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

std::string Day::GetTemperature(int index) {
    if (index < kPartsOfDay) {
        return temperature[index];
    }
    return "";
}

std::string Day::GetHumidity(int index) {
    if (index < kPartsOfDay) {
        return relative_humidity[index];
    }
    return "";
}

std::string Day::GetWeather(int index) {
    if (index < kPartsOfDay) {
        return ReturnWeatherCode(weather_code[index]);
    }
    return "";
}

std::string Day::GetWind(int index) {
    if (index < kPartsOfDay) {
        return wind_speed[index];
    }
    return "";
}

std::string Day::GetData() {
    return data;
}

std::string Day::ReturnWeatherCode(int code) {
    std::map<int, std::string> codes;
    codes[0] = "Clear Sky";
    codes[1] = "Mainly Clear";
    codes[2] = "Partly Cloudy";
    codes[3] = "Overcast";
    codes[45] = "Fog";
    codes[48] = "Deposing Rime Fog";
    codes[51] = "Light Drizzle";
    codes[53] = "Moderate Drizzle";
    codes[55] = "Dense Drizzle";
    codes[56] = "Light Freezing Drizzle";
    codes[57] = "Dense Freezing Drizzle";
    codes[61] = "Slight Rain";
    codes[63] = "Moderate Rain";
    codes[65] = "Heavy Rain";
    codes[66] = "Light Freezing Rain";
    codes[67] = "Heavy Freezing Rain";
    codes[71] = "Slight Snow Fall";
    codes[73] = "Moderate Snow Fall";
    codes[75] = "Heavy Snow Fall";
    codes[77] = "Snow Grains";
    codes[80] = "Slight Rain Showers";
    codes[81] = "Moderate Rain Showers";
    codes[82] = "Heavy Rain Showers";
    codes[85] = "Light Snow Showers";
    codes[86] = "Heavy Snow Showers";
    codes[95] = "Thunderstorm";
    codes[96] = "Slight Rain and Thunderstorm";
    codes[99] = "Heavy Rain and Thunderstorm";
    try {
        return codes[code];
    }
    catch (...) {
        return "Weather Code Not Found";
    }

}

