//
// Created by Saleem Hamo on 20/02/2024.
//

#ifndef CONSTANTS_H // If CONSTANTS_H is not defined
#define CONSTANTS_H // Define CONSTANTS_H

namespace Constants {
    constexpr int PedestriansTrafficLightRedPin = 5;
    constexpr int PedestriansTrafficLightGreenPin = 6;
    constexpr int CarsTrafficLightRedPin = 13;
    constexpr int CarsTrafficLightGreenPin = 19;
    constexpr int CheckingSystemUltrasonic1TriggerPin = 23;
    constexpr int CheckingSystemUltrasonic1EchoPin = 23;
    constexpr int CheckingSystemUltrasonic2TriggerPin = 23;
    constexpr int CheckingSystemUltrasonic2EchoPin = 23;
    constexpr int CheckingSystemButtonPin = 25;
    constexpr int WarningSystemLedPin = 12;
    constexpr int WarningSystemBuzzerPin = 18;
    // Add more constants here
}

#endif // End of the header guard