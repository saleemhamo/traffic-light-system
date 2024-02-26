//
// Created by Saleem Hamo on 20/02/2024.
//
#include "models/TrafficLight.h"
#include "main/SystemInterface.h"
#include "utils/Constants.h"

class CarsTrafficLightSystem : public TrafficLight, public SystemInterface {
public:
    // Constructor
    CarsTrafficLightSystem();

    static const int redPin = Constants::CarsTrafficLightRedPin;
    static const int greenPin = Constants::CarsTrafficLightGreenPin;

    // ISystem interface methods
    void initialize() override;

    void activate() override;

    void deactivate() override;

    // Additional methods specific to car traffic light system


};

