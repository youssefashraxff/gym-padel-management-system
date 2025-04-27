#include <iostream>

#include "includes/DataManager.h"
#include "includes/WorkoutManager.h"

#include "utils/json_utils.h"
#include "User.h"
#include "Member.h"
using namespace std;

int main()
{
    DataManager dataManager;
    WorkoutManager workoutManager;

    dataManager.loadData();
    workoutManager.load_member_bookings(dataManager);

    cout<<"\n\n"<<workoutManager.memberWorkouts["M002"].top()<<"\n\n";

    // dataManager.workoutManager.l
    // User u(dataManager);
    // u.login();

    dataManager.saveData();
}