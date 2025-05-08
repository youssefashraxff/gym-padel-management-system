#ifndef CLASS_MANAGER_H
#define CLASS_MANAGER_H

#pragma once

#include <iostream>
#include <unordered_map>
#include <stack>
#include "DataManager.h"
#include "Class.h"

using namespace std;

class ClassManager
{
private:
    DataManager data_manager;

public:
    unordered_map<string, stack<Class>> memberClasses;

    ClassManager(DataManager &data_manager)
    {
        this->data_manager = data_manager;
    }

    void load_member_classes()
    {
        for (auto c : data_manager.classes)
        {
            for ( auto m : c.getMembers())
            {
                memberClasses[m].push(c);
            }
        }
    }

    stack<Class> getWorkout(string memberID)
    {
        return memberClasses[memberID];
    }

    void addWorkout(string memberID, Class c)
    {
        memberClasses[memberID].push(c);
    }
    void show_member_history(string memberID)
    {
        cout << "\n[Your Classes History]\n";
            stack<Class> workouts = getWorkout(memberID);
            while (!workouts.empty())
            {
                Class workout = workouts.top();
                workouts.pop();
                cout << "Class Type: " << workout.type << "\n";
                cout << "Coach Name: " << workout.coachName << "\n";
                cout << "Class Time: " << workout.dayTime << "\n";
            }
    }
};

#endif