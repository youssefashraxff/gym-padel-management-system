

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

    void addMember(string memberID) {
        if (members.size() < capacity) {
            members.push_back(memberID);
        }
    }
    
    void removeMember(string memberID) {
        members.erase(remove(members.begin(), members.end(), memberID), members.end());
    }
    
    void addToWaitlist(string memberID) {
        if (members.size() >= capacity) {
            waitlist.push(memberID);
        }
    }
};

#endif