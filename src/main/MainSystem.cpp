#include "main/MainSystem.h"
#include "utils/Logger.h"

MainSystem::MainSystem() : trafficLightState(OFF) {}

MainSystem::~MainSystem() {
    shutdown();
}

void MainSystem::initialize() {
    // Initialize all subsystems here
    Logger::logInfo("MainSystem::initialize called");
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
    Logger::logInfo("Cars motion detected");
    std::cout << "Cars motion detected" << std::endl;
    if (trafficLightState != CARS_RED_PEDESTRIANS_GREEN) {
        return; // Do Nothing
    }

    // State is CARS_RED_PEDESTRIANS_GREEN
    checkingSystem.disableSensing();
    disableTrafficLightsNormalBehaviour();
    turnAllTrafficLightsRed();
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
    Logger::logInfo("Pedestrians motion detected");
    std::cout << "Pedestrians motion detected" << std::endl;
    if (trafficLightState != CARS_GREEN_PEDESTRIANS_RED) {
        return; // Do Nothing
    }

    // State is CARS_GREEN_PEDESTRIANS_RED
    checkingSystem.disableSensing();
    disableTrafficLightsNormalBehaviour();
    turnAllTrafficLightsRed();
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
    yellowTrafficLightTimer.stopTimer();
}

void MainSystem::turnCarsTrafficLightGreen() {
    Logger::logInfo("turnCarsTrafficLightGreen called");
    if (!isTrafficLightRunningInNormalBehaviour) {
        return;
    }
    carsTrafficLight.turnYellow();
    pedestriansTrafficLight.turnRed();
    yellowTrafficLightTimer.setTimeout([this] {
        carsTrafficLight.turnGreen();
        pedestriansTrafficLight.turnRed();
        trafficLightState = CARS_GREEN_PEDESTRIANS_RED;
        pedestriansTrafficLightTimer.setTimeout([this] { turnPedestriansTrafficLightGreen(); }, 5000);
    }, 2000);

    Logger::logInfo("turnCarsTrafficLightGreen finished");

}

void MainSystem::turnPedestriansTrafficLightGreen() {
    Logger::logInfo("turnPedestriansTrafficLightGreen called");
    if (!isTrafficLightRunningInNormalBehaviour) {
        return;
    }
    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnGreen();
    trafficLightState = CARS_RED_PEDESTRIANS_GREEN;
    carsTrafficLightTimer.setTimeout([this] { turnCarsTrafficLightGreen(); }, 5000);
    Logger::logInfo("turnPedestriansTrafficLightGreen finished");


}

void MainSystem::turnAllTrafficLightsRed() {
    Logger::logInfo("turnAllTrafficLightsRed called");
    carsTrafficLight.turnRed();
    pedestriansTrafficLight.turnRed();
    trafficLightState = OFF;
}


void MainSystem::runTrafficLightsNormalBehaviour() {
    Logger::logInfo("runTrafficLightsNormalBehaviour called");
    turnCarsTrafficLightGreen();
}