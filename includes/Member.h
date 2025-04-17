#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

#include "Workout.h"
#include "CourtBooking.h"
#include "Utils.h"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

struct Subscription {
    int period;
    int price;
    time_t startDate;
    time_t endDate;
    bool active;
};


class Member {
public:
    string name;
    string id;
    time_t dateOfBirth;
    Subscription subscription;
    vector<Workout> workouts;
    vector<CourtBooking> courtBookings;
};

void to_json(json& j, const Subscription& sub) {
    j = json{
        {"period", sub.period},
        {"price", sub.price},
        {"startDate", time_t_to_string(sub.startDate)},
        {"endDate", time_t_to_string(sub.endDate)},
        {"active", sub.active}
    };
}

void from_json(const json& j, Subscription& sub) {
    j.at("period").get_to(sub.period);
    j.at("price").get_to(sub.price);
    std::string startStr, endStr;
    j.at("startDate").get_to(startStr);
    j.at("endDate").get_to(endStr);
    sub.startDate = string_to_time_t(startStr);
    sub.endDate = string_to_time_t(endStr);
    j.at("active").get_to(sub.active);
}

void to_json(json& j, const Member& m) {
    j = json{
        {"name", m.name},
        {"id", m.id},
        {"dateOfBirth", time_t_to_string(m.dateOfBirth)},
        {"subscription", m.subscription}
    };
}

void from_json(const json& j, Member& m) {
    j.at("name").get_to(m.name);
    j.at("id").get_to(m.id);
    std::string dobStr;
    j.at("dateOfBirth").get_to(dobStr);
    m.dateOfBirth = string_to_time_t(dobStr);
    j.at("subscription").get_to(m.subscription);
}