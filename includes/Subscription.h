#ifndef SUBSCRIPTION_H
#define SUBSCRIPTION_H

#pragma once

#include <iostream>
#include <string>

using namespace std;

class Subscription
{
public:
    int id;
    int period;
    int price;
    time_t startDate;
    time_t endDate;
    bool active;
private:

};

#endif