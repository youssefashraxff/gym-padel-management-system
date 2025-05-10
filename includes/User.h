#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include "Member.h"
#include "Staff.h"
#include "DataManager.h"
// #include "utils.h"

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
    bool getMember(string u, string p){
        for (const auto& [id, member] : dataManager->membersID)
        {
            if (member.username == u && member.password == p)
            {
                loggedInMember = member;
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
                cout << "\nSigned in successfully as " << role << ". Welcome, " << loggedInStaff.name << "!\n";
                return true;
            }
            cout << "Invalid username or password." << endl;
            return false;
        }
        else
        {
            if (getMember(username, password))
            {
                cout << "\nSigned in successfully as " << role << ". Welcome, " << loggedInMember.name << "!\n";
                return true;
            }

            cout << "\nInvalid username or password." << endl;
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
        Member temp(username, password, name, age,-1);
        loggedInMember = temp;
        dataManager->membersID[loggedInMember.id]= loggedInMember;
        cout << "Sign-up successful! \n";
    }

    // LOGIN FUNCTION
    void login()
    {
        string hasAccount;
        cout << "\nDo you have an account? (yes/no): ";
        cin >> hasAccount;

        if (hasAccount == "yes" || hasAccount == "YES")
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            while (!signIn(username, password))
            {
                cout << "\nPlease try again.\n";
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
            }
            cout << "Login successful!\n";
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
    Member getLoggedInMember(){
        return loggedInMember;
    }
};