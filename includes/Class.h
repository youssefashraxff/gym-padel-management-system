

#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>

// #include "Member.h"
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

// void addMember(Member member, Class c) {
//     if (c.members.size() < c.capacity) {
//         c.members.push_back(member.id);
//     }
// }

// void removeMember(Member member, Class c) {
//     c.members.erase(remove(c.members.begin(), c.members.end(), member.id), c.members.end());
// }

// void addToWaitlist(Member member, Class c) {
//     if (c.members.size() >= c.capacity) {
//         c.waitlist.push(member.id);
//     }
// }
#endif