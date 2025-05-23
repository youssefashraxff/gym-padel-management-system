#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <unordered_set>

using namespace std;

class Subscription
{
private:
    static unordered_set<int> usedIds;

    int generateUniqueId()
    {
        int newId;
        do
        {
            newId = rand() % 200 + 100;
        } while (usedIds.find(newId) != usedIds.end());
        usedIds.insert(newId);
        return newId;
    }

public:
    int id;
    string period;
    int price = 500;
    time_t startDate;
    time_t endDate;
    bool active;

    Subscription(int period, bool discount) : active(true)
    {
        startDate = time(nullptr);
        tm startTm = *localtime(&startDate);
        id = generateUniqueId();
        if (period == 1)
        {
            this->period = "Monthly";
            startTm.tm_mon += 1;
            if (discount)
            {
                price *= 0.8;
            }
            price *= 1;
        }
        else if (period == 3)
        {
            this->period = "3 months";
            startTm.tm_mon += 3;
            if (discount)
            {
                price = (price * 3 - 300) * 0.8;
            }
            price = price * 3 - 300;
        }
        else if (period == 6)
        {
            this->period = "6 months";
            startTm.tm_mon += 6;
            if (discount)
            {
                price = (price * 6 - 600) * 0.8;
            }
            price = price * 6 - 600;
        }
        else if (period == 12)
        {
            this->period = "Yearly";
            startTm.tm_mon += 12;
            if (discount)
            {
                price = (price * 12 - 1200) * 0.8;
            }
            price = price * 12 - 1200;
        }
        else
        {
            cerr << "Invalid subscription period: " << period << endl;
            price = 0;
            active = false;
        }
        endDate = mktime(&startTm);
    }
    Subscription() {}

    void checkActive()
    {
        time_t currentTime = time(nullptr);
        if (difftime(currentTime, endDate) > 0 && active == true)
        {
            active = false;
        }
    }
    bool checkForRenewal()
    {
        time_t currentTime = time(nullptr);
        double daysLeft = difftime(endDate, currentTime) / (60 * 60 * 24);

        return active && daysLeft <= 3 && daysLeft >= 0;
    }
    static void markIdAsUsed(int existingId)
    {
        usedIds.insert(existingId);
    }
};
inline unordered_set<int> Subscription::usedIds;
#endif