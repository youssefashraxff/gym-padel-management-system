#include <iostream>

#include "json_utils.h"
#include "../includes/Notification.h"

using namespace std;
using json = nlohmann::json;

// Subscription

void to_json(json &j, const Subscription &sub)
{
    j = json{
        {"id", sub.id},
        {"period", sub.period},
        {"price", sub.price},
        {"startDate", time_t_to_string(sub.startDate)},
        {"endDate", time_t_to_string(sub.endDate)},
        {"active", sub.active}};
}

void from_json(const json &j, Subscription &sub)
{
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

// Member

void to_json(json &j, const Member &m)
{
    j = {
        {"id", m.id},
        {"name", m.name},
        {"username", m.username},
        {"password", m.password},
        {"age", m.Age},
        {"subscriptionId", m.subscriptionId}};
}

void from_json(const json &j, Member &m)
{
    j.at("name").get_to(m.name);
    j.at("username").get_to(m.username);
    j.at("password").get_to(m.password);
    j.at("id").get_to(m.id);
    j.at("age").get_to(m.Age);
    j.at("subscriptionId").get_to(m.subscriptionId);
}

// Staff

void to_json(json &j, const Staff &s)
{
    j = json{
        {"username", s.username},
        {"password", s.password},
        {"name", s.name},
        {"id", s.id},
        {"role", s.role}};
}

void from_json(const json &j, Staff &s)
{
    s.username = j.at("username").get<string>();
    s.password = j.at("password").get<string>();
    s.name = j.at("name").get<string>();
    s.id = j.at("id").get<string>();
    s.role = j.at("role").get<string>();
}

// Class

void to_json(json &j, const Class &c)
{
    j = json{
        {"type", c.type},
        {"id", c.id},
        {"coachName", c.coachName},
        {"capacity", c.capacity},
        {"memberIDs", c.memberIDs},
        {"dayTime", c.dayTime}, // store as time_t (number)
        {"waitlist", queue_to_vector(c.waitlist)}};
}

void from_json(const json &j, Class &c)
{
    j.at("type").get_to(c.type);
    j.at("id").get_to(c.id);
    j.at("coachName").get_to(c.coachName);
    j.at("capacity").get_to(c.capacity);
    j.at("memberIDs").get_to(c.memberIDs);

    j.at("dayTime").get_to(c.dayTime); // get as time_t (number)

    vector<string> waitlistVec;
    j.at("waitlist").get_to(waitlistVec);
    c.waitlist = vector_to_queue(waitlistVec);
}

// Court

void to_json(json &j, const Court &c)
{
    j = json{
        {"id", c.id},
        {"location", c.location},
        {"timeSlots", c.timeSlots}};
}

void from_json(const json &j, Court &c)
{
    j.at("id").get_to(c.id);
    j.at("location").get_to(c.location);
    j.at("timeSlots").get_to(c.timeSlots);
}

// Court Booking

void to_json(json &j, const CourtBooking &c)
{
    j = json{
        {"courtID", c.courtID},
        {"memberID", c.memberID},
        {"location", c.location},
        {"date", time_t_to_string(c.date)},
        {"time", c.time}};
}

void from_json(const json &j, CourtBooking &c)
{
    c.courtID = j.at("courtID").get<std::string>();
    c.memberID = j.at("memberID").get<std::string>();
    c.location = j.at("location").get<std::string>();
    c.date = string_to_time_t(j.at("date").get<std::string>());
    c.time = j.at("time").get<std::string>();
}

// Notification
void to_json(json &j, const Notification &n)
{
    j = json{
        {"message", n.message},
        {"timestamp", time_t_to_string(n.timestamp)},
        {"memberId", n.memberId}};
}

void from_json(const json &j, Notification &n)
{
    n.message = j.at("message").get<string>();
    n.timestamp = string_to_time_t(j.at("timestamp").get<string>());
    n.memberId = j.contains("memberId") ? j.at("memberId").get<string>() : "";
}

// User

// void to_json(json& j, const User& u) {
//     j = json{
//         {"username", u.getUsername()},
//         {"password", u.getPassword()}
//     };
// }

// //WRITE INTO FILES
// void from_json(const json& j, User& u) {
//     string username, pass;
//     j.at("username").get_to(username);
//     j.at("password").get_to(pass);

//     u.setUsername(username);
//     u.setPassword(pass);
// }