//
// Created by Saleem Hamo on 20/02/2024.
//
#include "models/TrafficLight.h"
#include "main/SystemInterface.h"
#include "utils/Constants.h"

class PedestriansTrafficLightSystem : public TrafficLight, public SystemInterface {
public:
    // Constructor
    PedestriansTrafficLightSystem();

    static const int redPin = Constants::PedestriansTrafficLightGreenPin;
    static const int greenPin = Constants::PedestriansTrafficLightRedPin;

    // ISystem interface methods
    void initialize() override;

    void activate() override;

    void deactivate() override;

    // Additional methods specific to pedestrian traffic light system
};
