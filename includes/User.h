
#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "Member.h"
#include "Staff.h"
#include "DataManager.h"
#include "../utils/utils.h"

using namespace std;
class User
{
private:
    DataManager *dataManager;

    Staff loggedInStaff;
    Member loggedInMember;

public:
    User(DataManager &d)
    {
        dataManager = &d;
    }

    // IDENTIFING THE ROLE FROM USERNAME
    string getUserType(const string &username)
    {
        if (username.find("staff_") == 0)
            return "staff";
        return "member";
    }
    bool getMember(string u, string p)
    {
        for (int i = 0; i < dataManager->members.size(); i++)
        {
            if (dataManager->members[i].username == u && dataManager->members[i].password == p)
            {
                loggedInMember = dataManager->members[i];
                return true;
            }
        }
        return false;
    }

    bool getStaff(string username)
    {
        for (int i = 0; i < dataManager->staff.size(); i++)
        {
            if (dataManager->staff.at(i).username == username)
            {
                loggedInStaff = dataManager->staff.at(i);
                return true;
            }
        }
        return false;
    }
    // SIGN-IN FUNCTION
    bool signIn(const string &username, const string &password)
    {
        string role = getUserType(username);
        if (role == "staff_")
        {
            if (getStaff(username))
            {
                cout << "Signed in successfully as " << role << ". Welcome, " << loggedInStaff.name << "!\n";
                return true;
            }
            cout << "Invalid username or password." << endl;
            return false;
        }
        else
        {
            if (getMember(username, password))
            {
                cout << "Signed in successfully as " << role << ". Welcome, " << loggedInMember.name << "!\n";
                return true;
            }

            cout << "Invalid username or password." << endl;
            return false;
        }
    }

    // SIGN-UP FUNCTION
    void signUp()
    {
        string username, password, name;
        int age;

        cout << "Enter a new username : ";
        cin >> username;

        cout << "Enter a password (at least 8 characters): ";
        cin >> password;

        cout << "Enter your full name: ";
        cin.ignore();
        getline(cin, name); // accept spaces

        cout << "Enter your Age: ";
        cin >> age;
        Member loggedInMember(username, password, name, age);
        dataManager->members.push_back(loggedInMember);
        cout << "Sign-up successful! \n";
    }

    // LOGIN FUNCTION
    void login()
    {
        string hasAccount;
        cout << "Do you have an account? (yes/no): ";
        cin >> hasAccount;

        if (hasAccount == "yes" || hasAccount == "YES")
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            signIn(username, password);
        }
        else if (hasAccount == "no" || hasAccount == "NO")
        {
            signUp();
        }
        else
        {
            cout << "Invalid input. Please type 'yes' or 'no'.\n";
        }
    }
};