//
// Created by Saleem Hamo on 20/02/2024.
//
#include <string>
#include "../actuators/LED.h"

#ifndef CROSSGUARD_TRAFFICLIGHT_H
#define CROSSGUARD_TRAFFICLIGHT_H

class TrafficLight {

public:
    enum class State {
        OFF,
        RED,
        GREEN

    };

    // Constructor with pins for the red and green LEDs
    TrafficLight(int redPin, int greenPin);

    // Turns the traffic light red
    void turnRed();

    // Turns the traffic light green
    void turnGreen();

    // Turns off all lights
    void turnOff();

    // Changes the state after a timeout
    void changeStateAfterTimeout(int timeoutMillis);

private:
    LED redLED;
    LED greenLED;
    int currentState;  // 0 = off, 1 = red, 2 = green
};


#endif //CROSSGUARD_TRAFFICLIGHT_H
