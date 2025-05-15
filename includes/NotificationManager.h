#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <stack>
#include <unordered_map>
#include <string>
#include "Notification.h"
#include "DataManager.h"
#include "FileHandler.h"

using namespace std;

class NotificationManager
{
private:
    DataManager &data_manager;
    unordered_map<string, stack<Notification>> memberNotifications;

public:
    NotificationManager(DataManager &data_manager) : data_manager(data_manager) {}

    void load_member_notifications()
    {
        for (Notification n : data_manager.notifications)
        {
            memberNotifications[n.memberId].push(n);
        }
    }
    bool addNotification(const string &memberId, const string &message)
    {
        if (data_manager.membersID.count(memberId))
        {

            if (!memberNotifications[memberId].empty())
            {
                string testMessage = memberNotifications[memberId].top().message;
                if (testMessage == message)
                {
                    return false;
                }
            }
            Notification n(message, memberId);
            memberNotifications[memberId].push(n);
            data_manager.notifications.push_back(n);
            return true;
        }
        return false;
    }

    void notify_Latest_in_waitinglist(string memberID, Class c)
    {
        string msg = "You are added to class " + c.id + "\n"
                                                        "Class type: " +
                     c.type + "\n"
                              "Date: " +
                     time_t_to_string(c.dayTime) + "\n"
                                                   "Coach: " +
                     c.coachName;

        addNotification(memberID, msg);
    }

    void notifySubscriptionExpiry(const string &memberId, int daysLeft)
    {
        string msg = "Subscription expires in " + to_string(daysLeft) +
                     (daysLeft == 1 ? " day" : " days");
        addNotification(memberId, msg);
    }

    void show(const string &memberId)
    {
        if (memberNotifications[memberId].empty())
        {
            cout << "\nNo notifications.\n";
            return;
        }

        cout << "\n[Your Notifications]\n";
        stack<Notification> temp = memberNotifications[memberId];
        while (!temp.empty())
        {
            const auto &notif = temp.top();
            cout << "\n[" << time_t_to_string(notif.timestamp) << "]\n"
                 << notif.message << "\n"
                 << "----------------------------------\n";
            temp.pop();
        }
    }
};

#endif