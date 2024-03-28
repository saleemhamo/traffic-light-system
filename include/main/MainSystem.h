#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <mutex>
#include <thread>
#include <atomic>
#include "CarsTrafficLightSystem.h"
#include "PedestriansTrafficLightSystem.h"
#include "CheckingSystem.h"
#include "WarningSystem.h"
#include "utils/Timer.cpp"
#include <iostream>

class MainSystem {
public:
    enum TrafficLightState {
        OFF,
        CARS_RED_PEDESTRIANS_GREEN,
        CARS_GREEN_PEDESTRIANS_RED
    };

    MainSystem();

    ~MainSystem();

    void initialize();

    void runSystems();

    void shutdown();

private:
    TrafficLightState trafficLightState;
    Timer carsTrafficLightTimer;
    Timer pedestriansTrafficLightTimer;
    Timer mainSystemTimer;

    CarsTrafficLightSystem carsTrafficLight;
    PedestriansTrafficLightSystem pedestriansTrafficLight;
    CheckingSystem checkingSystem;
    WarningSystem warningSystem;

    std::thread carsThread;
    std::thread pedestriansThread;
    std::thread checkingThread;
    std::thread warningThread;

    std::atomic<bool> isTrafficLightRunningInNormalBehaviour;


    void onCarsMotionDetected();

    void onPedestriansMotionDetected();

    void onPedestriansButtonClicked();

    void enableTrafficLightsNormalBehaviour();

    void disableTrafficLightsNormalBehaviour();

    void runTrafficLightsNormalBehaviour();

    void turnCarsGreen();

    void turnPedestriansGreen();

    void turnAllRed();

//    void resetTrafficLightTimer();
};

#endif // MAINSYSTEM_H