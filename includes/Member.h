#include <iostream>
#include <string>
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Member {
public:
    string name;
    int id;
};

void to_json(json& j, const Member& m) {
    j = json{{"name", m.name}, {"id", m.id}};
}

void from_json(const json& j, Member& s) {
    j.at("name").get_to(s.name);
    j.at("id").get_to(s.id);
}