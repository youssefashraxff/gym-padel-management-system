#ifndef WORKOUT_MANAGER_H
#define WORKOUT_MANAGER_H

#include<iostream>

#include"DataManager.h"
#include"map"
#include"stack"


#pragma once
using namespace std;

class WorkoutManager
{
private:

public:
    map<string,stack<int>> memberWorkouts;
    void load_member_bookings(DataManager &data_manager){
        for(int i = 0 ;i<data_manager.workouts.size();i++){
            string member_ID = data_manager.workouts.at(i).memberID;
            int workout_ID = data_manager.workouts.at(i).workoutID;
            memberWorkouts[member_ID].push(workout_ID);
        }
    }
};

#endif