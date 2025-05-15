#ifndef STAFF_H
#define STAFF_H

#include <iostream>
#include <string>
#include "Member.h"
#include "Class.h"
#include "../utils/utils.h"
#include <vector>

using namespace std;

class Staff
{
public:
    string username;
    string password;
    string name;
    string id;
    string role;

    void showProfile()
    {
        cout << "\n[Profile]\n";
        cout << "ID: " << id << "\n";
        cout << "Name: " << name << "\n";
        cout << "Username: " << username << "\n";
        cout << "Role: " << role << "\n";
        cout << "----------------------------------\n";
    }
};
class Coach : public Staff
{
public:
    Coach() {}
    Coach(const Staff &s)
    {
        id = s.id;
        name = s.name;
        username = s.username;
        password = s.password;
        role = s.role;
    }
    void searchMemberInfo(unordered_map<string, Member *> membersUsername)
    {
        string username;
        cout << "Enter member username: ";
        cin >> username;

        if (membersUsername.count(username))
        {
            membersUsername[username]->showProfile();
        }
        else
        {
            cout << "Member not found.\n";
        }
    }
    void viewClasses(unordered_map<string, stack<Class *>> classesByCoachID, unordered_map<string, Member> membersID)
    {
        stack tempClasses = classesByCoachID[id];
        if (tempClasses.empty())
        {
            cout << "No classes available.\n";
            return;
        }
        cout << "\n[Classes]\n";
        while (!tempClasses.empty())
        {
            Class *tempClass = tempClasses.top();
            tempClass->showClass(membersID);
            tempClass->showWaitlist(membersID);
            cout << "----------------------------------\n";
            tempClasses.pop();
        }
        }
    void removeClass(unordered_map<string, Class> &classesID)
    {
        string classID;
        bool isExist;
        do
        {
            isExist = false;
            cout << "Enter Class ID to remove (e.g : CL004): ";
            cin >> classID;
            if (classesID.count(classID))
            {
                classesID.erase(classID);
                cout << "Class has been removed successfully\n";
            }
            else
            {
                cout << "Class ID not found.\n";
                isExist = true;
            }
        } while (isExist);
    }
    void addClass(unordered_map<string, Class> &classesID)
    {
        string classID, dayTime, type;
        int capacity;
        bool idExists;
        do
        {
            idExists = false;
            cout << "Enter Class ID (e.g : CL004): ";
            cin >> classID;
            if (classesID.count(classID))
            {
                cout << "Class ID already exists. Please enter a different ID.\n";
                idExists = true;
            }
        } while (idExists);
        cin.ignore();

        cout << "\nEnter the type of class: ";
        cin >> type;

        cout << "\nEnter the day and time (DD-MM-YYYY HH:MM): ";
        cin >> dayTime;

        cout << "\nEnter class capacity: ";
        cin >> capacity;

        Class temp(type, classID, this->name, this->id, capacity, string_to_time_t(dayTime));
        classesID[classID] = temp;

        cout << "Class has been added successfully\n";
    }
};
class Manager : public Staff
{
public:
    // Manager Methods
};
#endif