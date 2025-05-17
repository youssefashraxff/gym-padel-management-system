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
    int capacity;
    time_t dayTime;
    queue<string> vipWaitlist;
    queue<string> regularWaitlist;
    unordered_set<string> memberIDs;
    unordered_map<string, bool> memberVIPStatus;

public:
    void addMember(string memberID, bool isVIP = false)
    {
        // Always store VIP status first
        memberVIPStatus[memberID] = isVIP;
        
        if (memberIDs.size() < capacity)
        {
            memberIDs.insert(memberID);
            memberVIPStatus[memberID] = isVIP;
            cout << "Booking confirmed for " << memberID << ".\n";
            cout << "\n\nMembers " << memberIDs.size() << "\n";
        }
        else
        {
            
            if (isVIP) {
                vipWaitlist.push(memberID);
            } else {
                regularWaitlist.push(memberID);
            }
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
        memberVIPStatus.erase(memberID);
        
       
        if (!vipWaitlist.empty()) {
            string nextMember = vipWaitlist.front();
            vipWaitlist.pop();
            memberIDs.insert(nextMember);
            memberVIPStatus[nextMember] = true;
            cout << "VIP Member " << nextMember << " moved from waitlist to class.\n";
        } else if (!regularWaitlist.empty()) {
            string nextMember = regularWaitlist.front();
            regularWaitlist.pop();
            memberIDs.insert(nextMember);
            memberVIPStatus[nextMember] = false;
            cout << "Member " << nextMember << " moved from waitlist to class.\n";
        }
        
        cout << "Booking cancelled for " << memberID << ".\n";
    }
    unordered_set<string> getMembers()
    {
        return memberIDs;
    }
    
    
    void showWaitlist() {
        if (vipWaitlist.empty() && regularWaitlist.empty()) {
            cout << "Waitlist is empty.\n";
            return;
        }
        
        cout << "\nWaitlist Status:\n";
        int position = 1;
        
        // Show VIP members first
        queue<string> tempVIP = vipWaitlist;
        while (!tempVIP.empty()) {
            string memberID = tempVIP.front();
            cout << position++ << ". " << memberID << " (VIP: Yes)\n";
            tempVIP.pop();
        }
        
        // Then show regular members
        queue<string> tempRegular = regularWaitlist;
        while (!tempRegular.empty()) {
            string memberID = tempRegular.front();
            cout << position++ << ". " << memberID << " (VIP: No)\n";
            tempRegular.pop();
        }
    }
};

#endif