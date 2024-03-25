#ifndef MAINSYSTEM_H
#define MAINSYSTEM_H

#include <mutex>
#include <thread>
#include <atomic>
#include "utils/SystemTimer.h"
#include "CarsTrafficLightSystem.h"
#include "PedestriansTrafficLightSystem.h"
#include "CheckingSystem.h"
#include "WarningSystem.h"

class MainSystem {
public:
    enum TrafficLightState {
        OFF,
        CARS_RED_PEDESTRIANS_GREEN,
        CARS_GREEN_PEDESTRIANS_RED,
        EMERGENCY_STATE
    };

    void startTimer(long millisecs, cppTimerType_t type = PERIODIC)
    {
        m_timer.startTimer(millisecs, type);
    }

    void stopTimer()
    {
        m_timer.stopTimer();
    }

    void handleTimerEvent()
    {
        // Implement the desired behavior when the timer fires
        // This could involve changing the state of the traffic lights or performing other actions
    }

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
    SystemTimer m_timer{*this};
    CheckingSystem checkingSystem;
    WarningSystem warningSystem;

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