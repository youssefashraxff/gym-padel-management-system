#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <queue>
#include "json.hpp"
#include "Utils.h"

using json = nlohmann::json;

using namespace std;

class Class {
public:
    string type;
    string id;
    string coachName;
    int capacity;
    vector<string> members;
    string dayTime;
    queue<string> waitlist;
};

void addMember(Member member, Class c) {
    if (c.members.size() < c.capacity) {
        c.members.push_back(member.id);
    }
}

void removeMember(Member member, Class c) {
    c.members.erase(remove(c.members.begin(), c.members.end(), member.id), c.members.end());
}

void addToWaitlist(Member member, Class c) {
    if (c.members.size() >= c.capacity) {
        c.waitlist.push(member.id);
    }
}

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
