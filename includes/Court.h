#ifndef COURT_H
#define COURT_H

#include <iostream>
#include <string>
#include <map>
#include <ctime>   // For time calculations
#include <iomanip> // For put_time
#include <sstream> // For stringstream

using namespace std;

class Court
{
public:
    string id;
    string location;
    map<string, map<string, bool>> daySlots;
};

#endif