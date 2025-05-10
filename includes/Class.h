#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>

#include "Member.h"
#include <unordered_set>
#include "../utils/utils.h"


using namespace std;

class Class {
public:
    string type;
    string id;
    string coachName;
    int capacity;
    string dayTime;
    vector<string> members;
    queue<string> waitlist;
    unordered_set<string> memberIDs;
 
public:
    bool addMember(string memberID) {
        if (memberIDs.size() < capacity) {
            memberIDs.insert(memberID);
            cout << "Booking confirmed for " << memberID << ".\n";
            return true;
        } else {
            waitlist.push(memberID);
            cout << "Class is full. " << memberID << " added to waitlist.\n";
            return false;
        }
    }
    void removeMember(string memberID) {
        if (memberIDs.find(memberID) == memberIDs.end()) {
            cout << "Member " << memberID << " not found in this class.\n";
            return;
        }
        memberIDs.erase(memberID);
        cout << "Booking cancelled for " << memberID << ".\n";
    }
    unordered_set <string> getMembers() {
        return memberIDs;
    }
};

#endif