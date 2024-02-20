#include "control_logic/TrafficControlSystem.h"
#include <chrono>
#include <thread>

using namespace std;

// Function prototypes for initializing GPIO and reading inputs
void initializeSystem();

bool readCarTrafficLightSensor();

bool readRoadStatusSensor();

bool readPedestrianButton();

bool readPedestrianSensor();

int main() {
    // Initialize the traffic control system and GPIO
    TrafficControlSystem trafficControlSystem;

    initializeSystem();
    // start cars traffic light
    // start traffic control logic

    // TODO: initialize a thread that acts as the normal cars traffic light
    // Our system should read input from there and just send a signal to make it red when necessary (transition to CAR_RED_PEDESTRIAN_GREEN_SAFE)

    // Main loop
    while (true) {
        // Check inputs
        bool carLightGreen = readCarTrafficLightSensor(); // TODO: Take input from cars traffic light
        bool roadIsEmpty = readRoadStatusSensor(); // TODO: Read from camera
        bool pedestrianButtonPressed = readPedestrianButton(); // TODO: Convert this a signal (interrupt)
        bool pedestrianDetected = readPedestrianSensor(); // TODO: Read from ultrasonic sensor

        // Update system based on inputs
        trafficControlSystem.handleCarTrafficLightChange(carLightGreen);
        trafficControlSystem.handleRoadStatusChange(roadIsEmpty);
        if (pedestrianButtonPressed) {
            trafficControlSystem.handlePedestrianButtonPress();
        }
        if (pedestrianDetected) {
            trafficControlSystem.handlePedestrianSensorTrigger(true);
        }

        // Process any state changes and update outputs
        trafficControlSystem.update();

        // Sleep for a short duration before checking inputs again
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    return 0;
}

void initializeSystem() {
    // Initialize GPIO pins for inputs and outputs
    // This is placeholder logic. Use specific GPIO library calls here.
}

// TODO: Move to CarTrafficLightController
bool readCarTrafficLightSensor() {
    // Read the sensor/state that indicates whether the car traffic light is green
    // Placeholder logic
    return false; // Replace with actual GPIO read
}

// TODO: Read from Camera module
bool readRoadStatusSensor() {
    // Read the sensor that indicates whether the road is empty
    // Placeholder logic
    return false; // Replace with actual GPIO read
}

// TODO: Convert to interrupt
bool readPedestrianButton() {
    // Read the state of the pedestrian button
    // Placeholder logic
    return false; // Replace with actual GPIO read
}

// TODO: Read from Ultrasonic
bool readPedestrianSensor() {
    // Read the sensor that detects pedestrians waiting to cross
    // Placeholder logic
    return false; // Replace with actual GPIO read
}
