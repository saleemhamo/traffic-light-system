//
// Created by Saleem Hamo on 20/02/2024.
//
#include <string>
#include "actuators/LED.h"

#ifndef CROSSGUARD_TRAFFICLIGHT_H
#define CROSSGUARD_TRAFFICLIGHT_H

class TrafficLight {

public:
    enum class State {
        OFF,
        RED,
        GREEN,
        YELLOW

    };

    TrafficLight(int redPin, int greenPin);

    TrafficLight(int redPin, int greenPin, int yellowPin);


    void turnRed();

    void turnGreen();

    void turnYellow();

    void turnOff();

private:
    LED redLED;
    LED greenLED;
    LED yellowLED;
    State currentState;  // 0 = off, 1 = red, 2 = green
};


#endif //CROSSGUARD_TRAFFICLIGHT_H
