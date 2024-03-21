#include "main/PedestriansTrafficLightSystem.h"
#include <chrono>  // For std::chrono
#include "utils/Logger.h"

PedestriansTrafficLightSystem::PedestriansTrafficLightSystem(
        std::mutex *mtx, std::condition_variable *cv, bool *signalChanged
) : TrafficLight(redPin, greenPin),
    mtx(mtx), cv(cv), signalChanged(signalChanged), stopRequested(false) {}


void PedestriansTrafficLightSystem::initialize() {
    // Initialize default state
    turnRed();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Use std::chrono for non-blocking sleep
    turnGreen();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    turnOff();
}

void PedestriansTrafficLightSystem::activate() {
    stopRequested = false;
    lightThread = std::thread(&PedestriansTrafficLightSystem::run, this);
}

void PedestriansTrafficLightSystem::deactivate() {
    stopRequested = true;
    if (lightThread.joinable()) {
        lightThread.join();
    }
    turnOff(); // Ensure the light is turned off
}

void PedestriansTrafficLightSystem::run() {
    Logger::logInfo("PedestriansTrafficLightSystem::run called");
    while (!stopRequested) {
        std::unique_lock<std::mutex> lk(*mtx);
        cv->wait(lk, [this] { return !(*signalChanged); }); // Wait until cars light changes
        // Code to switch lights
        Logger::logInfo("PedestriansTrafficLightSystem::turnGreen called");
        turnGreen();

        *signalChanged = true; // Reset the signal
        lk.unlock();
        cv->notify_all(); // Notify car system

        // Add delay or conditions for light change
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        Logger::logInfo("PedestriansTrafficLightSystem::turnRed called");
        turnRed();
    }
}

void PedestriansTrafficLightSystem::requestStop() {
    stopRequested = true;
}

//void PedestriansTrafficLightSystem::run() {
//    while (!stopRequested) {
//        // Traffic light control logic
//        turnGreen();
//        std::this_thread::sleep_for(std::chrono::seconds(10)); // Adjust timing as needed
//        turnRed();
//        std::this_thread::sleep_for(std::chrono::seconds(10)); // Adjust timing as needed
//    }
//}
