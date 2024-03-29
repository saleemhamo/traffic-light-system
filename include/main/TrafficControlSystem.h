//
// Created by Saleem Hamo on 12/02/2024.
//

#ifndef TRAFFICCONTROLSYSTEM_H
#define TRAFFICCONTROLSYSTEM_H

#include "main/interfaces/SystemInterface.h"

class TrafficControlSystem : public SystemInterface {
public:
    // Enum to represent the various states of the traffic control system
    enum class State {
        CAR_RED_PEDESTRIAN_GREEN,         // Cars stopped, pedestrians can walk
        CAR_GREEN_PEDESTRIAN_RED,         // Cars can go, pedestrians stop
        CAR_GREEN_PEDESTRIAN_WAIT,        // Cars go, pedestrians wait for safe crossing
        CAR_RED_PEDESTRIAN_GREEN_SAFE,    // Safe for pedestrians to cross, cars stop
        // Additional states can be added as necessary
    };

    // Constructor
    TrafficControlSystem();

    TrafficControlSystem::State getCurrentState();

    // Handlers for various triggers
    void handleCarTrafficLightChange(bool isGreen);

    void handleRoadStatusChange(bool isEmpty);

    void handlePedestrianButtonPress();

    void handlePedestrianSensorTrigger(bool isDetected);

    // Override system interface
    void run();

private:
    State currentState;
    State defaultState;

    void initializeSystemState();

    // Private method to change the state of the system
    void changeState(State newState);

    // Private method to update the outputs (lights, buzzer) based on the current state
    void updateOutputs();

    void update();
};

#endif // TRAFFICCONTROLSYSTEM_H
