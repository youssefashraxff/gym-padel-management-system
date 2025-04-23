#include <iostream>

#include "json_utils.h"
// #include "includes/Member.h"
// #include "includes/Staff.h"
// #include "includes/Workout.h"
// #include "includes/Class.h"
// #include "includes/Court.h"
// #include "includes/CourtBooking.h"
// #include "includes/json.hpp"

#include <sstream>
#include <iomanip>

#include <vector>
#include <queue>

using namespace std;
using json = nlohmann::json;

//Subscription

void to_json(json& j, const Subscription& sub) {
    j = json{
        {"id" , sub.id},
        {"period", sub.period},
        {"price", sub.price},
        {"startDate", time_t_to_string(sub.startDate)},
        {"endDate", time_t_to_string(sub.endDate)},
        {"active", sub.active}
    };
}

void from_json(const json& j, Subscription& sub) {
    j.at("id").get_to(sub.id);
    j.at("period").get_to(sub.period);
    j.at("price").get_to(sub.price);
    string startStr, endStr;
    j.at("startDate").get_to(startStr);
    j.at("endDate").get_to(endStr);
    sub.startDate = string_to_time_t(startStr);
    sub.endDate = string_to_time_t(endStr);
    j.at("active").get_to(sub.active);
}

//Member

void to_json(json& j, const Member& m) {
    j = json{
        {"name", m.name},
        {"id", m.id},
        {"dateOfBirth", time_t_to_string(m.dateOfBirth)},
        {"subscriptionId", m.subscriptionId},
        {"workoutIds" , m.workoutIds},
        {"courtBookingIds" , m.courtBookingIds}
    };
}

void from_json(const json& j, Member& m) {
    j.at("name").get_to(m.name);
    j.at("id").get_to(m.id);
    std::string dobStr;
    j.at("dateOfBirth").get_to(dobStr);
    m.dateOfBirth = string_to_time_t(dobStr);
    j.at("subscriptionId").get_to(m.subscriptionId);
    j.at("workoutIds").get_to(m.workoutIds);
    j.at("courtBookingIds").get_to(m.courtBookingIds);
}

//Staff

void to_json(json& j, const Staff& s) {
    j = json{
        {"name", s.name},
        {"id", s.id},
        {"role", s.role}
    };
}

void from_json(const json& j, Staff& s) {
    s.name = j.at("name").get<string>();
    s.id = j.at("id").get<string>();
    s.role = j.at("role").get<string>();
}

//Class

void to_json(json& j, const Class& c) {
    j = json{
        {"type", c.type},
        {"id", c.id},
        {"coachName", c.coachName},
        {"capacity", c.capacity},
        {"members", c.members},
        {"dayTime", c.dayTime},
        {"waitlist", queue_to_vector(c.waitlist)}
    };
}

void from_json(const json& j, Class& c) {
    j.at("type").get_to(c.type);
    j.at("id").get_to(c.id);
    j.at("coachName").get_to(c.coachName);
    j.at("capacity").get_to(c.capacity);
    j.at("members").get_to(c.members);
    j.at("dayTime").get_to(c.dayTime);

    vector<string> waitlistVec;
    j.at("waitlist").get_to(waitlistVec);
    c.waitlist = vector_to_queue(waitlistVec);
}

//Court

void to_json(json& j, const Court& c) {
    j = json{
        {"id", c.id},
        {"location", c.location},
        {"timeSlots", c.timeSlots}
    };
}

void from_json(const json& j, Court& c) {
    j.at("id").get_to(c.id);
    j.at("location").get_to(c.location);
    j.at("timeSlots").get_to(c.timeSlots);
}

//Court Booking

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

//Workout

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

