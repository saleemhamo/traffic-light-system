//
// Created by Saleem Hamo on 20/02/2024.
//

#ifndef CONSTANTS_H // If CONSTANTS_H is not defined
#define CONSTANTS_H // Define CONSTANTS_H

namespace Constants {
    constexpr int PedestriansTrafficLightRedPin = 7;
    constexpr int PedestriansTrafficLightGreenPin = 11;
    constexpr int CarsTrafficLightRedPin = 29;
//    constexpr int CarsTrafficLightRedPin = 27; // TODO: yellow PIN CORRECTED
    constexpr int CarsTrafficLightGreenPin = 28;
    constexpr int CheckingSystemUltrasonic1TriggerPin = 30;
    constexpr int CheckingSystemUltrasonic1EchoPin = 31; // Traffic ultrasonic
    constexpr int CheckingSystemUltrasonic2TriggerPin = 3;
    constexpr int CheckingSystemUltrasonic2EchoPin = 2; //Pedestrian ultrasonic
    constexpr int CheckingSystemButtonPin = 21; //push botton
    constexpr int WarningSystemLedPin = 25; //25 24 23
    constexpr int WarningSystemBuzzerPin = 14;
    // Add more constants here
    // buzzer 14
    // 
}

#endif // End of the header guard
