#ifndef ULTRASONICSENSOR_H
#define ULTRASONICSENSOR_H

// Including the pigpio library conditionally
#ifdef RASPBERRY_PI
#include <pigpio.h>
#else

#include "pigpio_stub.h" // This will be your stub for non-RPi platforms.

#endif

#include <functional>

class UltrasonicSensor {
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

    std::chrono::steady_clock::time_point lastMeasurementTime;
    int measurementInterval = 100; // Time between measurements in milliseconds

    void sendPulse();
    float calculateDistance();
};

#endif // ULTRASONICSENSOR_H
