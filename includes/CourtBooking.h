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

class CourtBooking {
public:
    string courtID;
    string memberID;
    string location;
    time_t date;
    string time;
};

void to_json(json& j, const CourtBooking& c) {
    j = json{
        {"courtID", c.courtID},
        {"memberID", c.memberID},
        {"location", c.location},
        {"date", time_t_to_string(c.date)},
        {"time", c.time}
    };
}

void from_json(const json& j, CourtBooking& c) {
    c.courtID = j.at("courtID").get<std::string>();
    c.memberID = j.at("memberID").get<std::string>();
    c.location = j.at("location").get<std::string>();
    c.date = string_to_time_t(j.at("date").get<std::string>());
    c.time = j.at("time").get<std::string>();
}