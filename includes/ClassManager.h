#ifndef CLASS_MANAGER_H
#define CLASS_MANAGER_H

#pragma once

#include <iostream>
#include <unordered_map>
#include <stack>
#include "DataManager.h"
#include "Class.h"
#include <ctime>

using namespace std;

class ClassManager
{
private:
    DataManager &data_manager;

public:
    unordered_map<string, stack<Class *>> memberClasses;

    ClassManager(DataManager &data_manager) : data_manager(data_manager) {}

    void load_member_classes()
    {
        for (auto &pair : data_manager.classesID)
        {
            Class &c = pair.second;
            for (const string &m : c.getMembers())
            {
                memberClasses[m].push(&c);
            }
        }
    }

    stack<Class *> getWorkout(string memberID)
    {
        return memberClasses[memberID];
    }

    void addWorkout(string memberID, Class *c)
    {
        memberClasses[memberID].push(c);
    }
    void removeWorkout(string memberID, Class *c)
    {
        memberClasses[memberID].pop();
    }

    void show_member_history(string memberID)
    {
        cout << "\n[Your Classes History]\n";
        stack<Class *> workouts = getWorkout(memberID);
        while (!workouts.empty())
        {
            Class *workout = workouts.top();
            workouts.pop();
            cout << "\nClass ID: " << workout->id << "\n";
            cout << "\nClass Type: " << workout->type << "\n";
            cout << "Coach Name: " << workout->coachName << "\n";
            string workoutDate = time_t_to_string(workout->dayTime);
            cout << "Class Time: " << workoutDate << "\n";
            if ((workout->dayTime) < time(nullptr))
            {
                cout << "Status : [Done]\n";
            }
            else
            {
                cout << "Status : [Pending]\n";
            }
        }
    }
    void show_member_pending_classes(string memberID)
    {
        cout << "\n[Your Pending Classes]\n";
        stack<Class *> workouts = getWorkout(memberID);

        bool hasUpcoming = false;

        while (!workouts.empty())
        {
            Class *workout = workouts.top();
            workouts.pop();

            if (workout->dayTime < time(nullptr))
                continue;

            hasUpcoming = true;
            cout << "\nClass ID: " << workout->id << "\n";
            cout << "\nClass Type: " << workout->type << "\n";
            cout << "Coach Name: " << workout->coachName << "\n";
            string workoutDate = time_t_to_string(workout->dayTime);
            cout << "Class Time: " << workoutDate << "\n";
        }

        if (!hasUpcoming)
            cout << "You have no upcoming classes.\n";
    }
};

#endif
