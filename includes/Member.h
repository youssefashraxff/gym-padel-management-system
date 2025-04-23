

#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>
#include <string>


#include "Workout.h"
#include "CourtBooking.h"
#include "Subscription.h"

using namespace std;

class Member {
public:
    // string email;
    // string password;
    string name;
    string id;
    time_t dateOfBirth;
    int subscriptionId;
    vector<int> workoutIds;
    vector<int> courtBookingIds;
};
#endif 
