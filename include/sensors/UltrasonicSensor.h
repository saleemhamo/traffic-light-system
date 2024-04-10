#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#if defined(__linux__) && defined(__arm__)
#include <pigpio.h>
#else

#include "pigpio_stub.h"

#endif

class UltrasonicSensor
{
public:
    UltrasonicSensor(int triggerPin, int echoPin);

    ~UltrasonicSensor();

    void initialize();

    float calculateDistance();

    bool isMotionDetected(float distanceThreshold = 5.0f, int debounceMs = 500); // Threshold in cm

private:
    int triggerPin, echoPin;
    float lastDistance = 0.0f;
    std::chrono::steady_clock::time_point lastCheck = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point lastDetectionTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point lastMotionDetectedAt;

    static void sonarReceiveAlertFunction(int gpio, int level, uint32_t tick, void *user);

    uint32_t startTick, endTick;
    bool measuring = false;

    void sendPulse();

    static float timeToDistance(uint32_t time);
};
