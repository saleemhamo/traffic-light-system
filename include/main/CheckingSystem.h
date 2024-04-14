//
// Created by Saleem Hamo on 20/02/2024.
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


class CheckingSystem {
public:
    CheckingSystem();

    ~CheckingSystem();

    void initialize();

    void run();

    void deactivate();

    void onPedestriansButtonPress();

    void registerCarsMotionCallback(const std::function<void()> &callback);

    void registerPedestriansMotionCallback(const std::function<void()> &callback);

    void registerPedestriansButtonCallback(const std::function<void()> &callback);

    void enablePedestriansMotionDetection();

    void disablePedestriansMotionDetection();

    void enableCarsMotionDetection();

    void disableCarsMotionDetection();

    void enablePedestriansButton();

    void disablePedestriansButton();

    void enableSensing();

    void disableSensing();

    void monitorPedestrian();

    void monitorRoad();

private:
    std::atomic<bool> isActive;
    std::atomic<bool> monitorPedestriansActive;
    std::atomic<bool> monitorRoadsActive;
    std::atomic<bool> pedestriansButtonEnabled;

    std::function<void()> carsMotionDetected;
    std::function<void()> pedestriansMotionDetected;
    std::function<void()> pedestriansButtonClicked;

    //    CameraSensor camera;
    UltrasonicSensor pedestrianSensor;
    UltrasonicSensor roadSensor;
    PushButton pedestriansPushButton;

    std::thread pedestrianThread;
    std::thread roadThread;



    void monitorPedestriansButton();
};

#endif // CHECKINGSYSTEM_H
