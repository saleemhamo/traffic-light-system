#include "main/MainSystem.h"

MainSystem::MainSystem() : trafficLightState(OFF) {}

MainSystem::~MainSystem() {
    shutdown();
}

void MainSystem::initialize() {
    // Initialize all subsystems here
    carsTrafficLight.initialize();
    pedestriansTrafficLight.initialize();
    checkingSystem.initialize();
    warningSystem.initialize();

    // Register callbacks from the CheckingSystem
    checkingSystem.registerCarsMotionCallback([this]() { this->onCarsMotionDetected(); });
    checkingSystem.registerPedestriansMotionCallback([this]() { this->onPedestriansMotionDetected(); });
    checkingSystem.registerPedestriansButtonCallback([this]() { this->onPedestriansButtonClicked(); });
}

void MainSystem::runSystems() {
    enableTrafficLightsNormalBehaviour();
    std::thread trafficLightsThread(&MainSystem::runTrafficLightsNormalBehaviour, this);
    std::thread checkingSystemThread([this]() { checkingSystem.run(); });
    trafficLightsThread.join();
    checkingSystemThread.join();
    // Enable running warning system if needed
}

void MainSystem::shutdown() {
    carsTrafficLight.deactivate();
    pedestriansTrafficLight.deactivate();
    checkingSystem.deactivate();
    warningSystem.deactivate();
    // Join all threads here if they are joinable
}

void MainSystem::onCarsMotionDetected() {
    std::cout << "Cars motion detected" << std::endl;
    if (trafficLightState != CARS_RED_PEDESTRIANS_GREEN) {
        return; // Do Nothing
    }

    // State is CARS_RED_PEDESTRIANS_GREEN
    checkingSystem.disableSensing();
    disableTrafficLightsNormalBehaviour();
    turnAllRed();
    warningSystem.activate();

    // after 5 seconds
    mainSystemTimer.setTimeout([this] {
        warningSystem.deactivate();
        enableTrafficLightsNormalBehaviour();
        runTrafficLightsNormalBehaviour();
        checkingSystem.enableSensing();
    }, 5000);
}

void MainSystem::onPedestriansMotionDetected() {
    std::cout << "Pedestrians motion detected" << std::endl;
    if (trafficLightState != CARS_GREEN_PEDESTRIANS_RED) {
        return; // Do Nothing
    }

    // State is CARS_GREEN_PEDESTRIANS_RED
    checkingSystem.disableSensing();
    disableTrafficLightsNormalBehaviour();
    turnAllRed();
    warningSystem.activate();

    // after 5 seconds
    mainSystemTimer.setTimeout([this] {
        warningSystem.deactivate();
        enableTrafficLightsNormalBehaviour();
        runTrafficLightsNormalBehaviour();
        checkingSystem.enableSensing();
    }, 5000);
}

void MainSystem::onPedestriansButtonClicked() {
    if (trafficLightState != CARS_GREEN_PEDESTRIANS_RED) {
        return; // Do Nothing
    }

    // State is CARS_GREEN_PEDESTRIANS_RED
    // if road status is empty (sensor or camera) -> turn to CARS_RED_PEDESTRIANS_GREEN
    // continue normal behaviour

}

void MainSystem::enableTrafficLightsNormalBehaviour() {
    isTrafficLightRunningInNormalBehaviour = true;

}

void MainSystem::disableTrafficLightsNormalBehaviour() {
    isTrafficLightRunningInNormalBehaviour = false;
    carsTrafficLightTimer.stopTimer();
    pedestriansTrafficLightTimer.stopTimer();
}

void MainSystem::turnCarsGreen() {
    std::cout << "turnCarsGreen called" << std::endl;
    if (!isTrafficLightRunningInNormalBehaviour) {
        return;
    }
    carsTrafficLight.turnGreen();
    pedestriansTrafficLight.turnRed();
    trafficLightState = CARS_GREEN_PEDESTRIANS_RED;
    pedestriansTrafficLightTimer.setTimeout([this] { turnPedestriansGreen(); }, 5000);
    std::cout << "turnCarsGreen finished" << std::endl;

}

void MainSystem::turnPedestriansGreen() {
    std::cout << "turnPedestriansGreen called" << std::endl;
    if (!isTrafficLightRunningInNormalBehaviour) {
        return;
    }
    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnGreen();
    trafficLightState = CARS_RED_PEDESTRIANS_GREEN;
    carsTrafficLightTimer.setTimeout([this] { turnCarsGreen(); }, 5000);
    std::cout << "turnPedestriansGreen finished" << std::endl;
}

void MainSystem::turnAllRed() {
    std::cout << "turnAllRed called" << std::endl;
    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnRed();
    trafficLightState = OFF;
}


void MainSystem::runTrafficLightsNormalBehaviour() {
    std::cout << "runTrafficLightsNormalBehaviour called" << std::endl;
    turnCarsGreen();
}


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
