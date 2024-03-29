#include "main/PedestriansTrafficLightSystem.h"
#include <chrono>  // For std::chrono
#include "utils/Logger.h"
#include "utils/Constants.h"
#include <thread>

PedestriansTrafficLightSystem::PedestriansTrafficLightSystem()
        : TrafficLight(Constants::PedestriansTrafficLightRedPin,
                       Constants::PedestriansTrafficLightGreenPin),
          isActive(false) {}

void PedestriansTrafficLightSystem::initialize() {

}

void PedestriansTrafficLightSystem::run() {
    isActive = true;
    while (isActive) {
        turnGreen();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // Example timing
        if (!isActive) break; // Check again after waking up

        turnRed();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000)); // Example timing
    }
}

void PedestriansTrafficLightSystem::deactivate() {
    isActive = false;
    turnOff();
}
