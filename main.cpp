#include <iostream>

#include "includes/DataManager.h"
#include "includes/ClassManager.h"
#include "includes/CourtBookingManager.h"
#include "includes/SubscriptionManager.h"

#include "utils/json_utils.h"

#include "includes/User.h"
#include "includes/Member.h"
#include "includes/Class.h"
#include "includes/Subscription.h"
#include "includes/CourtBooking.h"
#include "includes/Court.h"
#include "includes/Staff.h"
#include <stack>
using namespace std;

int main()
{
    DataManager dataManager;
    dataManager.loadData();

    ClassManager classManager(dataManager);
    CourtBookingManager courtBookingManager(dataManager);
    SubscriptionManager subscriptionManager(dataManager);

    subscriptionManager.load_member_subscriptions();
    classManager.load_member_classes();
    courtBookingManager.load_member_court_bookings();
Staff s;
s.addClass(dataManager.classes);
    // User temp(dataManager);
    // temp.login();
    // Member loggedInMember = temp.getLoggedInMember();

    // bool running = true;
    // while (running)
    // {
    //     cout << "\n[1] View Profile\n";
    //     cout << "[2] View Subscription\n";
    //     cout << "[3] View Available Classes\n";
    //     cout << "[4] View Available Padel Courts\n";
    //     cout << "[5] View Court Bookings\n";
    //     cout << "[6] View Workout History\n";
    //     cout << "[0] Logout / Exit\n";

    //     int choice;
    //     cout << "\nEnter your choice: ";
    //     cin >> choice;
    //     switch (choice)
    //     {
    //     case 1:
    //         loggedInMember.showProfile();
    //         break;
    //     case 2:
    //         subscriptionManager.showSubscriptionDetails(loggedInMember);
    //         break;
    //     case 3:
    //         cout << "\n[Available Classes]\n";
    //         for (auto c : dataManager.classes)
    //         {
    //             cout << "\nClass : " << c.type << "\n";
    //             cout << "Time: " << c.dayTime << "\n";
    //             cout << "Coach : " << c.coachName << "\n";
    //         }
    //         break;
    //     case 4:
    //         // cout<<"\n[Available Padel Courts]\n";
    //         // for(auto c : dataManager.courts){
    //         //     cout<<"Court ID: "<<c.getId()<<endl;
    //         //     cout<<"Court Type: "<<c.getType()<<endl;
    //         //     cout<<"Court Availability: "<<(c.isAvailable() ? "Available" : "Not Available")<<endl;
    //         // }
    //         break;
    //     case 5:
    //     {
    //         cout << "\n[Your Court Bookings]\n";
    //         stack<CourtBooking> bookings = courtBookingManager.getBookingInfo(loggedInMember.id);
    //         while (!bookings.empty())
    //         {
    //             CourtBooking booking = bookings.top();
    //             bookings.pop();
    //             cout << "Court ID: " << booking.courtID << "\n";
    //             cout << "Booking Time: " << booking.time << "\n";
    //             cout << "Booking Date: " << time_t_to_string(booking.date) << "\n";
    //         }
    //         break;
    //     }
    //     case 6:
    //     {
    //         classManager.show_member_history(loggedInMember.id);
    //         break;
    //     }
    //     case 0:
    //         running = false;
    //         ;
    //     }
    // }
    dataManager.saveData();
}