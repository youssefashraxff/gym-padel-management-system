#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

#include "Utils.h"

using json = nlohmann::json;

using namespace std;

class Workout {
public:
    int memberID;
    string activity;
    string duration;
    time_t date;
};

void to_json(json& j, const Workout& w) {
    j = json{
        {"memberID", w.memberID},
        {"activity", w.activity},
        {"duration", w.duration},
        {"date", time_t_to_string(w.date)}
    };
}


void from_json(const json& j, Workout& w) {
    j.at("memberID").get_to(w.memberID);
    j.at("activity").get_to(w.activity);
    j.at("duration").get_to(w.duration);
    w.date = string_to_time_t(j.at("date").get<string>());
}