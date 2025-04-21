#include <iostream>
#include "includes/FileHandler.h"
#include "includes/Member.h"
#include "includes/Class.h"
#include "includes/Court.h"
#include "includes/CourtBooking.h"
#include "includes/Staff.h"
#include "includes/Workout.h"
#include "includes/Utils.h"

using namespace std;

int main() {
    FileHandler<CourtBooking> courtBookingHandler("files/CourtBookings.json");
    FileHandler<Member> memberHandler("files/Members.json");
    FileHandler<Staff> staffHandler("files/Staff.json");
    FileHandler<Workout> workoutHandler("files/Workouts.json");
    FileHandler<Court> courtHandler("files/Courts.json");
    FileHandler<Class> classHandler("files/Classes.json");

    vector<CourtBooking> courtBookings = courtBookingHandler.read();
    vector<Member> members = memberHandler.read();
    vector<Staff> staff = staffHandler.read();
    vector<Workout> workouts = workoutHandler.read();
    vector<Court> courts = courtHandler.read();
    vector<Class> classes = classHandler.read();

    for (const auto& c : courtBookings) {
        cout << c.courtID << " - " << time_t_to_string(c.date) << endl;
    }

    for (const auto& c : members) {
        cout << c.dateOfBirth << " - " << c.id << endl;
    }

    for (const auto& c : staff) {
        cout << c.id << " - " << c.role << endl;
    }

    for (const auto& c : workouts) {
        cout << c.activity << " - " << c.duration << endl;
    }

    for (const auto& c : courts) {
        cout << c.location << " - " << c.id << endl;
    }

    for (const auto& c : classes) {
        cout << c.coachName << " - " << endl;
    }

    courtBookingHandler.write(courtBookings);
    memberHandler.write(members);
    staffHandler.write(staff);
    workoutHandler.write(workouts);
    courtHandler.write(courts);
    classHandler.write(classes);
    
    return 0;
}