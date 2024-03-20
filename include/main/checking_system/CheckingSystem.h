//
// Created by Saleem Hamo on 20/02/2024.
//

#include "main/SystemInterface.h"
#include "sensors/CameraSensor.h"
#include "sensors/UltrasonicSensor.h"
#include <thread>
#include <atomic>
#include "utils/Constants.h"

class CheckingSystem : public SystemInterface {
public:
    CheckingSystem();

    ~CheckingSystem();

    static const int ultrasonic1TriggerPin = Constants::CheckingSystemUltrasonic1TriggerPin;
    static const int ultrasonic1EchoPin = Constants::CheckingSystemUltrasonic1EchoPin;
    static const int ultrasonic2TriggerPin = Constants::CheckingSystemUltrasonic2TriggerPin;
    static const int ultrasonic2EchoPin = Constants::CheckingSystemUltrasonic2EchoPin;
    static const int buttonPin = Constants::CheckingSystemButtonPin;

    void initialize() override;

    void activate() override;

    void deactivate() override;

    void monitorPedestrians();

    void checkRoadStatus();

private:
//    CameraSensor camera;
//    UltrasonicSensor pedestrianSensor;
//    UltrasonicSensor roadSensor;

    std::thread pedestrianThread;
    std::atomic<bool> active{false};
};
