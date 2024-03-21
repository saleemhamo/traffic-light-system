#include "main/MainSystem.h"

MainSystem::MainSystem() : running(false), trafficLightState(OFF) {}

MainSystem::~MainSystem() {
    shutdown();
}

void MainSystem::initialize() {
    // Initialize all subsystems here
    carsTrafficLight.initialize();
    pedestriansTrafficLight.initialize();
    checkingSystem.initialize();
    warningSystem.initialize();

    // Set traffic light initial state
    trafficLightState = CARS_GREEN_PEDESTRIANS_RED;
    // Register callbacks from the CheckingSystem
    checkingSystem.registerCarsMotionCallback([this]() { this->onCarsMotionDetected(); });
    checkingSystem.registerPedestriansMotionCallback([this]() { this->onPedestriansMotionDetected(); });
    checkingSystem.registerPedestriansMotionCallback([this]() { this->onPedestriansMotionDetected(); });
}

void MainSystem::runSystems() {
    running = true;
    std::thread normalTrafficLights(&MainSystem::runTrafficLightsNormalBehaviour, this);
    normalTrafficLights.join();
//
//    // The manageTrafficStates method could run on its own thread or be part of the main loop.
//    std::thread trafficManagementThread(&MainSystem::manageTrafficStates, this);
//    trafficManagementThread.join();
}

void MainSystem::shutdown() {
    running = false;
    deactivateSubsystems();

    // Join all threads here if they are joinable
}

void MainSystem::deactivateSubsystems() {
    carsTrafficLight.deactivate();
    pedestriansTrafficLight.deactivate();
    checkingSystem.deactivate();
    warningSystem.deactivate();
}

void MainSystem::onCarsMotionDetected() {
    std::cout << "Cars motion detected";
    if (trafficLightState == CARS_GREEN_PEDESTRIANS_RED) {
        return; // Do Nothing
    }
    // State is CARS_RED_PEDESTRIANS_GREEN


    // -> Stop the normal behaviour
    // -> State is OFF (all red)
    // -> fire the alarm for 5 seconds
    // after 5 seconds -> run normal system

    // Implement logic to be executed when car motion is detected
}

void MainSystem::onPedestriansMotionDetected() {
    std::cout << "Pedestrians motion detected";
    if (trafficLightState == CARS_RED_PEDESTRIANS_GREEN) {
        return; // Do Nothing
    }
    // State is CARS_GREEN_PEDESTRIANS_RED

    // -> Stop the normal behaviour
    // -> State is OFF (all red)
    // -> fire the alarm for 5 seconds
    // after 5 seconds -> run normal system


}

void MainSystem::onPedestriansButtonClicked() {

}

void MainSystem::enableTrafficLightsNormalBehaviour() {
    isTrafficLightRunningInNormalBehaviour = true;
}

void MainSystem::disableTrafficLightsNormalBehaviour() {
    isTrafficLightRunningInNormalBehaviour = false;
}

void MainSystem::runTrafficLightsNormalBehaviour() {
    while (true) {
        if (isTrafficLightRunningInNormalBehaviour) {
            carsTrafficLight.turnGreen();
            pedestriansTrafficLight.turnRed();
            trafficLightState = CARS_GREEN_PEDESTRIANS_RED;
            // wait 2 second
            carsTrafficLight.turnRed();
            pedestriansTrafficLight.turnGreen();
            trafficLightState = CARS_RED_PEDESTRIANS_GREEN;
            // wait 2 second
        }
    }
}

void MainSystem::manageTrafficStates() {
    // Set initial states
    // States:
    //      - CARS_RED_PED_GREEN
    //      - CARS_GREEN_PED_RED

    // Scenario #1 -> CARS_RED_PED_GREEN -> monitor road -> when needed, turn all red and fire alarm.
    // Scenario #2 -> CARS_RED_PED_GREEN -> timeout      -> change state
    // Scenario #3 -> CARS_GREEN_PED_RED -> monitor ped -> when needed, turn all red and fire alarm.
    // Scenario #4 -> CARS_GREEN_PED_RED -> button pressed -> monitor road and decide
    // Scenario #5 -> CARS_GREEN_PED_RED -> timeout      -> change state


    // set traffic lights
    // start detection


    // runTrafficLightsNormalBehaviour
    // run what to check based on state ->
    //                                      CARS_RED_PED_GREEN -> check road only
    //                                      CARS_GREEN_PED_RED -> check pedestrians

    // callback from road -> Scenario #1


    while (running) {
        std::cout << "Hiiii";
        // Implement logic to manage and update the traffic light states
        // This could involve checking the current state of each traffic light, deciding on state transitions, etc.
        // Remember to use locking where necessary to prevent data races
    }
}
