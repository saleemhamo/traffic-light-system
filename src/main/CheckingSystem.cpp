//
// Created by Saleem Hamo on 20/02/2024.
//
#include "main/CheckingSystem.h"
#include <chrono>  // For std::chrono

CheckingSystem::CheckingSystem() {
//    pedestrianSensor
}

CheckingSystem::~CheckingSystem() {
    active = false;  // Signal threads to stop
    if (pedestrianThread.joinable()) {
        pedestrianThread.join();  // Wait for the thread to finish
    }
}

void CheckingSystem::initialize() {
    // Initialize sensors and internal state
//    pedestrianSensor.initialize();
//    roadSensor.initialize();
    active = true;  // Mark the system as active
}

void CheckingSystem::activate() {
    // Start monitoring in a separate thread
    pedestrianThread = std::thread(&CheckingSystem::monitorPedestrians, this);
}

void CheckingSystem::deactivate() {
    // Stop monitoring
    active = false;
}

void CheckingSystem::monitorPedestrians() {
    while (active) {
        // Simulate checking pedestrians
        std::this_thread::sleep_for(std::chrono::seconds(1));  // Replace with actual sensor checking logic
    }
}

void CheckingSystem::checkRoadStatus() {
    // Triggered when button is pressed, implement logic to check road status
}