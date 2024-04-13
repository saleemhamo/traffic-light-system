//
// Created by Saleem Hamo on 20/02/2024.Documented by Miguel Rosa
//
#include <string>
#include "actuators/LED.h"

#ifndef CROSSGUARD_TRAFFICLIGHT_H
#define CROSSGUARD_TRAFFICLIGHT_H

/**
 * @class TrafficLight
 * @brief Manages the state of a traffic light using individual LEDs for each color.
 * 
 * The TrafficLight class uses three LED instances to represent the red, green, and yellow 
 * lights of a traffic light. It allows for control of these lights through public methods 
 * that simulate typical traffic light operations.
 */
class TrafficLight {

public:
    /**
     * @enum State
     * @brief Represents the possible states of a traffic light.
     */
    enum class State {
        OFF,    ///< Indicates that all lights are off.
        RED,    ///< Indicates that the red light is on.
        GREEN,  ///< Indicates that the green light is on.
        YELLOW  ///< Indicates that the yellow light is on.
    
    };

    /**
     * @brief Constructor for a traffic light with specified pins for the red and green LEDs.
     * @param redPin GPIO pin connected to the red LED.
     * @param greenPin GPIO pin connected to the green LED.
     */
    TrafficLight(int redPin, int greenPin);

    /**
     * @brief Constructor for a traffic light with specified pins for the red, green, and yellow LEDs.
     * @param redPin GPIO pin connected to the red LED.
     * @param greenPin GPIO pin connected to the green LED.
     * @param yellowPin GPIO pin connected to the yellow LED.
     */
    TrafficLight(int redPin, int greenPin, int yellowPin);


    void turnRed();    ///< Sets the traffic light to red.
    void turnGreen();  ///< Sets the traffic light to green.
    void turnYellow(); ///< Sets the traffic light to yellow.
    void turnOff();    ///< Turns off all lights.


private:
    LED redLED;        ///< LED object for red light control.
    LED greenLED;      ///< LED object for green light control.
    LED yellowLED;     ///< LED object for yellow light control, if present.
    State currentState;  // 0 = off, 1 = red, 2 = green
};


#endif //CROSSGUARD_TRAFFICLIGHT_H
