#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Staff {
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
    s.name = j.at("name").get<std::string>();
    s.id = j.at("id").get<std::string>();
    s.role = j.at("role").get<std::string>();
}