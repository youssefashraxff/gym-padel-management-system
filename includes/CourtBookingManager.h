#ifndef COURTBOOKINGMANAGER_H
#define COURTBOOKINGMANAGER_H

#include <iostream>

#include "DataManager.h"
#include "CourtBooking.h"
#include "Court.h"

#include <unordered_map>
#include "stack"

#pragma once
using namespace std;

class CourtBookingManager
{
private:
    DataManager &data_manager;

public:
    unordered_map<string, vector<CourtBooking>> memberCourtBookings;

    CourtBookingManager(DataManager &data_manager)
        : data_manager(data_manager) {}

    void load_member_court_bookings()
    {
        for (const auto &[bookingID, booking] : data_manager.courtBookings)
        {
            memberCourtBookings[booking.memberID].push_back(booking);
        }
    }

    vector<CourtBooking> getBookingInfo(const string &memberID)
    {
        return memberCourtBookings[memberID];
    }

    void addBooking(const string &memberID, CourtBooking c)
    {
        c.memberID = memberID;
        memberCourtBookings[memberID].push_back(c);
        data_manager.courtBookings[c.bookingID] = c;
    }

    void showCourtBookings(string memberID)
    {
        cout << "\n[Court Bookings]\n";
        vector<CourtBooking> cbs = getBookingInfo(memberID);
        for (CourtBooking cb : cbs)
        {
            cout << "\nBooking ID: " << cb.bookingID << "\n";
            cout << "Court ID: " << cb.courtID << "\n";
            cout << "Date: " << cb.date << "\n";
            cout << "Location: " << cb.location << "\n";
            cout << "Time: " << cb.bookingTime << "\n";
        }
    }

    void showAvailability(const vector<Court> &courts)
    {
        bool foundAnyCourt = false;

        string date, location;
        cout << "Enter Location: ";
        cin >> location;
        cout << "Enter Date: ";
        cin >> date;

        for (int i = 0; i < courts.size(); i++)
        {
            if (courts[i].location == location)
            {
                if (courts[i].daySlots.find(date) != courts[i].daySlots.end())
                {
                    auto &timeSlots = courts[i].daySlots.at(date);
                    bool foundSlots = false;

                    cout << "Available slots at " << courts[i].location << " (Court " << courts[i].id << ") on " << date << ":\n";
                    for (const auto &slot : timeSlots)
                    {
                        if (!slot.second)
                        {
                            cout << "- " << slot.first << endl;
                            foundSlots = true;
                            foundAnyCourt = true;
                        }
                    }

                    if (!foundSlots)
                    {
                        cout << "  No available time slots for this court/date.\n";
                    }
                    cout << endl;
                }
            }
        }

        if (!foundAnyCourt)
        {
            cout << "No courts found at " << location << " with availability on " << date << ".\n";
        }
    }

    void bookSlot(vector<Court> &courts, string memberID)
    {
        bool foundCourt = false;
        bool slotBooked = false;

        string date, location, time;
        cout << "Enter Location: ";
        cin >> location;
        cout << "Enter Date: ";
        cin >> date;
        cout << "Enter Time: ";
        cin >> time;

        for (int i = 0; i < courts.size(); i++)
        {
            if (courts[i].location == location)
            {
                if (courts[i].daySlots.find(date) != courts[i].daySlots.end())
                {
                    map<string, bool> &timeSlots = courts[i].daySlots[date];

                    if (timeSlots.find(time) != timeSlots.end())
                    {
                        foundCourt = true;
                        if (!timeSlots[time])
                        {
                            timeSlots[time] = true;
                            cout << "Successfully booked " << time << " at " << location << " (Court " << courts[i].id << ") on " << date << endl;
                            slotBooked = true;
                            CourtBooking cb;
                            cb.bookingID = cb.generateRandomMemberID();
                            cb.courtID = courts[i].id;
                            cb.date = date;
                            cb.location = location;
                            cb.memberID = memberID;
                            cb.bookingTime = time;

                            addBooking(memberID, cb);
                            return;
                        }
                    }
                }
            }
        }

        if (!foundCourt)
        {
            cout << "Invalid location or time slot " << location << endl;
        }
        else
        {
            cout << "No available slots at " << time << " on " << date << " in any court at " << location << endl;
        }
    }

