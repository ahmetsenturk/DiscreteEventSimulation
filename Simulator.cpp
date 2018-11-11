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
    currentTime = _passengers.front().exitTime;
    numOfPassengers = _passengers.size();
    numMissedFlights = 0;
    avgWaitingTime = 0;
    buildEventQueue(_passengers);
    timerTick();
}

void Simulator::buildEventQueue(queue<Passenger> passengers) {
    while (!passengers.empty()) {
        Passenger p = passengers.front();
        if(firstFlight)
            p.firstFlight = true;
        else
            p.firstFlight = false;
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
        currentTime++;
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
    float temp = (avgWaitingTime / numOfPassengers) * 1000;
    int withoutDecimals = temp;
    float result = (float(withoutDecimals))/1000;
    avgWaitingTime = result;
}