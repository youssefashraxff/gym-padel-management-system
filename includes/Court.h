#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Court {
public:
    string id;
    string location;
    map<string, bool> timeSlots;
};

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