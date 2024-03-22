#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <mutex>
#include <thread>
#include <atomic>
#include "CarsTimer.h>
#include "PedestriansTimer.h"
#include "CarsTrafficLightSystem.h"
#include "PedestriansTrafficLightSystem.h"
#include "CheckingSystem.h"
#include "WarningSystem.h"

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
    std::mutex mtx;
    std::atomic<bool> running;

    CarsTrafficLightSystem carsTrafficLight;
    PedestriansTrafficLightSystem pedestriansTrafficLight;
    CheckingSystem checkingSystem;
    WarningSystem warningSystem;
    CarsTimer carsTimer;
    PedestriansTimer pedestriansTimer;

    std::thread carsThread;
    std::thread pedestriansThread;
    std::thread checkingThread;
    std::thread warningThread;

    std::atomic<bool> isTrafficLightRunningInNormalBehaviour;

    void deactivateSubsystems();

    void onCarsMotionDetected();

    void onPedestriansMotionDetected();

    void manageTrafficStates();

    void onPedestriansButtonClicked();

    void enableTrafficLightsNormalBehaviour();

    void disableTrafficLightsNormalBehaviour();

    void runTrafficLightsNormalBehaviour();

    void manageTrafficStates();
};

#endif // MAINSYSTEM_H