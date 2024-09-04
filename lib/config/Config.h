#pragma once
#include "iostream"
#include "nlohmann/json.hpp"
#include "fstream"
#include "vector"
class Config {
public:
    Config(const std::string& path);
    std::vector<std::string> GetCities();
    size_t GetFreq();
    int GetDays();
private:
    nlohmann::json cities;
    size_t frequency;
    int days_stored;
};

