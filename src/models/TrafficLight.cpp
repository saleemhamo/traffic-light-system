//
// Created by Saleem Hamo on 20/02/2024.
//
#include "models/TrafficLight.h"

TrafficLight::TrafficLight(int redPin, int greenPin) : redLED(redPin), greenLED(greenPin), currentState(State::OFF) {}

void TrafficLight::turnRed() {
    greenLED.off();
    redLED.on();
    currentState = State::RED;
}

void TrafficLight::turnGreen() {
    redLED.off();
    greenLED.on();
    currentState = State::GREEN;
}

void TrafficLight::turnOff() {
    redLED.off();
    greenLED.off();
    currentState = State::OFF;
}