#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <queue>
#include "json.hpp"
#include "Utils.h"

using json = nlohmann::json;
using namespace std;
class User {
    private:
        string username;
        string password;
    public:
    User(string u,string p) {
        username = u;
        password = p;
    }
    string getUsername() const {
        return username;
    }

    void setUsername(const string& name) {
        username = name;
    }
    string getPassword() const {
        return password;
    }

    void setPassword(const string& pass) {
        password = pass;
    }
};
map<string, User*> users; //Store both Staff and Member with full data

// IDENTIFING THE ROLE FROM USERNAME
string getUserType(const string& username) {
    if (username.find("member_") == 0) return "member";
    if (username.find("staff_") == 0) return "staff";
    return "invalid";
}
//SIGN-IN FUNCTION
bool signIn(const string& username, const string& password) {
    auto it = users.find(username);
    if (it != users.end() && it->second->getPassword() == password) {
        string role = getUserType(username);
        cout << "Signed in successfully as " << role << ". Welcome, " << it->second->getUsername() << "!\n";
        return true;
    }
    cout << "Invalid username or password."<<endl;
    return false;
}

//SIGN-UP FUNCTION
void signUp() {
    string username, password, name;
    struct tm dobStruct = {};
    time_t dob;

    while (true) {
        cout << "Enter a new username (must start with 'member_'): ";
        cin >> username;

        string userType = getUserType(username);
        if (userType != "member") {
            cout << "Invalid username. It must start with 'member_'.\n";
            continue;
        }

        if (users.find(username) != users.end()) {
            cout << "This username is already taken.\n";
            continue;
        }

        break; // valid username
    }
    while (true) {
        cout << "Enter a password (at least 8 characters): ";
        cin >> password;
        if (password.length() < 8) {
            cout << "Password is too short. Try again.\n";
        } else {
            break;
        }
    }
    cout << "Enter your full name: ";
    cin.ignore();
    getline(cin, name);//accept spaces

    cout << "Enter your date of birth (YYYY MM DD): ";
    cin >> dobStruct.tm_year >> dobStruct.tm_mon >> dobStruct.tm_mday;
    dobStruct.tm_year -= 1900;
    dobStruct.tm_mon -= 1;
    dob = mktime(&dobStruct);

    users[username] = new Member(username, password, name, dob);
    cout << "Sign-up successful! You can now sign in.\n";
}

// LOGIN FUNCTION
void login() {
    string hasAccount;
    cout << "Do you have an account? (yes/no): ";
    cin >> hasAccount;

    if (hasAccount == "yes"||hasAccount=="YES") {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        signIn(username, password);
    } else if (hasAccount == "no"||hasAccount=="NO") {
        signUp();
    } else {
        cout << "Invalid input. Please type 'yes' or 'no'.\n";
    }
}

//READ FROM FILES
void to_json(json& j, const User& u) {
        j = json{
            {"username", u.getUsername()},
            {"password", u.getPassword()}
        };
    }

//WRITE INTO FILES
void from_json(const json& j, User& u) {
        string username, pass;
        j.at("username").get_to(username);
        j.at("password").get_to(pass);
    
        u.setUsername(username);
        u.setPassword(pass);
    }