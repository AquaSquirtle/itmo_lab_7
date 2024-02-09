#pragma once
#include "iostream"
#include "vector"
#include "map"

class Day {
public:
    Day(std::vector<std::string> temperature_,std::vector<std::string> relative_humidity_ , std::vector<int> weather_code_, std::vector<std::string> wind_speed_, const std::string& data_);
    void PrintAll ();
    std::string GetTemperature(int index);
    std::string GetHumidity(int index);
    std::string GetWeather(int index);
    std::string GetWind(int index);
    std::string GetData();
private:
    std::string ReturnWeatherCode(int code);
    const int kPartsOfDay = 4;
    std::string data;
    std::vector<std::string> temperature;
    std::vector<std::string> relative_humidity;
    std::vector<int> weather_code;
    std::vector<std::string> wind_speed;
};



