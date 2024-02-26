//
// Created by Saleem Hamo on 20/02/2024.
//

#include "main/pedestrians_traffic_light_system/PedestriansTrafficLightSystem.h"
#include "main/cars_traffic_light_system/CarsTrafficLightSystem.h"
#include "main/checking_system/CheckingSystem.h"
#include "main/warning_system/WarningSystem.h"

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