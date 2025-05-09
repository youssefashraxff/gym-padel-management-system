#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <stack>
#include <unordered_map>
#include <string>
#include "Notification.h"
#include "DataManager.h"
#include "FileHandler.h"

using namespace std;

class NotificationManager {
private:
    DataManager& dataManager;
    unordered_map<string, stack<Notification>> notifications;
    FileHandler<Notification> fileHandler;

public:
    NotificationManager(DataManager& dm) 
        : dataManager(dm), fileHandler("files/notifications.json") {
        
        vector<Notification> loadedNotifs = fileHandler.read();
        for (const auto& notif : loadedNotifs) {
            if (dataManager.membersID.find(notif.memberId) != dataManager.membersID.end()) {
                notifications[notif.memberId].push(notif);
            }
        }
    }

   
    void saveAllNotifications() {
        vector<Notification> allNotifs;
        for (const auto& [memberId, memberStack] : notifications) {
            stack<Notification> temp = memberStack;
            while (!temp.empty()) {
                allNotifs.push_back(temp.top());
                temp.pop();
            }
        }
        fileHandler.write(allNotifs);
    }

    void addNotification(const string& memberId, const string& message, Notification::Type type) {
        if (dataManager.membersID.find(memberId) != dataManager.membersID.end()) {
            notifications[memberId].push(Notification(type, message, memberId));
        }
    }

    void notifyClassBooking(const string& memberId, const string& classType, 
                          const string& coachName, const string& dayTime) {
        string msg = "Class Booking Confirmed!\n"
                    "Class: " + classType + "\n"
                    "Coach: " + coachName + "\n"
                    "Time: " + dayTime;
        addNotification(memberId, msg, Notification::CLASS_BOOKING);
    }

    void notifyWaitlist(const string& memberId, const string& classType, 
                       const string& coachName, const string& dayTime) {
        string msg = "Added to Waitlist:\n"
                    "Class: " + classType + "\n"
                    "Coach: " + coachName + "\n"
                    "Time: " + dayTime;
        addNotification(memberId, msg, Notification::WAITLIST_UPDATE);
    }

    void notifySubscriptionExpiry(const string& memberId, int daysLeft) {
        if (daysLeft <= 0) return;
        
        string msg = "Subscription expires in " + to_string(daysLeft) + 
                    (daysLeft == 1 ? " day" : " days");
        addNotification(memberId, msg, 
                       daysLeft == 1 ? Notification::SUBSCRIPTION_REMINDER_1DAY 
                                   : Notification::SUBSCRIPTION_REMINDER_3DAYS);
    }

    void show(const string& memberId) {
        if (notifications[memberId].empty()) {
            cout << "\nNo notifications.\n";
            return;
        }

        cout << "\n[Your Notifications]\n";
        stack<Notification> temp = notifications[memberId];
        while (!temp.empty()) {
            const auto& notif = temp.top();
            cout << "\n[" << time_t_to_string(notif.timestamp) << "]\n"
                 << notif.message << "\n"
                 << "----------------------------------\n";
            temp.pop();
        }
    }
};

#endif