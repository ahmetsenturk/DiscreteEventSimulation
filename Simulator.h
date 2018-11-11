//
// Created by Ahmet Şentürk on 29.10.2018.
//

#ifndef CMPE250_PROJECT2_AHMETSENTURK_SIMULATOR_H
#define CMPE250_PROJECT2_AHMETSENTURK_SIMULATOR_H

#include <iostream>
#include <queue>
#include "Passenger.h"
#include "Event.h"

using namespace std;

class Simulator {
public:
    struct CompareQueue{
        bool operator()(const Passenger& p1, const Passenger& p2){
            if(p1.firstFlight && p2.firstFlight){
                if(p1.flightTime == p2.flightTime) {
                    return p1.arrivalTime > p2.arrivalTime;
                }else {
                    return p1.flightTime > p2.flightTime;
                }
            }else {
                if(p1.arrivalTimeToQueue == p2.arrivalTimeToQueue){
                    return p1.arrivalTime > p2.arrivalTime;
                }else {
                    return p1.arrivalTimeToQueue > p2.arrivalTimeToQueue;
                }
            }
        }
    };

    struct CompareEvents{
        bool operator()(const Passenger& p1, const Passenger& p2){
            if(p1.exitTime == p2.exitTime){
                if(p1.event == p2.event){
                    return p1.arrivalTime > p2.arrivalTime;
                }else{
                    return p1.event > p2.event;
                }
            }else{
                return p1.exitTime > p2.exitTime;
            }
        }
    };

    priority_queue<Passenger, vector<Passenger>, CompareQueue> luggageQueue;
    priority_queue<Passenger, vector<Passenger>, CompareQueue> securityQueue;
    priority_queue<Passenger, vector<Passenger>, CompareEvents> eventQueue;
    bool firstFlight;
    bool VIP;
    bool onlineTicket;
    int numLuggageCounters;
    int numSecurityCounters;
    float avgWaitingTime;
    int numMissedFlights;
    int currentTime;
    int numOfPassengers;

    Simulator(queue<Passenger> _passengers ,bool _firstFlight, bool _VIP,
              bool _onlineTicket, int _numLugCount, int _numSecCount);
    void timerTick();
    void buildEventQueue(queue<Passenger> passengers);
    void calculateResults();
    void luggageQueueToCounter();
    void securityQueueToCounter();
};


#endif //CMPE250_PROJECT2_AHMETSENTURK_SIMULATOR_H