    void cancelCourt(vector<Court> &courts, string memberID)
    {
        showCourtBookings(memberID);

        cout << "Enter The Booking ID you want to cancel: ";
        string id;
        cin >> id;

        vector<CourtBooking> bookings = getBookingInfo(memberID);

        for (CourtBooking cb : bookings)
        {
            if (id == cb.bookingID && checkCancellationTime(cb.date, cb.bookingTime))
            {
                data_manager.courtBookings.erase(id);

                auto &memberBookings = memberCourtBookings[memberID];
                memberBookings.erase(remove_if(memberBookings.begin(), memberBookings.end(), [id](const CourtBooking &cb)
                                               { return cb.bookingID == id; }),
                                     memberBookings.end());

                bool foundBooking = false;
                for (Court &c : courts)
                {
                    if (c.id == cb.courtID)
                    {
                        if (c.daySlots.find(cb.date) != c.daySlots.end())
                        {
                            map<string, bool> &timeSlots = c.daySlots[cb.date];

                            if (timeSlots.find(cb.bookingTime) != timeSlots.end() && timeSlots[cb.bookingTime])
                            {
                                timeSlots[cb.bookingTime] = false; // Mark as available
                                cout << "Successfully cancelled booking at " << cb.bookingTime << " on " << cb.date << " (Court " << c.id << ")\n";
                                foundBooking = true;
                                break;
                            }
                        }
                    }
                }

                if (!foundBooking)
                {
                    cout << "No active booking found at " << cb.bookingTime << " on " << cb.date << "\n";
                }
            }
        }
    }

    bool checkCancellationTime(string date, string myTime)
    {
        time_t bookingTime = string_to_time_t(date + " " + myTime);
        time_t now = time(nullptr);

        double hoursDiff = difftime(bookingTime, now) / 3600.0;

        if (hoursDiff < 3.0)
        {
            cout << "Cannot cancel - must cancel at least 3 hours before.\n";
            return false;
        }
        if (hoursDiff < 0)
        {
            cout << "This booking is already past.\n";
            return false;
        }
        return true;
    }

    void rescheduleSlot(vector<Court> &courts, string oldDate, string oldTime, string newDate, string newTime)
    {
        string courtID;
        cout << "Enter court ID to reschedule: ";
        cin >> courtID;

        time_t now = time(nullptr);
        time_t oldBooking = string_to_time_t(oldDate + " " + oldTime);
        time_t newBooking = string_to_time_t(newDate + " " + newTime);

        double hoursDiff = difftime(oldBooking, now) / 3600.0;
        cout << "Hours until current booking: " << hoursDiff << endl;

        if (hoursDiff < 3.0)
        {
            cout << "Cannot reschedule - must be at least 3 hours before booking time.\n";
            return;
        }

        bool foundCourt = false;
        bool rescheduled = false;

        for (Court &court : courts)
        {
            if (court.id == courtID)
            {
                foundCourt = true;

                if (court.daySlots[oldDate].count(oldTime) &&
                    court.daySlots[oldDate][oldTime])
                {

                    if (court.daySlots[newDate].count(newTime) &&
                        !court.daySlots[newDate][newTime])
                    {

                        court.daySlots[oldDate][oldTime] = false;
                        court.daySlots[newDate][newTime] = true;

                        cout << "Successfully rescheduled Court " << courtID
                             << " from " << oldDate << " " << oldTime
                             << " to " << newDate << " " << newTime << endl;
                        rescheduled = true;
                    }
                    else
                    {
                        cout << "New time slot " << newDate << " " << newTime
                             << " is unavailable.\n";
                    }
                    break;
                }
            }
        }

        if (!foundCourt)
        {
            cout << "Court " << courtID << " not found.\n";
        }
        else if (!rescheduled)
        {
            cout << "No active booking found at " << oldDate << " " << oldTime
                 << " on Court " << courtID << endl;
        }
    }
};

#endif