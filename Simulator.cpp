//
// Created by Ahmet Şentürk on 29.10.2018.
//

#include "Simulator.h"
#include "Passenger.h"

Simulator::Simulator(queue<Passenger> _passengers, bool _firstFlight,
                     bool _VIP, bool _onlineTicket, int _numLugCount, int _numSecCount){
    firstFlight = _firstFlight;
    VIP = _VIP;
    onlineTicket = _onlineTicket;
    numLuggageCounters = _numLugCount;
    numSecurityCounters = _numSecCount;
    numOfPassengers = _passengers.size();
    numMissedFlights = 0;
    avgWaitingTime = 0;
    currentTime = !_passengers.empty() ? _passengers.front().exitTime : 0;
    buildEventQueue(_passengers);
    timerTick();
}

void Simulator::buildEventQueue(queue<Passenger> passengers) {
    while (!passengers.empty()) {
        Passenger p = passengers.front();
        p.firstFlight = firstFlight;
        p.event = ArrivingTerminal;
        eventQueue.push(p);
        passengers.pop();
    }
}

void Simulator::timerTick() {
    while(!eventQueue.empty()) {
        while (!eventQueue.empty() && eventQueue.top().exitTime == currentTime) {
            Passenger p = eventQueue.top();
            eventQueue.pop();
            Event event = p.event;
            switch (event) {
                case ArrivingTerminal :
                    if(onlineTicket && (p.onlineTicket == 'N')){
                        if(VIP && (p.VIP == 'V')){
                            if(currentTime>p.flightTime)
                                numMissedFlights++;
                        }else{
                            p.arrivalTimeToQueue = currentTime;
                            securityQueue.push(p);
                        }
                    }else{
                        p.arrivalTimeToQueue = currentTime;
                        luggageQueue.push(p);
                    }
                    break;
                case LeavingLuggage :
                    numLuggageCounters++;
                    if(VIP && (p.VIP == 'V')){
                        avgWaitingTime += currentTime-p.arrivalTime;
                        if(currentTime>p.flightTime)
                            numMissedFlights++;
                    }else{
                        p.arrivalTimeToQueue = currentTime;
                        securityQueue.push(p);
                    }
                    break;
                case LeavingSecurity :
                    numSecurityCounters++;
                    avgWaitingTime += currentTime-p.arrivalTime;
                    if(currentTime>p.flightTime)
                        numMissedFlights++;
                    break;
            }
            securityQueueToCounter();
            luggageQueueToCounter();
        }
        currentTime = eventQueue.top().exitTime;
    }
    calculateResults();
}

void Simulator::luggageQueueToCounter() {
    while(numLuggageCounters>0 && !luggageQueue.empty()){
        Passenger p = luggageQueue.top();
        luggageQueue.pop();
        p.exitTime = currentTime + p.handInTime;
        p.event = LeavingLuggage;
        eventQueue.push(p);
        numLuggageCounters--;
    }
}

void Simulator::securityQueueToCounter() {
    while(numSecurityCounters>0 && !securityQueue.empty()){
        Passenger p = securityQueue.top();
        securityQueue.pop();
        p.exitTime = currentTime + p.securityTime;
        p.event = LeavingSecurity;
        eventQueue.push(p);
        numSecurityCounters--;
    }
}

void Simulator::calculateResults() {
    avgWaitingTime = avgWaitingTime / numOfPassengers;
}