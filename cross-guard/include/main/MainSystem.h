//
// Created by Saleem Hamo on 20/02/2024.
//

#include "./pedestrians_traffic_light_system/PedestriansTrafficLightSystem.h"
#include "./cars_traffic_light_system/CarsTrafficLightSystem.h"
#include "./checking_system/CheckingSystem.h"
#include "./warning_system/WarningSystem.h"

class MainSystem {
public:
    MainSystem();

    ~MainSystem();

    void initialize();

    void run();

private:
    PedestriansTrafficLightSystem pedestriansTrafficLight;
    CarsTrafficLightSystem carsTrafficLight;
    CheckingSystem checkingSystem;
    WarningSystem warningSystem;

    // You can add more members for thread management if needed
};