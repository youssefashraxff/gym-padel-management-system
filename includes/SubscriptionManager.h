#ifndef SUBSCRIPTIONMANAGER_H
#define SUBSCRIPTIONMANAGER_H

#pragma once

#include <iostream>
#include <unordered_map>

#include "DataManager.h"
#include "NotificationManager.h"
#include "Subscription.h"
#include "Member.h"

#include <ctime>

#include "../utils/utils.h"
using namespace std;

class SubscriptionManager
{
private:
    DataManager &data_manager;

public:
    unordered_map<string, Subscription> memberSubscription;

    SubscriptionManager(DataManager &data_manager)
        : data_manager(data_manager) {}

    void load_member_subscriptions(Member &loggedInMember, NotificationManager &notification_manager)
    {
        for (const auto &[id, m] : data_manager.membersID)
        {
            auto it = data_manager.subscriptionsID.find(m.subscriptionId);

            if (it != data_manager.subscriptionsID.end())
            {
                Subscription &sub = it->second;

                sub.checkActive();
                if (sub.checkForRenewal())
                {
                    notification_manager.notifySubscriptionExpiry(loggedInMember.id, (sub.endDate - time(nullptr)) / (60 * 60 * 24));
                }
                Subscription::markIdAsUsed(sub.id);

                memberSubscription[m.id] = sub;
            }
        }
    }
    void addSubscription(Member &loggedInMember, bool discount)
    {
        cout << "Enter Subscription Period (Monthly, 3 months, 6 months, Yearly): ";
        int period;
        cin >> period;
        Subscription sub(period, discount);
        loggedInMember.subscriptionId = sub.id;
        data_manager.subscriptionsID[sub.id] = sub;
        data_manager.membersID[loggedInMember.id] = loggedInMember;

        cout << "Subscribed Successfully\n";

        memberSubscription[loggedInMember.id] = sub;
    }
    void removeSubscription(Member &loggedInMember)
    {
        memberSubscription.erase(loggedInMember.id);
        loggedInMember.subscriptionId = -1;
        data_manager.membersID[loggedInMember.id].subscriptionId = -1;
        cout << "Subscription cancelled successfully.\n";
    }
    void showSubscriptionDetails(Member &loggedInMember)
    {
        cout << "\n[Subscription]\n";
        if (loggedInMember.subscriptionId == -1)
        {
            cout << "Not Subscribed" << "\n";
            cout << "Do you want to Subscribe?\n";
            string choice;
            cin >> choice;
            if (choice == "yes" || choice == "YES")
            {
                addSubscription(loggedInMember, false);
            }
            return;
        }
        else
        {
            Subscription &sub = getSubscription(loggedInMember.id);
            cout << "\nPeriod: " << sub.period << "\n";
            cout << "Price: " << sub.price << "\n";
            cout << "Start Date: " << time_t_to_string(sub.startDate) << "\n";
            cout << "End Date: " << time_t_to_string(sub.endDate) << "\n";
            cout << "Status: " << (sub.active ? "Active" : "Inactive") << "\n";
            cout << "Subscription ID: " << sub.id << "\n";

            cout << "[\n1] Cancel your subscription?\n";
            cout << "[2] Renew your subscription?\n";
            cout << "[0] Back\n";

            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                removeSubscription(loggedInMember);
                break;
            case 2:
            {
                Subscription &sub = getSubscription(loggedInMember.id);
                if ((sub.endDate - time(nullptr)) >= 3)
                {
                    cout << "\nCongratulations, you got an early discount rate.\n";
                    addSubscription(loggedInMember, true);
                }
                else
                {
                    addSubscription(loggedInMember, false);
                }
                break;
            }
            case 0:
            {
                cout << "\nBack to main menu\n";
                break;
            }
            }
        }
    }
    Subscription &getSubscription(string memberID)
    {
        return memberSubscription[memberID];
    }
};

#endif