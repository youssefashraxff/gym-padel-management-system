#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <vector>
#include "FileHandler.h"
#include "Member.h"
#include "Staff.h"
#include "Workout.h"
#include "Court.h"
#include "Class.h"
#include "Subscription.h"
#include "CourtBooking.h"

class DataManager {
public:
    
    vector<Member> members;
    vector<Staff> staff;
    vector<Workout> workouts;
    vector<Court> courts;
    vector<Class> classes;
    vector<Subscription> subscriptions;
    vector<CourtBooking> courtBookings;

    DataManager() :
        memberHandler("files/members.json"),
        staffHandler("files/staff.json"),
        workoutHandler("files/workouts.json"),
        courtHandler("files/courts.json"),
        classHandler("files/classes.json"),
        subscriptionHandler("files/subscriptions.json"),
        courtBookingHandler("files/court_bookings.json")
    {
        loadData();
    }

    ~DataManager() {
        saveData();
    }

    void loadData() {
        members = memberHandler.read();
        staff = staffHandler.read();
        workouts = workoutHandler.read();
        courts = courtHandler.read();
        classes = classHandler.read();
        subscriptions = subscriptionHandler.read();
        courtBookings = courtBookingHandler.read();
    }

    void saveData() {
        memberHandler.write(members);
        staffHandler.write(staff);
        workoutHandler.write(workouts);
        courtHandler.write(courts);
        classHandler.write(classes);
        subscriptionHandler.write(subscriptions);
        courtBookingHandler.write(courtBookings);
    }

private:
    FileHandler<Member> memberHandler;
    FileHandler<Staff> staffHandler;
    FileHandler<Workout> workoutHandler;
    FileHandler<Court> courtHandler;
    FileHandler<Class> classHandler;
    FileHandler<Subscription> subscriptionHandler;
    FileHandler<CourtBooking> courtBookingHandler;
};

#endif 