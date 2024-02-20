#include "control_logic/TrafficControlSystem.h"
#include "control_logic/CarsTrafficLightComponent.h"

// Function prototypes for initializing GPIO and reading inputs
void initializeSystem();


int main() {

    TrafficControlSystem trafficControlSystem;
    CarsTrafficLightComponent carsTrafficLightComponent;

    // Initialize the traffic control system and GPIO
    initializeSystem();

    // start cars traffic light
    carsTrafficLightComponent.run();

    // start traffic control logic
    trafficControlSystem.run();

    return 0;
}

void initializeSystem() {
    // Initialize GPIO pins for inputs and outputs
    // This is placeholder logic. Use specific GPIO library calls here.
}
