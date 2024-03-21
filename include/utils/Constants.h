//
// Created by Saleem Hamo on 20/02/2024.
//

#ifndef CONSTANTS_H // If CONSTANTS_H is not defined
#define CONSTANTS_H // Define CONSTANTS_H

namespace Constants {
    constexpr int PedestriansTrafficLightRedPin = 7;
    constexpr int PedestriansTrafficLightGreenPin = 11;
    constexpr int CarsTrafficLightRedPin = 29;
    // constexpr int CarsTrafficLightRedPin = 27; // TODO: yellow PIN CORRECTED
    constexpr int CarsTrafficLightGreenPin = 28;
    // Traffic ultrasonic
    constexpr int CheckingSystemUltrasonic1TriggerPin = 30;
    constexpr int CheckingSystemUltrasonic1EchoPin = 31;
    // Pedestrian ultrasonic
    constexpr int CheckingSystemUltrasonic2TriggerPin = 3;
    constexpr int CheckingSystemUltrasonic2EchoPin = 2;
    constexpr int CheckingSystemButtonPin = 21;
    // All three warning system leds are connected to 25, 24 and 23
    constexpr int WarningSystemLedPin = 25;
    constexpr int WarningSystemLed2Pin = 24;
    constexpr int WarningSystemLed3Pin = 23;
    constexpr int WarningSystemBuzzerPin = 14;

    // Add more constants here
}

#endif // End of the header guard
