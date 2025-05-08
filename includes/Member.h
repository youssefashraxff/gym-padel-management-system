

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
#include <sstream>

#include "CourtBooking.h"
#include "Subscription.h"
#include <unordered_set>

using namespace std;

class Member {
public:
    string username;
    string password;
    string name;
    string id;
    int Age;
    int subscriptionId;
    static unordered_set<string> usedIds;
private:  
    string generateRandomMemberID() {
        static bool seeded = false;
    if (!seeded) {
        srand(time(nullptr));
        seeded = true;
    }
    string id;
    do {
        int num = rand() % 1000; // 0 to 999
        ostringstream oss;
        oss << "M" << setw(3) << std::setfill('0') << num;
        id = oss.str();
    } while (usedIds.find(id) != usedIds.end());

    return id;
    }
public:
    Member(const string& username,
        const string& password,
        const string& name,
        const int& age,
        const int& subscriptionId )
     : username(username), password(password), name(name), Age(age),subscriptionId(subscriptionId) {
        this->id = generateRandomMemberID();
     }

     Member(){}

    void showProfile()
    {
        cout << "\n[Profile]\n";
        cout << "ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Username: " << username << "\n";
        cout << "Age: " << Age << "\n";
        cout << "Subscription ID: " << subscriptionId << "\n";
        cout << "----------------------------------\n";
    }
};
inline unordered_set<string> Member::usedIds;
#endif 
