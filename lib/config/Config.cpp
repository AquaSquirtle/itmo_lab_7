#include "Config.h"

Config::Config(const std::string &path) {
    std::ifstream file(path);
    if (file.is_open()) {
        std::ostringstream temp;
        temp << file.rdbuf();
        std::string string_json = temp.str();
        nlohmann::json json = nlohmann::json::parse(string_json);
        cities = json["city"];
        frequency = json["frequency"];
        days_stored = json["days_stored"];
    }
    else {
        std::cout << "There is no such config file";
        exit(0);
    }
}


size_t Config::GetFreq() {
    return frequency;
}

int Config::GetDays() {
    return days_stored;
}

std::vector<std::string> Config::GetCities() {
    std::vector<std::string> result;
    for (auto i: cities) {
        result.push_back(i);
    }
    return result;
}

