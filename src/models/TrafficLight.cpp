//
// Created by Saleem Hamo on 20/02/2024.
//
#include "models/TrafficLight.h"

//TrafficLight::TrafficLight(int redPin, int greenPin) : redLED(redPin), greenLED(greenPin), currentState(State::OFF) {}

TrafficLight::TrafficLight(int redPin, int greenPin, int yellowPin) : redLED(redPin), greenLED(greenPin),
                                                                      yellowLED(yellowPin), currentState(State::OFF) {}

void TrafficLight::turnRed() {
    greenLED.off();
    redLED.on();
    yellowLED.off();
    currentState = State::RED;
}

void TrafficLight::turnYellow() {
    greenLED.off();
    redLED.off();
    yellowLED.on();
    currentState = State::YELLOW;
}

void TrafficLight::turnGreen() {
    redLED.off();
    greenLED.on();
    yellowLED.off();
    currentState = State::GREEN;
}

void TrafficLight::turnOff() {
    redLED.off();
    greenLED.off();
    yellowLED.off();
    currentState = State::OFF;
}