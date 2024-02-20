//
// Created by Saleem Hamo on 20/02/2024.
//
#include "../../models/TrafficLight.h"
#include "../SystemInterface.h"


class PedestriansTrafficLightSystem : public TrafficLight, public SystemInterface {
public:
    // Constructor
    PedestriansTrafficLightSystem(int redPin, int greenPin);

    // ISystem interface methods
    void initialize() override;

    void activate() override;

    void deactivate() override;

    // Additional methods specific to pedestrian traffic light system
};
