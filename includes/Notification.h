#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <ctime>
#include "../utils/utils.h"

using namespace std;

class Notification {
public:
    
    string message;
    time_t timestamp;
    string memberId;

    Notification(const string& message, const string& memberId) 
        : message(message), timestamp(time(nullptr)), memberId(memberId) {}


    Notification() : timestamp(0) {}
};

#endif 