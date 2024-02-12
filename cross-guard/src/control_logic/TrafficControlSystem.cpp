//
// Created by Saleem Hamo on 12/02/2024.
//

#include "TrafficControlSystem.h"

TrafficControlSystem::TrafficControlSystem() : currentState(State::CAR_RED_PEDESTRIAN_GREEN) {
    // Initialize system, possibly setting initial states of lights, etc.
    updateOutputs(); // Ensure outputs match the initial state
}

void TrafficControlSystem::update() {
    /*
     * This method would be called in a loop to regularly check for state transitions
     * and possibly read sensors if not interrupt-driven
     */
}

void TrafficControlSystem::changeState(State newState) {
    currentState = newState;
    updateOutputs(); // Update outputs anytime the state changes
}

void TrafficControlSystem::updateOutputs() {
    // Based on the current state, control the traffic lights, buzzer, and warning light
    // This is a placeholder for actual GPIO control logic
    switch (currentState) {
        case State::CAR_RED_PEDESTRIAN_GREEN:
            // Set car light to red, pedestrian light to green, disable buzzer and warning light
            break;
        case State::CAR_GREEN_PEDESTRIAN_RED:
            // Set car light to green, pedestrian light to red, disable buzzer and warning light
            break;
        case State::CAR_GREEN_PEDESTRIAN_WAIT:
            // Keep car light green, pedestrian light red, enable warning light, maybe enable buzzer shortly
            break;
        case State::CAR_RED_PEDESTRIAN_GREEN_SAFE:
            // Set car light to red, pedestrian light to green, disable buzzer, and warning light
            break;
            // Handle other states as needed
    }
}

void TrafficControlSystem::handleCarTrafficLightChange(bool isGreen) {
    if (isGreen && currentState == State::CAR_RED_PEDESTRIAN_GREEN) {
        changeState(State::CAR_GREEN_PEDESTRIAN_RED);
    } else if (!isGreen && currentState == State::CAR_GREEN_PEDESTRIAN_RED) {
        changeState(State::CAR_RED_PEDESTRIAN_GREEN);
    }
}

void TrafficControlSystem::handleRoadStatusChange(bool isEmpty) {
    if (isEmpty && currentState == State::CAR_GREEN_PEDESTRIAN_WAIT) {
        changeState(State::CAR_RED_PEDESTRIAN_GREEN_SAFE);
    }
    // Add logic for other scenarios as necessary
}

void TrafficControlSystem::handlePedestrianButtonPress() {
    if (currentState == State::CAR_GREEN_PEDESTRIAN_RED) {
        changeState(State::CAR_GREEN_PEDESTRIAN_WAIT);
    }
    // Adjust based on system requirements
}

void TrafficControlSystem::handlePedestrianSensorTrigger(bool isDetected) {
    // Implement according to how sensor detection affects the system state
}
