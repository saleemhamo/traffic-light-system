#include "main/PedestriansTrafficLightSystem.h"
#include <chrono>  // For std::chrono
#include "utils/Logger.h"
#include "utils/Constants.h"
#include <thread>

PedestriansTrafficLightSystem::PedestriansTrafficLightSystem()
        : TrafficLight(Constants::PedestriansTrafficLightRedPin,
                       Constants::PedestriansTrafficLightGreenPin,
                       Constants::UnusedPin),
          isActive(false) {}

void PedestriansTrafficLightSystem::initialize() {

}

void PedestriansTrafficLightSystem::run() {

}

void PedestriansTrafficLightSystem::deactivate() {
    isActive = false;
    turnOff();
}
