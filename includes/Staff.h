#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"
#include "User.h"


using json = nlohmann::json;

using namespace std;

class Staff : public User {
public:
    string name;
    string id;
    string role;
};

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
