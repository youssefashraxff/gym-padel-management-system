

#ifndef COURT_H
#define COURT_H

#include <iostream>
#include <string>
#include <map>


using namespace std;

class Court {
public:
    string id;
    string location;
    map<string, bool> timeSlots;
};
#endif
