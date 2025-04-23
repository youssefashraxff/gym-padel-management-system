#ifndef COURTBOOKING_H
#define COURTBOOKING_H


#include <iostream>
#include <string>

using namespace std;

class CourtBooking {
public:
    string courtID;
    string memberID;
    string location;
    time_t date;
    string time;
};

#endif