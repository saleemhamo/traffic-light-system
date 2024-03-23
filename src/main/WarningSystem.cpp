//
// Created by Saleem Hamo on 20/02/2024.
// Updated and modified by Miguel Rosa 23/03/2024
#include "WarningSystem.h"


/ Constructor with dependency injection for sensors and traffic control system
WarningSystem::WarningSystem(CameraSensor& camera, UltrasonicSensor& ultrasonic, TrafficControlSystem& trafficSystem)
: cameraSensor(camera), ultrasonicSensor(ultrasonic), trafficControlSystem(trafficSystem),
  warningLED(Constants::WarningSystemLedPin), warningBuzzer(Constants::WarningSystemBuzzerPin),
  eventOccurred(false), stopRequested(false), isInitialized(false) {
   
}

WarningSystem::~WarningSystem() {
    stop();
}

void WarningSystem::initialize() {
    // Hardware initialization logic here
    warningLED.initialize();
    warningBuzzer.initialize();
    isInitialized = true;
    // Potentially start the warning system in a ready state
    run();
}

void WarningSystem::activate() {
    // Directly activate warning mechanisms (LED and Buzzer)
    warningLED.turnOn();
    warningBuzzer.makeSound();
    // This method might be called by checkAndActivate based on certain conditions
}

void WarningSystem::deactivate() {
    // Directly deactivate warning mechanisms (LED and Buzzer)
    warningLED.turnOff();
    warningBuzzer.stopSound();
}

void WarningSystem::run() {
    // Start the thread only if it hasn't been started or if it was stopped
    if (!warningThread.joinable()) {
        stopRequested = false;
        warningThread = std::thread([this] {
            std::unique_lock<std::mutex> lock(mtx);
            while (!stopRequested) {
                cv.wait(lock, [this] { return eventOccurred || stopRequested; });
                if (stopRequested) break;

                checkAndActivate();
                eventOccurred = false;
            }
        });
    }
}

void WarningSystem::stop() {
    if (warningThread.joinable()) {
        stopRequested = true;
        cv.notify_one();
        warningThread.join();
    }
}

void WarningSystem::notifyEvent() {
    std::lock_guard<std::mutex> lock(mtx);
    eventOccurred = true;
    cv.notify_one();
}

}
// need to define all four methods below. Ask Saleem , don't want to mess with other files. 
void WarningSystem::checkAndActivate() {
    if (!isInitialized) return;

    bool isCarIncoming = cameraSensor.isCarIncoming();
    bool isPedestrianCrossing = ultrasonicSensor.isPedestrianDetected(); 
    auto carTrafficLightState = trafficControlSystem.getCarTrafficLightState(); 
    auto pedestrianLightState = pedestriansTrafficLightSystem.getCurrentState(); 

    // Determine if the warning should be activated based on the refined logic
    bool shouldActivateWarning = 
        (isCarIncoming && isPedestrianCrossing) ||
        (carTrafficLightState == TrafficControlSystem::State::CAR_GREEN && isPedestrianCrossing) ||
        (pedestrianLightState == PedestriansTrafficLightSystem::State::PEDESTRIAN_RED && isPedestrianCrossing);

    if (shouldActivateWarning) {
        activate();
    } else {
        deactivate();
    }
}

