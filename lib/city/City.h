#pragma once
#include "cpr/cpr.h"
#include "nlohmann/json.hpp"
#include "Days.h"
#include "iostream"
#include "fstream"

class City {
public:
    City(const std::string& name_, int days_stored_);
    ~City();
    void GetTemperature();
    Day* GetDay(int index);
    Day* GetCurDay();
    std::string GetName();
    void PrintAll();
private:
    bool CheckRequestCode(const cpr::Response& rq);
    std::pair<double, double> GetCoords();
    bool GetDays(std::pair<double, double> coords);
    void UpdateCurDayInfo(nlohmann::json data);
    void UpdateDaysInfo(nlohmann::json data);
    std::string DoubleToString (double num);
    const int kHours = 6;
    const int kHoursInDay = 24;
    int days_stored = 7;
    Day** days;
    Day* cur_day;
    std::string name;
};

