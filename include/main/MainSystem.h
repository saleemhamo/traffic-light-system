#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <mutex>
#include <thread>
#include <atomic>
#include <iostream>
#include "CarsTrafficLightSystem.h"
#include "PedestriansTrafficLightSystem.h"
#include "CheckingSystem.h"
#include "WarningSystem.h"
#include "utils/Timer.h"

/**
 * @file MainSystem.h
 * @brief Header file for the MainSystem class managing the traffic and pedestrian light systems.
 *
 * The MainSystem coordinates the operational states of traffic and pedestrian lights,
 * responding to various sensor inputs and managing state transitions accordingly.
 */

/**
 * @class MainSystem
 * @brief Orchestrates the operations of traffic and pedestrian traffic lights, monitoring systems, and emergency protocols.
 *
 * Integrates multiple subsystems like CarsTrafficLightSystem, PedestriansTrafficLightSystem, CheckingSystem,
 * and WarningSystem to create a cohesive traffic management system. Handles state transitions based on sensor inputs
 * and manages the safety protocols during unusual events.
 */

class MainSystem {
public:
    /**
     * @enum TrafficLightState
     * Enumerates the states of the traffic lights within the system.
     */
    enum TrafficLightState {
        OFF, ///< Both cars and pedestrians lights are off.
        CARS_RED_PEDESTRIANS_GREEN, ///< Cars at red and pedestrians at green.
        CARS_GREEN_PEDESTRIANS_RED ///< Cars at green and pedestrians at red.
    };

    MainSystem(); ///< Constructor initializes the system with traffic lights off.
    ~MainSystem(); ///< Destructor ensures proper shutdown of all systems.

    void initialize(); ///< Initializes all subsystems and registers necessary callbacks.
    void runSystems(); ///< Begins operation of all traffic management subsystems.
    void shutdown(); ///< Safely deactivates all subsystems and terminates operation.

private:
    TrafficLightState trafficLightState; ///< Current state of the traffic lights.
    Timer carsTrafficLightTimer; ///< Timer for transitions of car traffic lights.
    Timer pedestriansTrafficLightTimer; ///< Timer for transitions of pedestrian traffic lights.
    Timer yellowTrafficLightTimer; ///< Timer for managing intermediate yellow light duration.
    Timer mainSystemTimer; ///< Timer for overall system operations.

    CarsTrafficLightSystem carsTrafficLight; ///< Controls the traffic lights for cars.
    PedestriansTrafficLightSystem pedestriansTrafficLight; ///< Controls the traffic lights for pedestrians.
    CheckingSystem checkingSystem; ///< Monitors environmental conditions and system status.
    WarningSystem warningSystem; ///< Manages emergency warnings and alerts.

    std::thread carsThread; ///< Dedicated thread for car light operations.
    std::thread pedestriansThread; ///< Dedicated thread for pedestrian light operations.
    std::thread checkingThread; ///< Dedicated thread for environmental monitoring.
    std::thread warningThread; ///< Dedicated thread for managing emergency protocols.

    std::atomic<bool> isTrafficLightRunningInNormalBehaviour; ///< Flag indicating if the traffic lights are operating under normal conditions.

    void onCarsMotionDetected(); ///< Reacts to car motion detection events.
    void onPedestriansMotionDetected(); ///< Reacts to pedestrian motion detection events.
    void onPedestriansButtonClicked(); ///< Handles pedestrian button press events.

    void enableTrafficLightsNormalBehaviour(); ///< Enables normal operation of traffic lights.
    void disableTrafficLightsNormalBehaviour(); ///< Disables normal operation of traffic lights.

    void runTrafficLightsNormalBehaviour(); ///< Manages the regular cycle of traffic lights.

    void turnCarsTrafficLightGreen(); ///< Sets car traffic lights to green.
    void turnPedestriansTrafficLightGreen(); ///< Sets pedestrian traffic lights to green.
    void turnAllTrafficLightsRed(); ///< Sets all traffic lights to red.
};

#endif // MAINSYSTEM_H