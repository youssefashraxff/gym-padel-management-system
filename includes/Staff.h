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
    Manager() {}
    Manager(const Staff &s)
    {
        id = s.id;
        name = s.name;
        username = s.username;
        password = s.password;
        role = s.role;
    }
    void topActiveMembersMonthly(const vector<Member> &members, const vector<Class> &classes, int N, const string &targetMonth)
    {
        unordered_map<string, int> active; // memberID -> count

        for (const auto &c : classes)
        {
            // Convert dayTime (time_t) to "YYYY-MM"
            time_t t = c.dayTime;
            tm *ltm = localtime(&t);
            string month = to_string(1900 + ltm->tm_year) + "-" +
                           (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(ltm->tm_mon + 1);

            if (month == targetMonth)
            {
                for (const auto &memberID : c.memberIDs)
                    active[memberID]++;
            }
        }

        // Sort by activity count (highest first)
        vector<pair<string, int>> sorted(active.begin(), active.end());
        sort(sorted.begin(), sorted.end(), [](auto &a, auto &b)
             { return a.second > b.second; });

        cout << "\n[Top " << N << " Active Members in " << targetMonth << "]\n";
        cout << "----------------------------------\n";
        int shown = 0;
        for (auto &p : sorted)
        {
            if (shown >= N)
                break;
            for (const auto &m : members)
            {
                if (m.id == p.first)
                {
                    cout << "Name: " << m.name << "\nID: " << m.id
                         << "\nParticipated in: " << p.second << " activities\n----------------------------------\n";
                    shown++;
                    break;
                }
            }
        }
        if (shown == 0)
            cout << "No members participated in classes in this month.\n";
    }
    void revenueTracking(const vector<Subscription> &subscriptions)
    {
        map<string, double> profit; // month in "YYYY-MM" : revenue

        for (const auto &a : subscriptions)
        {
            if (!a.active)
                continue; // skip inactive

            int durationMonths = 0;
            if (a.period == "Monthly")
                durationMonths = 1;
            else if (a.period == "3 months")
                durationMonths = 3;
            else if (a.period == "6 months")
                durationMonths = 6;
            else if (a.period == "Yearly")
                durationMonths = 12;
            else
                continue; // unknown period, skip

            double monthlyRevenue = a.price / durationMonths;

            // Parse start year and month
            string startYM = time_t_to_string(a.startDate).substr(0, 7); // "YYYY-MM"
            int year = stoi(startYM.substr(0, 4));
            int month = stoi(startYM.substr(5, 2));

            for (int i = 0; i < durationMonths; i++)
            {
                // Build month string
                string ym = to_string(year) + "-" + (month < 10 ? "0" : "") + to_string(month);
                profit[ym] += monthlyRevenue;

                // Advance to next month
                month++;
                if (month > 12)
                {
                    month = 1;
                    year++;
                }
            }
        }
        cout << "Monthly Revenue Report:\n";
        cout << "-----------------------\n";
        cout << fixed << setprecision(2);
        for (const auto &[month, revenue] : profit)
        {
            cout << "Month " << month << ": $" << revenue << "\n";
        }
    }
};
#endif