#ifndef JSON_UTILS_H
#define JSON_UTILS_H

#include "utils.h"

#include "../includes/json.hpp"
using nlohmann::json;

// Include custom class headers relative to this file's location
#include "../includes/Member.h"
#include "../includes/Staff.h"
#include "../includes/Class.h"
#include "../includes/Court.h"
#include "../includes/CourtBooking.h"
#include "../includes/User.h"
#include "../includes/Notification.h"
#include "../includes/Subscription.h"

#include <sstream>
#include <iomanip>

#include <vector>
#include <queue>

string cleanUTF8(const string& str);

// Member & Subscription
void to_json(json& j, const Subscription& sub);
void from_json(const json& j, Subscription& sub);

void to_json(json& j, const Member& m);
void from_json(const json& j, Member& m);

// Staff
void to_json(json& j, const Staff& s);
void from_json(const json& j, Staff& s);

// Class
void to_json(json& j, const Class& c);
void from_json(const json& j, Class& c);

// Court
void to_json(json& j, const Court& c);
void from_json(const json& j, Court& c);

// CourtBooking
void to_json(json& j, const CourtBooking& c);
void from_json(const json& j, CourtBooking& c);

// Notification
void to_json(json& j, const Notification& n);
void from_json(const json& j, Notification& n);

//user

// void to_json(json& j, const Member& m);
// void from_json(const json& j, Member& m) ;


string time_t_to_string(const time_t& t);
time_t string_to_time_t(const string& str);

// Queue <-> Vector conversion functions
vector<string> queue_to_vector(queue<string> q);
queue<string> vector_to_queue(const vector<string>& v);

#endif // JSON_UTILS_H