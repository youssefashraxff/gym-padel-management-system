#include <iostream>

#include "includes/DataManager.h"
#include "includes/WorkoutManager.h"
#include "includes/CourtBookingManager.h"

#include "includes/Workout.h"

#include "utils/json_utils.h"
#include "User.h"
#include "Member.h"

#include "stack"
using namespace std;

int main()
{
    DataManager dataManager;
    
    WorkoutManager workoutManager(dataManager);
    CourtBookingManager courtBookingManager(dataManager);

    dataManager.loadData();

    workoutManager.load_member_workouts();
    courtBookingManager.load_member_court_bookings();
    
    
    dataManager.saveData();
}