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
#include "Notification.h"

#include <ctime>

class DataManager
{

private:
    FileHandler<Member> memberHandler;
    FileHandler<Staff> staffHandler;
    FileHandler<Court> courtHandler;
    FileHandler<Class> classHandler;
    FileHandler<Subscription> subscriptionHandler;
    FileHandler<CourtBooking> courtBookingHandler;
    FileHandler<Notification> notificationHandler;

public:
    vector<Staff> staff;
    vector<Court> courts;
    vector<Notification> notifications;
    unordered_map<int, Subscription> subscriptionsID;
    unordered_map<string, Member> membersID;
    unordered_map<string, Class> classesID;
    vector<CourtBooking> courtBookings;

    DataManager() : memberHandler("files/Members.json"),
                    staffHandler("files/Staff.json"),
                    courtHandler("files/Courts.json"),
                    classHandler("files/Classes.json"),
                    subscriptionHandler("files/subscriptions.json"),
                    courtBookingHandler("files/court_bookings.json"),
                    notificationHandler("files/notifications.json") {}

    void loadData()
    {
        try
        {
            vector<Member> members = memberHandler.read();
            loadMembers(members);
            staff = staffHandler.read();
            courts = courtHandler.read();
            notifications = notificationHandler.read();
            vector<Class> classes = classHandler.read();
            loadClasses(classes);
            vector<Subscription> subscriptions = subscriptionHandler.read();
            loadSubscriptions(subscriptions);
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
            memberHandler.write(getMembersAsVector());
            staffHandler.write(staff);
            courtHandler.write(courts);
            notificationHandler.write(notifications);
            classHandler.write(getClassesAsVector());
            subscriptionHandler.write(getSubscriptionsAsVector());
            courtBookingHandler.write(courtBookings);
        }
        catch (const nlohmann::json::exception &e)
        {
            std::cerr << "[JSON Error] Failed to save data: " << e.what() << endl;
        }
        std::cout << "\n\n[SAVE] Members to save: " << membersID.size() << std::endl;
    }
    void loadSubscriptions(const vector<Subscription> &subsList)
    {
        for (const auto &sub : subsList)
        {
            subscriptionsID[sub.id] = sub;
        }
    }
    void loadMembers(const vector<Member> &membersList)
    {
        for (const auto &member : membersList)
        {
            membersID[member.id] = member;
            Member::usedIds.insert(member.id);
        }
    }
    void loadClasses(const vector<Class> &classList)
    {
        for (const auto &c : classList)
        {
            classesID[c.id] = c;
        }
    }
    vector<Subscription> getSubscriptionsAsVector() const
    {
        vector<Subscription> result;
        for (const auto &pair : subscriptionsID)
        {
            if (pair.first == 0)
            {
                std::cout << "[DEBUG] WARNING: Subscription ID 0 exists in map!\n";
            }
            result.push_back(pair.second);
        }
        return result;
    }
    vector<Member> getMembersAsVector() const
    {
        vector<Member> result;
        for (const auto &pair : membersID)
        {
            result.push_back(pair.second);
        }
        return result;
    }
    vector<Class> getClassesAsVector() const
    {
        vector<Class> result;
        for (const auto &pair : classesID)
        {
            result.push_back(pair.second);
        }
        return result;
    }
    vector<Class> getAvailableClasses()
    {
        vector<Class> classes = getClassesAsVector();
        vector<Class> temp;

        for (auto it : classes)
        {
            if (it.dayTime > time(nullptr))
            {
                temp.push_back(it);
            }
        }
        return temp;
    }
    Class getClassByID(string chosenClassID)
    {
        return classesID[chosenClassID];
    }
};

#endif