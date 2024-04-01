#include "main/CarsTrafficLightSystem.h"
#include <chrono>  // For std::chrono
#include "utils/Logger.h"
#include <thread>
#include "utils/Constants.h"

CarsTrafficLightSystem::CarsTrafficLightSystem()
        : TrafficLight(Constants::CarsTrafficLightRedPin,
                       Constants::CarsTrafficLightGreenPin,
                       Constants::CarsTrafficLightYellowPin),
          isActive(false) {}

void CarsTrafficLightSystem::initialize() {

}

void CarsTrafficLightSystem::run() {

}

void CarsTrafficLightSystem::deactivate() {
    isActive = false;
    turnOff();
}
