#ifndef CARSTRAFFICLIGHTSYSTEM_H
#define CARSTRAFFICLIGHTSYSTEM_H

#include "models/TrafficLight.h"
#include <atomic>
#include <thread>

/**
 * @file CarsTrafficLightSystem.h
 * @brief Manages a traffic light system for cars using GPIO pins.
 *
 * Extends the TrafficLight class to implement a traffic light system specifically
 * for cars, managing the operation and state of the traffic lights through
 * multi-threaded control and atomic states.
 */

/**
 * @class CarsTrafficLightSystem
 * @brief Implements traffic light control specifically for cars.
 *
 * Inherits from TrafficLight and provides methods to initialize, activate,
 * run, and deactivate the traffic light system. This class uses atomic variables
 * to manage state in a thread-safe manner.
 */

class CarsTrafficLightSystem : public TrafficLight {
public:
    /**
     * @brief Constructs a new Cars Traffic Light System object.
     * 
     * Initializes the traffic light system with specific pins for red, green, and yellow lights.
     */
    CarsTrafficLightSystem();

    /**
     * @brief Initializes the traffic light system.
     *
     * Placeholder for initialization code, if any additional setup is required.
     */
    void initialize();

    /**
     * @brief Runs the main logic of the traffic light control.
     *
     * Placeholder for the main operational logic of the traffic light system.
     */
    void run();

    /**
     * @brief Deactivates the traffic light system.
     *
     * Turns off all lights and marks the system as inactive.
     */
    void deactivate();

private:
    std::atomic<bool> isActive; //Indicates whether the traffic light system is currently active.
};

#endif // CARSTRAFFICLIGHTSYSTEM_H
