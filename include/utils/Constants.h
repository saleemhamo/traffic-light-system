//
// Created by Saleem Hamo on 20/02/2024. Documented by Miguel Rosa
//

/**
 * @file Constants.h
 * @brief Defines a collection of constant values used for GPIO pin assignments and thresholds in a traffic control system.
 *
 * This file contains namespaces that define various constants including GPIO pin numbers for traffic lights,
 * ultrasonic sensors, and system control components like buttons and buzzers. These constants are used throughout
 * the project to maintain consistency and improve code readability by avoiding magic numbers.
 */

#ifndef CONSTANTS_H // If CONSTANTS_H is not defined
#define CONSTANTS_H // Define CONSTANTS_H

namespace Constants
{
    /**
     * @brief GPIO pin assignments for car traffic light control.
     */
    constexpr int CarsTrafficLightRedPin = 21;      ///< GPIO pin for car traffic red light.
    constexpr int CarsTrafficLightYellowPin = 16;   ///< GPIO pin for car traffic yellow light.
    constexpr int CarsTrafficLightGreenPin = 20;    ///< GPIO pin for car traffic green light.

    /**
     * @brief GPIO pin assignments for the first ultrasonic sensor in the checking system.
     */
    constexpr int CheckingSystemUltrasonic1TriggerPin = 23;  ///< Trigger pin for the first ultrasonic sensor.
    constexpr int CheckingSystemUltrasonic1EchoPin = 24;     ///< Echo pin for the first ultrasonic sensor.
    constexpr int UnusedPin = 1;                             ///< An unused pin, reserved for future use.

    /**
     * @brief GPIO pin assignments for pedestrian traffic light control.
     */
    constexpr int PedestriansTrafficLightRedPin = 4;         ///< GPIO pin for pedestrian traffic red light.
    constexpr int PedestriansTrafficLightGreenPin = 7;       ///< GPIO pin for pedestrian traffic green light.

    /**
     * @brief GPIO pin assignments for the second ultrasonic sensor in the checking system.
     */
    constexpr int CheckingSystemUltrasonic2TriggerPin = 14;  ///< Trigger pin for the second ultrasonic sensor.
    constexpr int CheckingSystemUltrasonic2EchoPin = 15;     ///< Echo pin for the second ultrasonic sensor.

    /**
     * @brief GPIO pin assignments for the warning system components.
     */
    constexpr int WarningSystemLedPin = 26;                  ///< GPIO pin for the first warning LED.
    constexpr int WarningSystemLed2Pin = 19;                 ///< GPIO pin for the second warning LED.
    constexpr int WarningSystemLed3Pin = 13;                 ///< GPIO pin for the third warning LED.
    constexpr int WarningSystemBuzzerPin = 11;               ///< GPIO pin for the warning system buzzer.
    constexpr int CheckingSystemButtonPin = 6;               ///< GPIO pin for the checking system button.

    /**
     * @brief Distance thresholds for the checking systems, defining the minimum change detected as motion.
     */
    constexpr float CheckingSystemPedestrianDistanceThreshold = 5.0f; ///< Distance threshold for the pedestrian checking system.
    constexpr float CheckingSystemCarDistanceThreshold = 5.0f;        ///< Distance threshold for the car checking system.

    // Additional constants can be added here when needed.
} // namespace Constants

#endif // CONSTANTS_H