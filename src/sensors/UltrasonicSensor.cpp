// Created by Saleem Hamo on 26/02/2024.
#include "sensors/UltrasonicSensor.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin),
                                                                  startTick(0), endTick(0)
{
    initialize();
}

UltrasonicSensor::~UltrasonicSensor()
{
    gpioTerminate();
}

void UltrasonicSensor::initialize()
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "GPIO Initialization failed." << std::endl;
        throw std::runtime_error("Failed to initialize GPIO");
    }

    gpioSetMode(triggerPin, PI_OUTPUT);
    gpioSetMode(echoPin, PI_INPUT);
    gpioSetAlertFuncEx(echoPin, sonarReceiveAlertFunction, this);

    lastDistance = calculateDistance();
}

void UltrasonicSensor::sendPulse()
{
    gpioWrite(triggerPin, 1);
    std::this_thread::sleep_for(std::chrono::microseconds(10)); // 10us pulse
    gpioWrite(triggerPin, 0);
}

float UltrasonicSensor::calculateDistance()
{
    sendPulse();
    measuring = true;
    auto startTime = std::chrono::steady_clock::now();
    while (measuring)
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
        if (elapsed > 100)
        { // Timeout after 100 ms
            measuring = false;
        }
    }
    uint32_t diff = endTick > startTick ? endTick - startTick : 0;
    return timeToDistance(diff);
}

bool UltrasonicSensor::isMotionDetected(float distanceThreshold) {
    auto now = std::chrono::steady_clock::now();
    // Check if enough time has elapsed since the last detection
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastDetectionTime).count() < 500) { // 500 ms cooldown
        return false;
    }

    float currentDistance = calculateDistance();
    if (currentDistance < 0)
        return false; // Invalid reading

    bool motionDetected = std::fabs(currentDistance - lastDistance) >= distanceThreshold && currentDistance < 25.0f;
    if (motionDetected) {
        lastDistance = currentDistance;
        lastDetectionTime = now; // Update the last detection time
    }
    return motionDetected;
}

void UltrasonicSensor::sonarReceiveAlertFunction(int gpio, int level, uint32_t tick, void *user)
{
    UltrasonicSensor *sensor = static_cast<UltrasonicSensor *>(user);
    if (level == 1)
    { // Rising edge
        sensor->startTick = tick;
    }
    else if (level == 0)
    { // Falling edge
        sensor->endTick = tick;
        sensor->measuring = false;
    }
}

float UltrasonicSensor::timeToDistance(uint32_t time)
{
    // Speed of sound in air (34320 cm/s) divided by 2 (to and back)
    return ((static_cast<float>(time) / 1000000.0f) * 34320.0f) / 2.0f;
}
