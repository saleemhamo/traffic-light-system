#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

// Including the pigpio library conditionally
#ifdef RASPBERRY_PI
#include <pigpio.h>
#else
#include "pigpio_stub.h"
#include <chrono>
#endif

#include <functional>

class UltrasonicSensor
{
public:
    using MotionDetectedCallback = std::function<void()>;

    UltrasonicSensor(int triggerPin, int echoPin);
    ~UltrasonicSensor();

    void initialize();
    void registerMotionCallback(MotionDetectedCallback callback);
    bool isMotionDetected();

private:
    int triggerPin, echoPin;
    MotionDetectedCallback motionCallback;
    float distanceThreshold; // Change in distance to trigger motion detection
    std::chrono::steady_clock::time_point lastCheck;
    float lastDistance;
    bool isMonitoring;

    void sendPulse();
    float calculateDistance();
    static void sonarReceiveAlertFunction(int gpio, int level, uint32_t tick);
};

#endif // ULTRASONICSENSOR_H