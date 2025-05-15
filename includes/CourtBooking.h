#ifndef COURTBOOKING_H
#define COURTBOOKING_H

#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <unordered_set>
#include <sstream>
// #include "User.h"

using namespace std;

class CourtBooking
{
public:
    string generateRandomMemberID()
    {
        static bool seeded = false;
        if (!seeded)
        {
            srand(time(nullptr));
            seeded = true;
        }
        string id;
        do
        {
            int num = rand() % 1000; // 0 to 999
            ostringstream oss;
            oss << "B" << setw(3) << std::setfill('0') << num;
            id = oss.str();
        } while (usedIds.find(id) != usedIds.end());

        return id;
    }

public:
    string courtID;
    string memberID;
    string location;
    string date;
    string bookingTime;
    string bookingID;
    static unordered_set<string> usedIds;
};
inline unordered_set<string> CourtBooking::usedIds;
#endif