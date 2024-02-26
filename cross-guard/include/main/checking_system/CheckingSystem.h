//
// Created by Saleem Hamo on 20/02/2024.
//

#include "main/SystemInterface.h"
#include "sensors/CameraSensor.h"
#include "sensors/UltrasonicSensor.h"
#include <thread>
#include <atomic>

class CheckingSystem : public SystemInterface {
public:
    CheckingSystem(
            int ultrasonic1TriggerPin,
            int ultrasonic1EchoPin,
            int ultrasonic2TriggerPin,
            int ultrasonic2EchoPin,
            int buttonPin
    );

    ~CheckingSystem();

    void initialize() override;

    void activate() override;

    void deactivate() override;

    void monitorPedestrians();

    void checkRoadStatus();

private:
    int ultrasonic1TriggerPin;
    int ultrasonic1EchoPin;
    int ultrasonic2TriggerPin;
    int ultrasonic2EchoPin;
    int buttonPin;

//    CameraSensor camera;
//    UltrasonicSensor pedestrianSensor;
//    UltrasonicSensor roadSensor;

    std::thread pedestrianThread;
    std::atomic<bool> active{false};
};
