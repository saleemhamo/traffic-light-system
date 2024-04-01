//
// Created by Saleem Hamo on 20/02/2024.
// Updated by Miguel Rosa on 23/03/2024\
#ifndef WARNING_SYSTEM_H
#define WARNING_SYSTEM_H

//

#include <mutex>
#include <condition_variable>
#include <thread>

#include "sensors/CameraSensor.h" 
#include "sensors/UltrasonicSensor.h"
#include "TrafficControlSystem.h" 
#include "PedestriansTrafficLightSystem.h"
#include "actuators/LED.h" 
#include "actuators/Buzzer.h" 
#include "utils/Constants.h" 
#include "SystemInterface.h"

class WarningSystem : public SystemInterface { // Inherit from SystemInterface
public:
    WarningSystem(CameraSensor& camera, UltrasonicSensor& ultrasonic, TrafficControlSystem& trafficSystem);
    virtual ~WarningSystem(); // Implement the virtual destructor

    // Implement SystemInterface's pure virtual functions
    virtual void initialize() override;
    virtual void activate() override;
    virtual void deactivate() override;

    void run();
    void stop();
    void notifyEvent(); // Method to be called to trigger the warning system check

private:
    std::mutex mtx;
    std::condition_variable cv;
    bool eventOccurred;
    bool stopRequested;
    std::thread warningThread;

    LED warningLED;
    Buzzer warningBuzzer;
    bool isInitialized;

    // Sensors and system references
    CameraSensor& cameraSensor;
    UltrasonicSensor& ultrasonicSensor;
    TrafficControlSystem& trafficControlSystem;

    void checkAndActivate();
};

#endif // WARNING_SYSTEM_H
