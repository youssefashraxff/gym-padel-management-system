#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
#include <ctime>

#include "Member.h"
#include <unordered_set>
#include "../utils/utils.h"

using namespace std;

class Class
{
public:
    string type;
    string id;
    string coachName;
    string coachId;
    int capacity;
    time_t dayTime;
    queue<string> waitlist;
    unordered_set<string> memberIDs;

public:
    Class(string type, string id, string coachName, string coachId, int capacity, time_t dayTime)
        : type(type), id(id), coachName(coachName), coachId(coachId), capacity(capacity), dayTime(dayTime) {}
    Class() {}
    void addMember(string memberID)
    {
        if (memberIDs.size() < capacity)
        {
            memberIDs.insert(memberID);
            cout << "Booking confirmed for " << memberID << ".\n";
            cout << "\n\nMembers " << memberIDs.size() << "\n";
        }
        else
        {
            waitlist.push(memberID);
            cout << "Class is full. " << memberID << " added to waitlist.\n";
        }
    }
    void removeMember(string memberID)
    {
        if (memberIDs.find(memberID) == memberIDs.end())
        {
            cout << "Member " << memberID << " not found in this class.\n";
            return;
        }
        memberIDs.erase(memberID);
        addMember(waitlist.front());
        waitlist.pop();
        cout << "Booking cancelled for " << memberID << ".\n";
    }
    unordered_set<string> getMembers()
    {
        return memberIDs;
    }
    void showClass(unordered_map<string, Member> membersID)
    {
        cout << "\nClass ID: " << id << "\n";
        cout << "Class Type: " << type << "\n";
        cout << "Coach Name: " << coachName << "\n";
        cout << "Capacity: " << capacity << "\n";
        cout << "Date & Time: " << time_t_to_string(dayTime) << "\n";
        cout << "\nEnrolled Members: ";
        if (memberIDs.empty())
        {
            cout << "None" << endl;
        }
        else
        {
            for (const auto &it : memberIDs)
            {
                cout << "\nID: " << membersID[it].id << "\n";
                cout << "Name" << membersID[it].name << "\n";
                cout << "Username: " << membersID[it].username << "\n";
            }
        }
    }

    void showWaitlist(unordered_map<string, Member> membersID)
    {
        cout << "\nWaitlist: ";
        if (waitlist.empty())
        {
            cout << "None" << endl;
        }
        else
        {
            queue<string> copy = waitlist;
            while (!copy.empty())
            {
                cout << "\nID: " << membersID[copy.front()].id << "\n";
                cout << "Name: " << membersID[copy.front()].name << "\n";
                cout << "Username: " << membersID[copy.front()].username << "\n";
                copy.pop();
            }
            cout << endl;
        }
    }
};

#endif