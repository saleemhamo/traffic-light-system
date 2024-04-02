//
// Created by Saleem Hamo on 20/02/2024.
//
#include "models/TrafficLight.h"

/**
 * @class TrafficLight
 * @brief A class to control a traffic light system using LEDs.
 *
 * This class encapsulates the functionality required to control a traffic light
 * system consisting of red, yellow, and green LEDs connected to GPIO pins. It
 * allows for changing the state of the traffic light among red, yellow, green,
 * and off states.
 */
TrafficLight::TrafficLight(int redPin, int greenPin, int yellowPin)
        : redLED(redPin), greenLED(greenPin), yellowLED(yellowPin), currentState(State::OFF) {}

/**
 * @brief Turns the traffic light red by activating the red LED and turning off others.
 */
void TrafficLight::turnRed() {
    greenLED.off();
    redLED.on();
    yellowLED.off();
    currentState = State::RED;
}

/**
 * @brief Turns the traffic light yellow by activating the yellow LED and turning off others.
 */
void TrafficLight::turnYellow() {
    greenLED.off();
    redLED.off();
    yellowLED.on();
    currentState = State::YELLOW;
}

/**
 * @brief Turns the traffic light green by activating the green LED and turning off others.
 */
void TrafficLight::turnGreen() {
    redLED.off();
    greenLED.on();
    yellowLED.off();
    currentState = State::GREEN;
}

/**
 * @brief Turns off all LEDs of the traffic light, setting its state to off.
 */
void TrafficLight::turnOff() {
    redLED.off();
    greenLED.off();
    yellowLED.off();
    currentState = State::OFF;
}