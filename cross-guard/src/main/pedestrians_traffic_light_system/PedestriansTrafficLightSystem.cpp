//
// Created by Saleem Hamo on 20/02/2024.
//
#include "main/pedestrians_traffic_light_system/PedestriansTrafficLightSystem.h"
#include <unistd.h>  // For sleep()

PedestriansTrafficLightSystem::PedestriansTrafficLightSystem(): TrafficLight(redPin, greenPin) {}

void PedestriansTrafficLightSystem::initialize() {
    // run all states with delays!
    // set default state
    turnRed();
    sleep(500); // This is for initialization only
    turnGreen();
    sleep(500); // This is for initialization only
    turnOff();
}

void PedestriansTrafficLightSystem::activate() {
    // Implementation
    // Start the loop and only listen to interrupts to handle tha change
}

void PedestriansTrafficLightSystem::deactivate() {
    turnOff();
}