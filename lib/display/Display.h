#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "ftxui/component/loop.hpp"
#include <iostream>
#include "lib/city/City.h"
#include "lib/days/Days.h"

class Display {
public:
    Display(std::vector<std::string> names, int days_stored_, size_t frequency_);
    auto GenerateDayInfo(Day* cur_day, int timeOfDay);
    auto GenerateDayCard(double temperature, short humidity, size_t weather, double wind_speed);
    auto DrawCityScreen();
    void DrawScreen();
    ~Display();
private:
    int kDaysParts = 4;
    int days_stored;
    size_t current_city = 0;
    size_t frequency;
    size_t amount_of_cities;
    City** cities;
};


