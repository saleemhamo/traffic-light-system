#include "main/CarsTrafficLightSystem.h"
#include <chrono>  // For std::chrono
#include "utils/Logger.h"
#include <thread>
#include "utils/Constants.h"

CarsTrafficLightSystem::CarsTrafficLightSystem()
        : TrafficLight(Constants::CarsTrafficLightRedPin,
                       Constants::CarsTrafficLightGreenPin),
          isActive(false) {}

void CarsTrafficLightSystem::initialize() {

}

void CarsTrafficLightSystem::run() {
    isActive = true;
    while (isActive) {
        turnGreen();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // Example timing
        if (!isActive) break;  // Check again after waking up

        turnRed();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // Example timing
    }
}

void CarsTrafficLightSystem::deactivate() {
    isActive = false;
    turnOff();
}
