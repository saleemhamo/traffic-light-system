//
// Created by Saleem Hamo on 20/02/2024.
//
#include <mutex>
#include <condition_variable>
#include "PedestriansTrafficLightSystem.h"
#include "CarsTrafficLightSystem.h"
#include "CheckingSystem.h"
#include "WarningSystem.h"

class MainSystem {
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool carLightGreen = true; // Initial state, car light is green
    CarsTrafficLightSystem carsTrafficLight;
    PedestriansTrafficLightSystem pedestriansTrafficLight;
    CheckingSystem checkingSystem;
    WarningSystem warningSystem;

public:
    MainSystem();

    ~MainSystem();

    void initialize();

    void run();

//    MainSystem();
    void runSystems(); // Starts and manages the traffic systems
};