#ifndef COURTBOOKINGMANAGER_H
#define COURTBOOKINGMANAGER_H

#include <iostream>

#include"DataManager.h"
#include "CourtBooking.h"

#include "map"
#include "stack"

#pragma once
using namespace std;

class CourtBookingManager
{
private:
DataManager data_manager;
public:
    map<string, stack<CourtBooking>> memberCourtBookings;

    CourtBookingManager(DataManager &data_manager){
        this->data_manager=data_manager;
    }

    void load_member_court_bookings(){
        for(int i = 0 ;i<data_manager.courtBookings.size();i++){
            string member_ID = data_manager.courtBookings.at(i).memberID;
            memberCourtBookings[member_ID].push(data_manager.courtBookings.at(i));
        }
    }
    stack<CourtBooking> getBookingInfo(string memberID){
        return memberCourtBookings[memberID];
    }
    void addBooking(string memberID,CourtBooking c){
        c.memberID=memberID;
        memberCourtBookings[memberID].push(c);
        data_manager.courtBookings.push_back(c);
    }



};

#endif