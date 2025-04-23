

#ifndef WORKOUT_H
#define WORKOUT_H

#include <iostream>
#include <string>

using namespace std;

class Workout {
public:
    int memberID;
    string activity;
    string duration;
    time_t date;
};

#endif