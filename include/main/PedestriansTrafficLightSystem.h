#ifndef PEDESTRIANSTRAFFICLIGHTSYSTEM_H
#define PEDESTRIANSTRAFFICLIGHTSYSTEM_H

#include "models/TrafficLight.h"
#include <atomic>
#include <thread>

class PedestriansTrafficLightSystem : public TrafficLight {
public:
    PedestriansTrafficLightSystem();

    void initialize();

    void run();

    void deactivate();

private:
    std::atomic<bool> isActive;
};

#endif // PEDESTRIANSTRAFFICLIGHTSYSTEM_H
