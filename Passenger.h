//
// Created by Ahmet Şentürk on 28.10.2018.
//

#ifndef CMPE250_PROJECT2_AHMETSENTURK_PASSENGER_H
#define CMPE250_PROJECT2_AHMETSENTURK_PASSENGER_H

#include <iostream>
#include "Event.h"

using namespace std;


class Passenger {
public:
    int arrivalTime;
    int arrivalTimeToQueue;
    int flightTime;
    int handInTime;
    int securityTime;
    int exitTime;
    bool firstFlight;
    char VIP;
    char onlineTicket;
    Event event;
    Passenger(int _arrivalTime, int _flightTime, int _handInTime, int _securityTime, char _VIP, char _onlineTicket);
    Passenger(const Passenger &p);
    Passenger operator=(const Passenger &p);
};


#endif //CMPE250_PROJECT2_AHMETSENTURK_PASSENGER_H
