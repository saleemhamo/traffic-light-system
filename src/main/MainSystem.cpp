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
    carsTimer.initialize();
    pedestriansTimer.initialize();
;

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
    if (trafficLightState != CARS_RED_PEDESTRIANS_GREEN) {
        return; // Do Nothing
    }

    // State is CARS_RED_PEDESTRIANS_GREEN
    disableTrafficLightsNormalBehaviour();
    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnRed();
    warningSystem.activate();
    // after 5 seconds
    warningSystem.deactivate();
    enableTrafficLightsNormalBehaviour();
}

void MainSystem::onPedestriansMotionDetected() {
    std::cout << "Pedestrians motion detected";
    if (trafficLightState != CARS_GREEN_PEDESTRIANS_RED) {
        return; // Do Nothing
    }

    // State is CARS_GREEN_PEDESTRIANS_RED
    disableTrafficLightsNormalBehaviour();
    checkingSystem.disableCarsMotionDetection();
    checkingSystem.disablePedestriansMotionDetection();
    checkingSystem.disablePedestriansButton();

    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnRed();
    warningSystem.activate();

    // after 5 seconds

    warningSystem.deactivate();
    enableTrafficLightsNormalBehaviour();
}

void MainSystem::onPedestriansButtonClicked() {
    if (trafficLightState != CARS_GREEN_PEDESTRIANS_RED) {
        return; // Do Nothing
    }

    // State is CARS_GREEN_PEDESTRIANS_RED
    // if road status is empty (sensor or camera) -> turn to CARS_RED_PEDESTRIANS_GREEN
    // continue normal behaviour

}

void MainSystem::manageTrafficStates() {
    // Start the timers
    carsTimer.start(1000);        // Start the cars timer with a 1 second interval
    pedestriansTimer.start(1000); // Start the pedestrians timer with a 1 second interval

    // Main loop
    while (running) {
        // Check if the cars timer has expired
        if (carsTimer.isExpired()) {
            // Turn the cars traffic light red
            carsTrafficLight.turnRed();

            // Turn the pedestrians traffic light green
            pedestriansTrafficLight.turnGreen();

            // Update the traffic light state
            trafficLightState = CARS_RED_PEDESTRIANS_GREEN;

            // Restart the cars timer
            carsTimer.restart();
        }

        // Check if the pedestrians timer has expired
        if (pedestriansTimer.isExpired()) {
            // Turn the cars traffic light green
            carsTrafficLight.turnGreen();

            // Turn the pedestrians traffic light red
            pedestriansTrafficLight.turnRed();

            // Update the traffic light state
            trafficLightState = CARS_GREEN_PEDESTRIANS_RED;

            // Restart the pedestrians timer
            pedestriansTimer.restart();
        }
    }
}


void MainSystem::enableTrafficLightsNormalBehaviour() {
    // TODO: set starting state
    isTrafficLightRunningInNormalBehaviour = true;
}

void MainSystem::disableTrafficLightsNormalBehaviour() {
    isTrafficLightRunningInNormalBehaviour = false;
}

void MainSystem::runTrafficLightsNormalBehaviour() {
    while (true) {
        if (isTrafficLightRunningInNormalBehaviour) {
            // Start cars timer for 2 seconds
            carsTimer.start(2000, [this]() { 
                carsTrafficLight.turnRed();
                pedestriansTrafficLight.turnGreen();
                trafficLightState = CARS_RED_PEDESTRIANS_GREEN; });

            // Wait for cars timer to finish
            while (carsTimer.isRunning())
            {
                // Implement logic here if needed
            }
            // Stop the cars timer
            carsTimer.stop();

            // Start pedestrians timer for 2 seconds
            pedestriansTimer.start(2000, [this]() { 
                carsTrafficLight.turnGreen();
                pedestriansTrafficLight.turnRed();
                trafficLightState = CARS_GREEN_PEDESTRIANS_RED; });

            // Wait for pedestrians timer to finish
            while (pedestriansTimer.isRunning())
            {
                // Implement logic here if needed
            }
            // Stop the pedestrians timer
            pedestriansTimer.stop();
        }
    }
}

/*
#include "CarsTimer.h"
#include "PedestriansTimer.h"

void CarsTimer::timerEvent() {
    // Code to execute when the cars timer expires
    // For example, you could check the state of the cars traffic light and change it if necessary
}
void PedestriansTimer::timerEvent() {
    // Code to execute when the pedestrians timer expires
    // For example, you could check the state of the pedestrians traffic light and change it if necessary
}
void MainSystem::manageTrafficStates() {
    // Rest of your code...

    // Stop the timers when you're done with them
    carsTimer.stop();
    pedestriansTimer.stop();
}

*/

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
