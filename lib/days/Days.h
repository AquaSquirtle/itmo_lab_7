#pragma once
#include "iostream"
#include "vector"

class Day {
public:
    Day(std::vector<double> temperature_,std::vector<short> relative_humidity_ , std::vector<size_t> weather_code_, std::vector<double> wind_speed_, const std::string& data_);
    void PrintAll ();
    double GetTemperature(int index);
    short GetHumidity(int index);
    size_t GetWeather(int index);
    double GetWind(int index);
    std::string GetData();
private:
    const int kPartsOfDay = 4;
    std::string data;
    std::vector<double> temperature;
    std::vector<short> relative_humidity;
    std::vector<size_t> weather_code;
    std::vector<double> wind_speed;
};



