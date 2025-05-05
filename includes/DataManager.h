#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include "FileHandler.h"
#include "Member.h"
#include "Staff.h"
#include "Court.h"
#include "Class.h"
#include "Subscription.h"
#include "CourtBooking.h"

// #include "../utils/json_utils.h"

class DataManager
{

private:
    FileHandler<Member> memberHandler;
    FileHandler<Staff> staffHandler;
    FileHandler<Court> courtHandler;
    FileHandler<Class> classHandler;
    FileHandler<Subscription> subscriptionHandler;
    FileHandler<CourtBooking> courtBookingHandler;

public:
    vector<Member> members;
    vector<Staff> staff;
    vector<Court> courts;
    vector<Class> classes;
    vector<Subscription> subscriptions;
    vector<CourtBooking> courtBookings;

    DataManager() : memberHandler("files/Members.json"),
                    staffHandler("files/Staff.json"),
                    courtHandler("files/Courts.json"),
                    classHandler("files/Classes.json"),
                    subscriptionHandler("files/subscriptions.json"),
                    courtBookingHandler("files/court_bookings.json") {}

    void loadData()
    {

        try
        {
            members = memberHandler.read();
            staff = staffHandler.read();
            courts = courtHandler.read();
            classes = classHandler.read();
            subscriptions = subscriptionHandler.read();
            courtBookings = courtBookingHandler.read();
        }
        catch (const nlohmann::json::exception &e)
        {
            std::cerr << "[JSON Error] Failed to load data: " << e.what() << endl;
        }
    }

    void saveData()
    {

        try
        {
            memberHandler.write(members);
            staffHandler.write(staff);
            courtHandler.write(courts);
            classHandler.write(classes);
            subscriptionHandler.write(subscriptions);
            courtBookingHandler.write(courtBookings);
        }
        catch (const nlohmann::json::exception &e)
        {
            std::cerr << "[JSON Error] Failed to save data: " << e.what() << endl;
        }
        std::cout << "[SAVE] Members to save: " << members.size() << std::endl;
    }
};

#endif