#include "main/CheckingSystem.h"
#include <chrono>  // For std::chrono
#include <iostream>

CheckingSystem::CheckingSystem() :
        isActive(false),
        monitorPedestriansActive(false),
        monitorRoadsActive(false),
        pedestriansButtonEnabled(false),
        pedestrianSensor(Constants::CheckingSystemUltrasonic1TriggerPin, Constants::CheckingSystemUltrasonic1EchoPin),
        roadSensor(Constants::CheckingSystemUltrasonic2TriggerPin, Constants::CheckingSystemUltrasonic2EchoPin),
        pedestriansPushButton(Constants::CheckingSystemButtonPin) {

}

CheckingSystem::~CheckingSystem() {
    deactivate();  // Ensure threads are properly joined and sensors are deactivated
}

void CheckingSystem::initialize() {
    // Initialize your ultrasonic sensors here
    pedestrianSensor.initialize();
    roadSensor.initialize();
    pedestriansPushButton.initialize();

    pedestriansPushButton.registerButtonPressCallback([this]() { this->onPedestriansButtonPress(); });
}

void CheckingSystem::run() {
    isActive = true;

    enablePedestriansMotionDetection();
    enableCarsMotionDetection();
    // Launch monitoring threads
    std::thread pedestrianThread([this]() { this->monitorPedestrian(); });
    std::thread roadThread([this]() { this->monitorRoad(); });

    // Detach threads if you don't need to synchronize them back
    pedestrianThread.join(); // TODO
    roadThread.join();
}

void CheckingSystem::onPedestriansButtonPress() {
    if (pedestriansButtonEnabled && pedestriansButtonClicked) {
        pedestriansButtonClicked();
    }
}

void CheckingSystem::monitorPedestrian() {
    while (isActive) {
        if (monitorPedestriansActive && pedestrianSensor.isMotionDetected()) {
            if (pedestriansMotionDetected) {
                pedestriansMotionDetected();  // Call the registered callback
            }
        }
        // Sleep to prevent hogging CPU - adjust the delay as needed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void CheckingSystem::monitorRoad() {
    while (isActive) {
        if (monitorRoadsActive && roadSensor.isMotionDetected()) {
            if (carsMotionDetected) {
                carsMotionDetected();  // Call the registered callback
            }
        }
        // Sleep to prevent hogging CPU - adjust the delay as needed
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void CheckingSystem::deactivate() {
    isActive = false;
    // Give time for threads to finish any ongoing work
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Adjust as needed
    // No need to manually join the threads since they were detached,
    // but ensure any needed cleanup is performed here.
}


void CheckingSystem::enablePedestriansMotionDetection() {
    monitorRoadsActive = true;
}

void CheckingSystem::disablePedestriansMotionDetection() {
    monitorRoadsActive = false;
}

void CheckingSystem::enableCarsMotionDetection() {
    monitorPedestriansActive = true;
}

void CheckingSystem::disableCarsMotionDetection() {
    monitorRoadsActive = false;
}

void CheckingSystem::enablePedestriansButton() {
    pedestriansButtonEnabled = true;
}

void CheckingSystem::disablePedestriansButton() {
    pedestriansButtonEnabled = false;
}


void CheckingSystem::registerCarsMotionCallback(const std::function<void()> &callback) {
    carsMotionDetected = callback;
}

void CheckingSystem::registerPedestriansMotionCallback(const std::function<void()> &callback) {
    pedestriansMotionDetected = callback;
}

void CheckingSystem::registerPedestriansButtonCallback(const std::function<void()> &callback) {
    pedestriansButtonClicked = callback;
}

void CheckingSystem::enableSensing() {
    enablePedestriansButton();
    enablePedestriansMotionDetection();
    enableCarsMotionDetection();
}

void CheckingSystem::disableSensing() {
    disablePedestriansButton();
    disablePedestriansMotionDetection();
    disableCarsMotionDetection();
}

