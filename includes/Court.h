#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "json.hpp"
#include "CourtBooking.h"

using json = nlohmann::json;

using namespace std;

class Court {
public:
    string id;
    string location;
    map<string, bool> timeSlots;
    Court(string,string,map<string, bool> );
    bool showAvailability();
    void bookSlot(string time);
    void cancelSlot(string time);
    void rescheduleSlot(string oldT);
};

Court::Court(string id,string location,map<string, bool>timeSlots )
{
this->id=id;
this->location=location;
 for (int hour = 8; hour <= 22; ++hour) 
   {
    stringstream ss;
     ss << setw(2) << setfill('0') << hour << ":00";
     this->timeSlots[ss.str()] = true; // true means available
    }
}

bool Court:: showAvailability()
{
    bool found = false;
    for (auto& slot : timeSlots) //available slots
    {
        if (slot.second) //value true 
        {
            cout << "- " << slot.first << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No available slots.\n";
    }
}

void Court::bookSlot(string time)
 {
    if (timeSlots.find(time) == timeSlots.end()) //time not found
    {
        cout << "Invalid time slot.\n";
        return;
    }
    else if (timeSlots[time])
     {
        timeSlots[time] = false;
        cout << "Slot at " << time << " booked successfully.\n";
    } 
     else {
       cout << "Slot is already booked.\n";
    }
}

void Court::cancelSlot(string time)
 {
    if (timeSlots.find(time) == timeSlots.end()) {
        cout << "Invalid time slot.\n";
        return;
    }

    else if (timeSlots[time]) {
        cout << "This slot is already available.\n";
        return;
    }
    else {
        timeSlots[time] = true;
        cout << "Slot at " << time << " cancelled successfully.\n";
    }
}

void Court::rescheduleSlot(string oldT) {
    
    string newT;
    if (timeSlots.find(oldT) == timeSlots.end() || timeSlots[oldT]) 
    {
        cout << "No valid booking at this time.\n";
        return;
    }
    cout << "Enter new time to reschedule (HH:00): ";
    cin >> newT;

    if (timeSlots.find(newT) == timeSlots.end()) 
    {
        cout << "Invalid new slot.\n";
        return;
    }

    if (!timeSlots[newT]) {
        cout << "New slot is already booked.\n";
        return;
    }

    timeSlots[oldT] = true;
    timeSlots[newT] = false;
    cout << "Booking slot rescheduled from " << oldT << " to " << newT << ".\n";
}

void to_json(json& j, const Court& c) {
    j = json{
        {"id", c.id},
        {"location", c.location},
        {"timeSlots", c.timeSlots}
    };
}

void from_json(const json& j, Court& c) {
    j.at("id").get_to(c.id);
    j.at("location").get_to(c.location);
    j.at("timeSlots").get_to(c.timeSlots);
}