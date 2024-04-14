// Documented by Miguel Rosa

#include "main/PedestriansTrafficLightSystem.h"
#include <chrono>  // For std::chrono
#include "utils/Logger.h"
#include "utils/Constants.h"
#include <thread>

/**
 * @file PedestriansTrafficLightSystem.cpp
 * @brief Implements functionality for the PedestriansTrafficLightSystem class.
 *
 * This file provides the definitions of the PedestriansTrafficLightSystem class methods,
 * handling initialization, operation, and deactivation of pedestrian traffic lights.
 */

/**
 * @brief Constructor for PedestriansTrafficLightSystem.
 * Initializes traffic light pins and sets the system as inactive.
 */

PedestriansTrafficLightSystem::PedestriansTrafficLightSystem()
        : TrafficLight(Constants::PedestriansTrafficLightRedPin,
                       Constants::PedestriansTrafficLightGreenPin,
                       Constants::UnusedPin),
          isActive(false) {}

/**
 * @brief Initializes the pedestrian traffic light system.
 * Placeholder for any setup required before activating the lights.
 */
void PedestriansTrafficLightSystem::initialize() {
    // Initialization code here, such as setting the mode of GPIO pins if needed.
}

/**
 * @brief Main operational logic for the pedestrian traffic lights.
 * Currently, it does not contain implementation details.
 */
void PedestriansTrafficLightSystem::run() {
    // Code to manage light changes and check the system's status.
}

/**
 * @brief Deactivates the traffic light system.
 * Turns off the lights and marks the system as inactive.
 */
void PedestriansTrafficLightSystem::deactivate() {
    isActive = false;
    turnOff(); // Method inherited from TrafficLight to turn off all lights.
}