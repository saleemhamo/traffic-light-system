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

/**
 * @brief Constructor for initializing the TrafficLight with all three LEDs.
 * This constructor initializes a traffic light with separate LEDs for red, green, and yellow colors. Each LED is 
 * connected to a specific GPIO pin, which is passed to the LED's constructor for initialization. The initial state 
 * of the traffic light is set to OFF, ensuring that all LEDs are deactivated at the start.
 * @param redPin Pin for the red LED.
 * @param greenPin Pin for the green LED.
 * @param yellowPin Pin for the yellow LED.
 */

TrafficLight::TrafficLight(int redPin, int greenPin, int yellowPin)
        : redLED(redPin), greenLED(greenPin), yellowLED(yellowPin), currentState(State::OFF) {}

/**
 * @brief Turns the traffic light red by activating the red LED and turning off others.
 * This method changes the traffic light's state to RED. It ensures that the red LED is turned on while the 
 * green and yellow LEDs are turned off to prevent any conflicting signals. This state change reflects the 
 * typical behavior of a traffic light controlling traffic at an intersection.
 */
void TrafficLight::turnRed() {
    greenLED.off();
    redLED.on();
    yellowLED.off();
    currentState = State::RED;
}

/**
 * @brief Activates the yellow LED and deactivates other LEDs.
 *
 * This method changes the traffic light's state to YELLOW. The yellow LED is turned on, and both the red 
 * and green LEDs are turned off. The activation of the yellow light typically signals that the traffic light 
 * will soon change to red, preparing drivers to stop.
 */
void TrafficLight::turnYellow() {
    greenLED.off();
    redLED.off();
    yellowLED.on();
    currentState = State::YELLOW;
}

/**
 * @brief Activates the green LED and deactivates other LEDs.
 *
 * This method changes the traffic light's state to GREEN, allowing traffic to proceed through the intersection.
 * The green LED is activated, and both the red and yellow LEDs are deactivated. This ensures clear signaling
 * without any ambiguity for the drivers.
 */
void TrafficLight::turnGreen() {
    redLED.off();
    greenLED.on();
    yellowLED.off();
    currentState = State::GREEN;
}

/**
 * @brief Deactivates all LEDs, setting the traffic light state to OFF.
 *
 * This method sets the traffic light's state to OFF, turning off all LEDs. This state might be used during times 
 * of low traffic demand or specific traffic management scenarios. Turning off the lights ensures power savings 
 * and can also be part of safety protocols during emergencies or maintenance.
 */
void TrafficLight::turnOff() {
    redLED.off();
    greenLED.off();
    yellowLED.off();
    currentState = State::OFF;
}