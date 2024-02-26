//
// Created by Saleem Hamo on 20/02/2024.
//

#include "main/MainSystem.h"

MainSystem::MainSystem() :
        carsTrafficLight(&mtx, &cv, &carLightGreen),
        pedestriansTrafficLight(&mtx, &cv, &carLightGreen) {}


MainSystem::~MainSystem() {
    // Destructor for cleaning up resources
}

void MainSystem::initialize() {
    // Initialize all subsystems
    pedestriansTrafficLight.initialize();
    carsTrafficLight.initialize();
    checkingSystem.initialize();
    warningSystem.initialize();

    // Initialize any other necessary state or resources
}

void MainSystem::run() {
    // Start running all subsystems, potentially in separate threads if needed
    pedestriansTrafficLight.activate();
    carsTrafficLight.activate();
    checkingSystem.activate();
    warningSystem.activate();

    // Here you would include logic for the systems to communicate and change states
    // This could be done using observer patterns, events, or direct method calls based on the state
}

void MainSystem::runSystems() {
    std::thread carsThread(&CarsTrafficLightSystem::run, &carsTrafficLight);
    std::thread pedestriansThread(&PedestriansTrafficLightSystem::run, &pedestriansTrafficLight);

    carsThread.join();
    pedestriansThread.join();
}
