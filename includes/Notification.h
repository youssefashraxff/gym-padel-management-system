#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <ctime>
#include "../utils/utils.h"

using namespace std;

class Notification {
public:
    enum Type {
        CLASS_BOOKING,
        WAITLIST_UPDATE,
        WAITLIST_PROMOTION,
        SUBSCRIPTION_REMINDER_3DAYS,
        SUBSCRIPTION_REMINDER_1DAY
    };

    Type type;
    string message;
    time_t timestamp;
    string memberId;

    Notification(Type type, const string& message, const string& memberId) 
        : type(type), message(message), timestamp(time(nullptr)), memberId(memberId) {}


    Notification() : type(CLASS_BOOKING), timestamp(0) {}
};

#endif 