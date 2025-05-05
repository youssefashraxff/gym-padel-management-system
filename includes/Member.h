

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>
#include <sstream>

#include "CourtBooking.h"
#include "Subscription.h"


using namespace std;

class Member {
public:
    string username;
    string password;
    string name;
    string id;
    int Age;
    int subscriptionId;
private:  
    string generateRandomId() {
        stringstream idStream;
        idStream << "M" << (rand() % 100000);
        return idStream.str();
    }

    public:
    Member(const string& username,
        const string& password,
        const string& name,
        const int& age)
     : username(username), password(password), name(name), Age(age) {}

     Member(){}
    
};
#endif 
