#ifndef CLASS_MANAGER_H
#define CLASS_MANAGER_H

#pragma once

#include <iostream>
#include <map>
#include <stack>
#include "DataManager.h"
#include "Class.h"

using namespace std;

class ClassManager
{
private:
    DataManager data_manager;

public:
    map<string, stack<Class>> memberClasses;

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
                // cout<<"\n\n loading \n\n";
                // cout<<"Member ID: " << m << " Class ID: " << c.id << endl;
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
};

#endif