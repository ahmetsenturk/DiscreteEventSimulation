//
// Created by Ahmet Şentürk on 28.10.2018.
//

#include "Passenger.h"
using namespace std;

Passenger::Passenger(int _arrivalTime, int _flightTime, int _handInTime, int _securityTime, char _VIP, char _onlineTicket) {
    arrivalTime = _arrivalTime;
    exitTime = _arrivalTime;
    flightTime = _flightTime;
    handInTime = _handInTime;
    securityTime = _securityTime;
    VIP = _VIP;
    onlineTicket = _onlineTicket;
}

Passenger::Passenger(const Passenger &p) {
    arrivalTime = p.arrivalTime;
    arrivalTimeToQueue = p.arrivalTimeToQueue;
    exitTime = p.exitTime;
    flightTime = p.flightTime;
    handInTime = p.handInTime;
    securityTime = p.securityTime;
    firstFlight = p.firstFlight;
    VIP = p.VIP;
    onlineTicket = p.onlineTicket;
    event = p.event;
}

Passenger Passenger::operator=(const Passenger &p) {
    arrivalTime = p.arrivalTime;
    arrivalTimeToQueue = p.arrivalTimeToQueue;
    exitTime = p.exitTime;
    flightTime = p.flightTime;
    handInTime = p.handInTime;
    securityTime = p.securityTime;
    firstFlight = p.firstFlight;
    VIP = p.VIP;
    onlineTicket = p.onlineTicket;
    event = p.event;
    return *this;
}

inline ostream& operator<<(ostream &output, const Passenger &P) {
    output << "Arrival time: " << P.arrivalTime << endl <<
           "Flight time: "<< P.flightTime << endl << "Hand in time: "<< P.handInTime <<
           "Security time: "<< P.securityTime << endl << "VIP? "<< P.VIP<< endl<< "Luggage? "<< P.onlineTicket;
    return output;
}