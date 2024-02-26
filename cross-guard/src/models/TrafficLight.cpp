//
// Created by Saleem Hamo on 20/02/2024.
//
#include "TrafficLight.h"
#include <unistd.h>  // For sleep()

TrafficLight::TrafficLight(int redPin, int greenPin) : redLED(redPin), greenLED(greenPin), currentState(0) {}

void TrafficLight::turnRed() {
    greenLED.off();
    redLED.on();
    currentState = 1;
}

void TrafficLight::turnGreen() {
    redLED.off();
    greenLED.on();
    currentState = 2;
}

void TrafficLight::turnOff() {
    redLED.off();
    greenLED.off();
    currentState = 0;
}

void TrafficLight::changeStateAfterTimeout(int timeoutMillis) {
//    TODO
//    sleep(timeoutMillis);
//    if (newState == "RED") {
//        turnRed();
//    } else if (newState == "GREEN") {
//        turnGreen();
//    } else {
//        turnOff();
//    }
}