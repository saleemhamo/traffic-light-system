#ifndef CARSTRAFFICLIGHTSYSTEM_H
#define CARSTRAFFICLIGHTSYSTEM_H

#include "models/TrafficLight.h"
#include <atomic>
#include <thread>

class CarsTrafficLightSystem : public TrafficLight {
public:
    CarsTrafficLightSystem();

    void initialize();

    void run();

    void deactivate();

private:
    std::atomic<bool> isActive;
};

#endif // CARSTRAFFICLIGHTSYSTEM_H
