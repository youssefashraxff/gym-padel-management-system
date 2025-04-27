#ifndef WORKOUT_MANAGER_H
#define WORKOUT_MANAGER_H

#include<iostream>

#include"DataManager.h"
#include"map"
#include"stack"
#include<Workout.h>

#pragma once
using namespace std;

class WorkoutManager
{
private:
    DataManager data_manager;
public:
    map<string,stack<Workout>> memberWorkouts;
    
    WorkoutManager(DataManager &data_manager){
        this->data_manager=data_manager;
    }

    void load_member_workouts(){
        for(int i = 0 ;i<data_manager.workouts.size();i++){
            string member_ID = data_manager.workouts.at(i).memberID;
            memberWorkouts[member_ID].push(data_manager.workouts.at(i));
        }
    }
    stack<Workout> getWorkout(string memberID){
        return memberWorkouts[memberID];
    }
    void addWorkout(string memberID,Workout w){
        memberWorkouts[memberID].push(w);
        data_manager.workouts.push_back(w);
    }
};

#endif