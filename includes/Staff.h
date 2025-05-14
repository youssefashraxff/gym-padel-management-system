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

    void searchMemberInfo(vector<Member> &members)
    {
        string username;
        cout << "Enter member username: ";
        cin >> username;
        bool found = false;
        cout << members.size();
        for (int i = 0; i < members.size(); i++)
        {
            if (members[i].username == username)
            {
                cout << "Displaying member info:\n";
                members[i].showProfile();
                found = true;
                break;
            }
        }
        if (found == false)
        {
            cout << "Member not found." << endl;
        }
    }
    void viewClasses(vector<Class> &classes)
    {
        int size = classes.size();
        for (int i = 0; i < size; i++)
        {
            cout << "Class ID: " << classes[i].id << endl;
            cout << "Type: " << classes[i].type << endl;
            cout << "Coach: " << classes[i].coachName << endl;
            cout << "Capacity: " << classes[i].capacity << endl;
            cout << "Date & Time: " << classes[i].dayTime << endl;
            cout << "Enrolled Members: ";
            if (classes[i].memberIDs.empty())
            {
                cout << "None" << endl;
            }
            else
            {
                int s = classes[i].memberIDs.size();
                for (auto it : classes[i].memberIDs)
                {
                    cout << it << " ";
                }
                cout << endl;
            }
            cout << "Waitlist: ";
            if (classes[i].waitlist.empty())
            {
                cout << "None" << endl;
            }
            else
            {
                queue<string> copy = classes[i].waitlist;
                while (!copy.empty())
                {
                    cout << copy.front() << " ";
                    copy.pop();
                }
                cout << endl;
            }
            cout << "------------------------" << endl;
        }
    }
    void removeClass(string id, vector<Class> &classes)
    {
        cout << "Enter class ID you want to remove:" << endl;
        cin >> id;
        for (int i = 0; i < classes.size(); i++)
        {
            if (classes[i].id == id)
            {
                classes.erase(classes.begin() + i);
                i--;
                cout << "Class with ID" << "  " << classes[i].id << " has been removed successfully" << endl;
                break;
            }
        }
    }
    void addClass(vector<Class> &classes)
    {
        string id, coachname, dayTime, type;
        bool idExists;
        do
        {
            idExists = false;
            cout << "Enter Class id: ";
            cin >> id;
            for (int i = 0; i < classes.size(); i++)
            {
                if (classes[i].id == id)
                {
                    cout << "Class already exists. Please enter a different ID.\n";
                    idExists = true;
                    break;
                }
            }
        } while (idExists);
        cin.ignore();
        cout << "Enter coach name: ";
        getline(cin, coachname);

        cout << "Enter the type of class: ";
        getline(cin, type);

        cout << "Enter the day and time: ";
        getline(cin, dayTime);

        Class temp;
        temp.id = id;
        temp.coachName = coachname;
        temp.type = type;
        temp.capacity = 0;
        temp.dayTime = string_to_time_t(dayTime);
        classes.push_back(temp);

        cout << "Class has been added successfully\n";
    }
};
#endif