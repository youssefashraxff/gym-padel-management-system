#include <iostream>

#include "includes/DataManager.h"
#include "includes/ClassManager.h"
#include "includes/CourtBookingManager.h"

#include "utils/json_utils.h"
#include "User.h"
#include "Member.h"
#include "Class.h"
#include "stack"
using namespace std;

int main()
{
    DataManager dataManager;

    CourtBookingManager courtBookingManager(dataManager);

    dataManager.loadData();
    ClassManager classManager(dataManager);

    classManager.load_member_classes();
    courtBookingManager.load_member_court_bookings();

    // Dah Test lel display bta3 el history classes bta3et member mo3yn
    stack<Class> classes = classManager.getWorkout("M001");
    while (!classes.empty())
    {
        Class c = classes.top();
        cout << "\nClass ID: " << c.id << endl;
        cout << "Class Type: " << c.type << endl;
        cout << "Coach Name: " << c.coachName << endl;
        cout << "Capacity: " << c.capacity << endl;
        cout << "Day Time: " << c.dayTime << endl;
        cout << endl;
        classes.pop();
    }

    //

    
    dataManager.saveData();
}