#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/component/loop.hpp"
#include <iostream>
#include "city/Days.h"
#include "city/City.h"
#include "map"

class Display {
public:
    Display(std::vector<std::string> names, int days_stored_, size_t frequency_);
    auto GenerateDayCard(Day* day, int index, bool is_cur_day);
    auto DrawCityScreen();
    void DrawScreen();
    ~Display();
private:
    void ClearScreen();
    std::map<int, std::string> part_of_day;
    const int kDaysParts = 4;
    const int kMaxDaysStored = 36;
    bool is_temperature_parsed = false;
    int days_stored;
    long long current_city = 0;
    size_t frequency;
    size_t amount_of_cities;
    City** cities;
};


