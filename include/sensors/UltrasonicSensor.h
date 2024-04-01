#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <pigpio.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    ~UltrasonicSensor();
    void initialize();
    float calculateDistance();
    bool isMotionDetected(float distanceThreshold = 0.2f); // Threshold in meters

private:
    int triggerPin, echoPin;
    float lastDistance = 0.0f;
    std::chrono::steady_clock::time_point lastCheck = std::chrono::steady_clock::now();
    static void sonarReceiveAlertFunction(int gpio, int level, uint32_t tick, void* user);
    uint32_t startTick, endTick;
    bool measuring = false;

    void sendPulse();
    static float timeToDistance(uint32_t time);
};
