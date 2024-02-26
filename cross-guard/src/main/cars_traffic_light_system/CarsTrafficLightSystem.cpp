//
// Created by Saleem Hamo on 20/02/2024.
//
#include "main/cars_traffic_light_system/CarsTrafficLightSystem.h"
#include <unistd.h>  // For sleep()

CarsTrafficLightSystem::CarsTrafficLightSystem(int redPin, int greenPin)
        : TrafficLight(redPin, greenPin) {}

void CarsTrafficLightSystem::initialize() {
    // run all states with delays!
    // set default state
    turnRed();
    sleep(500); // This is for initialization only
    turnGreen();
    sleep(500); // This is for initialization only
    turnOff();


}

void CarsTrafficLightSystem::activate() {
    // Implementation
    // Start the loop and only listen to interrupts to handle tha change
}

void CarsTrafficLightSystem::deactivate() {
    turnOff();
}