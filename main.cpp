#include <iostream>

#include "includes/DataManager.h"
#include "includes/ClassManager.h"
#include "includes/CourtBookingManager.h"
#include "includes/SubscriptionManager.h"
#include "includes/NotificationManager.h"

#include "utils/json_utils.h"

#include "includes/User.h"
#include "includes/Member.h"
#include "includes/Class.h"
#include "includes/Subscription.h"
#include "includes/CourtBooking.h"
#include "includes/Court.h"
// #include "includes/Staff.h"
#include <stack>
using namespace std;

int main()
{
    DataManager dataManager;
    dataManager.loadData();

    ClassManager classManager(dataManager);
    CourtBookingManager courtBookingManager(dataManager);
    NotificationManager notificationManager(dataManager);
    SubscriptionManager subscriptionManager(dataManager);

    classManager.load_member_classes();
    courtBookingManager.load_member_court_bookings();
    notificationManager.load_member_notifications();
    subscriptionManager.load_member_subscriptions(notificationManager);

    User temp(dataManager);
    temp.login();

    if (!temp.getLoggedInMember().id.empty())
    {
        // A member is logged in
        Member loggedInMember = temp.getLoggedInMember();
        bool running = true;
        while (running)
        {
            cout << "\n[1] Gym\n[2] Padel\n[0] Exit\n";
            cout << "\nEnter Choice\n";
            int menuChoice;
            cin >> menuChoice;
            switch (menuChoice)
            {
            case 1:
            {
                // Gym Menu
                bool secondRunning = true;
                while (secondRunning)
                {
                    cout << "\n[1] View Profile\n";
                    cout << "[2] View Subscription\n";
                    cout << "[3] View Available Classes\n";
                    cout << "[4] Cancel Pending Classes\n";
                    cout << "[5] View Workout History\n";
                    cout << "[6] View Notifications\n";
                    cout << "[0] Logout / Exit\n";

                    int choice;
                    cout << "\nEnter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                    {
                        cout << "\n\nTest 1\n\n";
                        loggedInMember.showProfile();
                        break;
                    }
                    case 2:
                    {
                        cout << "\n\nTest 2\n\n";
                        subscriptionManager.showSubscriptionDetails(loggedInMember);
                        break;
                    }
                    case 3:
                    {
                        for (auto it : dataManager.getAvailableClasses())
                        {
                            cout << "\nID: " << it.id << "\n";
                            cout << "Class : " << it.type << "\n";
                            cout << "Date: " << time_t_to_string(it.dayTime) << "\n";
                            cout << "Coach : " << it.coachName << "\n";
                        }
                        cout << "\nDo you want to book a class? (yes or no)\n";
                        string choice_sec;
                        cin >> choice_sec;

                        if (choice_sec == "yes")
                        {
                            if (subscriptionManager.getSubscription(loggedInMember.id).active == true)
                            {
                                cout << "\n Enter class ID: ";
                                string classID;
                                cin >> classID;
                                Class *chosenClass = &dataManager.classesID[classID];

                                if (chosenClass->addMember(loggedInMember.id))
                                {
                                    classManager.addWorkout(loggedInMember.id, chosenClass);
                                }
                            }
                            else
                            {
                                subscriptionManager.showSubscriptionDetails(loggedInMember);
                            }
                        }
                        break;
                    }
                    case 4:
                    {
                        classManager.show_member_pending_classes(loggedInMember.id);
                        cout << "Enter class Id you want to cancel: ";
                        string classId_forCancel;
                        cin >> classId_forCancel;

                        Class chosenClass = dataManager.getClassByID(classId_forCancel);
                        notificationManager.notify_Latest_in_waitinglist(chosenClass.waitlist.front(), chosenClass);
                        chosenClass.removeMember(loggedInMember.id);
                        classManager.removeWorkout(loggedInMember.id, &chosenClass);
                        dataManager.classesID[chosenClass.id] = chosenClass;

                        break;
                    }
                    case 5:
                    {
                        classManager.show_member_history(loggedInMember.id);
                        break;
                    }
                    case 6:
                    {
                        notificationManager.show(loggedInMember.id);
                    }
                    case 0:
                    {
                        secondRunning = false;
                        break;
                    }
                    }
                }
                break;
            }
            case 2:
            {
                bool secondRunning = true;
                while (secondRunning)
                {
                    cout << "\n[1] Show Available Courts\n";
                    cout << "[2] Book Court\n";
                    cout << "[3] Show Court Bookings\n";
                    cout << "[4] Reschedule Slot\n";
                    cout << "[5] Cancel Slot\n";
                    cout << "[0] Logout / Exit\n";

                    int choice;
                    cout << "\nEnter your choice: ";
                    cin >> choice;

                    switch (choice)
                    {
                    case 1:
                        courtBookingManager.showAvailability(dataManager.courts);
                        break;
                    case 2:
                        courtBookingManager.bookSlot(dataManager.courts, loggedInMember.id);
                        break;
                    case 3:
                        courtBookingManager.showCourtBookings(loggedInMember.id);
                        break;
                    case 4:

                        break;
                    case 5:
                        courtBookingManager.cancelCourt(dataManager.courts, loggedInMember.id);
                        break;
                    case 0:
                        secondRunning = false;
                        break;
                    default:
                        cout << "Invalid choice. Try again.\n";
                        break;
                    }
                }
            }
            break;
            case 0:
                running = false;
                break;
            default:
                break;
            }
        }
    }
    else if (!temp.getLoggedInStaff().id.empty() && temp.getLoggedInStaff().role == "Coach")
    {
        // A staff (coach or manager) is logged in
        Coach loggedInCoach(temp.getLoggedInStaff());

        bool secondRunning = true;
        while (secondRunning)
        {
            cout << "\n[1] View Profile\n";
            cout << "[2] Search Member Info\n";
            cout << "[3] View Assigned Classes\n";
            cout << "[4] Add Class\n";
            cout << "[5] Remove Class\n";
            cout << "[0] Logout / Exit\n";

            int choice;
            cout << "\nEnter your choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                loggedInCoach.showProfile();
                break;
            case 2:
                loggedInCoach.searchMemberInfo(dataManager.membersUsername);
                break;
            case 3:
            {
                loggedInCoach.viewClasses(dataManager.classesByCoachID, dataManager.membersID);
                break;
            }
            case 4:
                loggedInCoach.addClass(dataManager.classesID);
                break;
            case 5:
                loggedInCoach.removeClass(dataManager.classesID);
                break;
            case 0:
                secondRunning = false;
                break;
            default:
                cout << "Invalid choice.\n";
                break;
            }
        }
    }
    else if (!temp.getLoggedInStaff().id.empty() && temp.getLoggedInStaff().role == "Manager")
    {
        Manager loggedInManager(temp.getLoggedInStaff());
        cout << "\nGenerate Report\n";
        loggedInManager.topActiveMembersMonthly(dataManager.getMembersAsVector(), dataManager.getClassesAsVector(), 3, "2025-08");
        loggedInManager.revenueTracking(dataManager.getSubscriptionsAsVector());
    }
    dataManager.saveData();
}
