//
// Created by Saleem Hamo on 20/02/2024.
//

#ifndef CONSTANTS_H // If CONSTANTS_H is not defined
#define CONSTANTS_H // Define CONSTANTS_H

namespace Constants
{
    // Cars traffic
    constexpr int CarsTrafficLightRedPin = 21;
    constexpr int CarsTrafficLightYellowPin = 16;
    constexpr int CarsTrafficLightGreenPin = 20;
    constexpr int CheckingSystemUltrasonic1TriggerPin = 23;
    constexpr int CheckingSystemUltrasonic1EchoPin = 24;
    constexpr int UnusedPin = 1;

    // Pedestrian traffic
    constexpr int PedestriansTrafficLightRedPin = 4;
    constexpr int PedestriansTrafficLightGreenPin = 7;
    constexpr int CheckingSystemUltrasonic2TriggerPin = 14;
    constexpr int CheckingSystemUltrasonic2EchoPin = 15;

    /* All three warning system leds are connected
    to 25, 24 and 23 and other such as buzzer and button */
    constexpr int WarningSystemLedPin = 26;
    constexpr int WarningSystemLed2Pin = 19;
    constexpr int WarningSystemLed3Pin = 13;
    constexpr int WarningSystemBuzzerPin = 11;
    constexpr int CheckingSystemButtonPin = 6;
    
    // Add more constants here when needed
    constexpr float CheckingSystemPedestrianDistanceThreshold = 0.5f;
    constexpr float CheckingSystemCarDistanceThreshold = 0.5f;
} // End of namespace Constants

#endif // End of the header guard
