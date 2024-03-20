#include "main/CarsTrafficLightSystem.h"
#include <chrono>  // For std::chrono
#include "utils/Logger.h"


CarsTrafficLightSystem::CarsTrafficLightSystem(std::mutex *mtx, std::condition_variable *cv, bool *signalChanged)
        : TrafficLight(redPin, greenPin),
          mtx(mtx), cv(cv), signalChanged(signalChanged), stopRequested(false) {}


void CarsTrafficLightSystem::initialize() {
    // Initialize default state
    turnRed();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Use std::chrono for non-blocking sleep
    turnGreen();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    turnOff();
}

void CarsTrafficLightSystem::activate() {
    stopRequested = false;
    lightThread = std::thread(&CarsTrafficLightSystem::run, this);
}

void CarsTrafficLightSystem::deactivate() {
    stopRequested = true;
    if (lightThread.joinable()) {
        lightThread.join();
    }
    turnOff(); // Ensure the light is turned off
}

void CarsTrafficLightSystem::run() {
    Logger::logInfo("CarsTrafficLightSystem::run called");
    while (!stopRequested) {
        std::unique_lock<std::mutex> lk(*mtx);
        cv->wait(lk, [this] { return *signalChanged; }); // Wait until pedestrians light changes
        // Code to switch lights
        Logger::logInfo("CarsTrafficLightSystem::turnGreen called");
        turnGreen();

        *signalChanged = false; // Reset the signal
        lk.unlock();
        cv->notify_all(); // Notify pedestrian system

        // Add delay or conditions for light change
    }
}

void CarsTrafficLightSystem::requestStop() {
    stopRequested = true;
}

//void CarsTrafficLightSystem::run() {
//    while (!stopRequested) {
//        // Traffic light control logic
//        turnGreen();
//        std::this_thread::sleep_for(std::chrono::seconds(10)); // Adjust timing as needed
//        turnRed();
//        std::this_thread::sleep_for(std::chrono::seconds(10)); // Adjust timing as needed
//    }
//}
