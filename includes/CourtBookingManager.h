#ifndef COURTBOOKINGMANAGER_H
#define COURTBOOKINGMANAGER_H

#include <iostream>

#include "DataManager.h"
#include "CourtBooking.h"
#include "Court.h"

#include <unordered_map>
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
                            cb.bookingID = cb.generateRandomBookingID();
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
            if (id == cb.bookingID && check3hoursDiff(cb.date, cb.bookingTime))
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

    bool check3hoursDiff(string date, string myTime)
    {
        time_t bookingTime = string_to_time_t(date + " " + myTime);
        time_t now = time(nullptr);

        double hoursDiff = difftime(bookingTime, now) / 3600.0;

        if (hoursDiff < 3.0)
        {
            cout << "Cannot Cancel or Reschedule- must be at least 3 hours before.\n";
            return false;
        }
        if (hoursDiff < 0)
        {
            cout << "This booking is already past.\n";
            return false;
        }
        return true;
    }

    void rescheduleSlot(vector<Court>& courts, string memberID)
    {
        showCourtBookings(memberID);

        cout << "Enter the Booking ID you want to reschedule: ";
        string bookingID;
        cin >> bookingID;

        vector<CourtBooking> bookings = getBookingInfo(memberID);
        CourtBooking* targetBooking = nullptr;

        for (CourtBooking& cb : bookings)
        {
            if (cb.bookingID == bookingID)
            {
                targetBooking = &cb;
                break;
            }
        }

        if (!targetBooking)
        {
            cout << "Booking ID not found.\n";
            return;
        }

        if (!check3hoursDiff(targetBooking->date, targetBooking->bookingTime))
        {
            return;
        }

        string newDate, newTime;
        cout << "Enter new date (YYYY-MM-DD): ";
        cin >> newDate;
        cout << "Enter new time (HH:MM): ";
        cin >> newTime;

        for (Court& court : courts)
        {
            if (court.id == targetBooking->courtID)
            {
                if (court.daySlots[newDate].count(newTime) && !court.daySlots[newDate][newTime])
                {
                    court.daySlots[targetBooking->date][targetBooking->bookingTime] = false;
                    court.daySlots[newDate][newTime] = true;

                    targetBooking->date = newDate;
                    targetBooking->bookingTime = newTime;

                    data_manager.courtBookings[bookingID] = *targetBooking;
                    for (CourtBooking& cb : memberCourtBookings[memberID])
                    {
                        if (cb.bookingID == bookingID)
                        {
                            cb = *targetBooking;
                            break;
                        }
                    }

                    cout << "Successfully rescheduled booking to " << newDate << " " << newTime << " on Court " << court.id << ".\n";
                    return;
                }
                else
                {
                    cout << "New time slot " << newDate << " " << newTime << " is unavailable.\n";
                    return;
                }
            }
        }

        cout << "Court " << targetBooking->courtID << " not found.\n";
    }

};

#endif