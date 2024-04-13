// Documented by Miguel Rosa

#ifndef PEDESTRIANSTRAFFICLIGHTSYSTEM_H
#define PEDESTRIANSTRAFFICLIGHTSYSTEM_H

#include "models/TrafficLight.h"
#include <atomic>
#include <thread>

/**
 * @file PedestriansTrafficLightSystem.h
 * @brief Traffic light system for pedestrian control.
 *
 * Manages the traffic lights specific to pedestrian crossings, ensuring the lights
 * are controlled in a thread-safe manner with atomic operations.
 */

/**
 * @class PedestriansTrafficLightSystem
 * @brief Manages pedestrian-specific traffic lights.
 *
 * Extends the TrafficLight class to specifically handle pedestrian traffic lights,
 * managing their operational state and ensuring they can be safely activated and deactivated.
 */

class PedestriansTrafficLightSystem : public TrafficLight {
public:
    PedestriansTrafficLightSystem(); ///< Constructor initializing the system with default pin settings.
    void initialize(); ///< Initializes the traffic light system.
    void run(); ///< Starts the operation of the traffic light, managing its state changes.
    void deactivate(); ///< Deactivates the traffic lights, turning them off safely.

private:
    std::atomic<bool> isActive; ///< Indicates whether the traffic light system is currently active.
};

#endif // PEDESTRIANSTRAFFICLIGHTSYSTEM_H
