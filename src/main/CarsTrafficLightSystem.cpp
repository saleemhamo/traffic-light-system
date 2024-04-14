// Documentation by Miguel Rosa

#include "main/CarsTrafficLightSystem.h"
#include <chrono>  // For std::chrono functionalities
#include "utils/Logger.h"
#include <thread>
#include "utils/Constants.h"

/**
 * @file main/CarsTrafficLightSystem.cpp
 * @brief Implementation of the CarsTrafficLightSystem class.
 *
 * Provides functionality for initializing, running, and deactivating a traffic
 * light system designed specifically for car traffic. Uses the pigpio library
 * for controlling GPIO pins in a Raspberry Pi environment.
 */

/**
 * @brief Constructs a new Cars Traffic Light System object.
 * 
 * Initializes the traffic light system with specific pins for red, green, and yellow lights.
 */
CarsTrafficLightSystem::CarsTrafficLightSystem()
        : TrafficLight(Constants::CarsTrafficLightRedPin,
                       Constants::CarsTrafficLightGreenPin,
                       Constants::CarsTrafficLightYellowPin),
          isActive(false) {}

/**
 * @brief Initializes the traffic light system.
 *
 * Placeholder for initialization code, if any additional setup is required.
 */
void CarsTrafficLightSystem::initialize() {

}

/**
 * @brief Runs the main logic of the traffic light control.
 *
 * Placeholder for the main operational logic of the traffic light system.
 */
void CarsTrafficLightSystem::run() {

}

/**
 * @brief Deactivates the traffic light system.
 *
 * Turns off all lights and marks the system as inactive.
 */
void CarsTrafficLightSystem::deactivate() {
    isActive = false;
    turnOff();
}
