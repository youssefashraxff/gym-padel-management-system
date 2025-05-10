#ifndef COURTBOOKING_H
#define COURTBOOKING_H


#include <iostream>
#include <string>
#include "user.h"

using namespace std;

class CourtBooking {
public:
    string courtID;
    string memberID;
    string location;
    time_t date;
    string time;

    void displayInfo(User& user, const string& username, vector<CourtBooking>& courtBookings) {
    
        if (user.getUserType(username) == "staff") {
            for (const auto& booking : courtBookings) {
                cout << "Court ID: " << booking.courtID << endl;
                cout << "Member ID: " << booking.memberID << endl;
                cout << "Location: " << booking.location << endl;
                cout << "Date: " << time_t_to_string(booking.date) << endl;
                cout << "Time: " << booking.time << endl;
                cout << "------------------------" << endl;
            }
        } else if (user.getUserType(username) == "staff") {
            string memberID = username; // assuming username == memberID
            bool found = false;
            for (const auto& booking : courtBookings) {
                if (booking.memberID == memberID) {
                    cout << "Court ID: " << booking.courtID << endl;
                    cout << "Location: " << booking.location << endl;
                    cout << "Date: " << time_t_to_string(booking.date) << endl;
                    cout << "Time: " << booking.time << endl;
                    cout << "------------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No court bookings found for your account." << endl;
            }
        } else {
            cout << "Unknown role." << endl;
        }
    }
    
};
#endif;