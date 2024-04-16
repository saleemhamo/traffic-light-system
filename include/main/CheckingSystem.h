//
// Created by Saleem Hamo on 20/02/2024. Docunebtation by Miguel Rosa
// 
#ifndef CHECKINGSYSTEM_H
#define CHECKINGSYSTEM_H


#include "main/interfaces/SystemInterface.h"
#include "sensors/CameraSensor.h"
#include "sensors/UltrasonicSensor.h"
#include "sensors/PushButton.h"
#include <thread>
#include <atomic>
#include <functional>
#include "utils/Constants.h"
#include "utils/Logger.h"

/**
 * @file CheckingSystem.h
 * @brief Class to manage monitoring and control systems for pedestrian and vehicle traffic.
 *
 * This class integrates various sensors and controls to manage and monitor traffic systems effectively,
 * incorporating threads for asynchronous operation.
 */

/**
 * @class CheckingSystem
 * @brief Manages and operates the monitoring system for both pedestrian and vehicle detection.
 *
 * Integrates multiple sensors and provides functionalities to register callbacks, activate or deactivate detection,
 * and manage system states through an interface designed for real-time traffic monitoring.
 */

class CheckingSystem {
public:
    CheckingSystem();  ///< Constructor to initialize the system with default states and sensor configurations.
    ~CheckingSystem(); ///< Destructor to clean up resources, ensuring all threads are joined if necessary.

    void initialize(); ///< Initialize sensors and system components.
    void run();        ///< Start the system's main operation loop.
    void deactivate(); ///< Safely deactivate and shutdown all system operations.

    void onPedestriansButtonPress(); ///< Handler for pedestrian button presses.

    void registerCarsMotionCallback(const std::function<void()> &callback);

    void registerPedestriansMotionCallback(const std::function<void()> &callback);

    void registerPedestriansButtonCallback(const std::function<void()> &callback);

    void enablePedestriansMotionDetection();

    void disablePedestriansMotionDetection();

    void enableCarsMotionDetection();

    void disableCarsMotionDetection();

    void enablePedestriansButton();

    void disablePedestriansButton();

    void enableSensing(); ///< Enable all sensors and detection mechanisms.
    void disableSensing(); ///< Disable all sensors and detection mechanisms.



private:
    std::atomic<bool> isActive; ///< Indicates if the system is currently active.
    std::atomic<bool> monitorPedestriansActive; ///< State of pedestrian monitoring.
    std::atomic<bool> monitorRoadsActive; ///< State of vehicle monitoring.
    std::atomic<bool> pedestriansButtonEnabled; ///< State of the pedestrian button.


    std::function<void()> carsMotionDetected; ///< Callback for vehicle detection.
    std::function<void()> pedestriansMotionDetected; ///< Callback for pedestrian detection.
    std::function<void()> pedestriansButtonClicked; ///< Callback for pedestrian button press.

    //    CameraSensor camera;
    UltrasonicSensor pedestrianSensor; ///< Sensor to detect pedestrian movement.
    UltrasonicSensor roadSensor; ///< Sensor to detect vehicle movement.
    PushButton pedestriansPushButton; ///< Button for pedestrian interaction.

    std::thread pedestrianThread; ///< Thread for monitoring pedestrians.
    std::thread roadThread; ///< Thread for monitoring vehicles.

    void monitorPedestrian(); ///< Function to monitor pedestrian movements continuously.
    void monitorRoad(); ///< Function to monitor vehicle movements continuously.

    void monitorPedestriansButton();
};

#endif // CHECKINGSYSTEM_H
