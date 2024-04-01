// Created by Saleem Hamo on 26/02/2024.
#include "sensors/UltrasonicSensor.h"
#include <chrono>
#include <thread>
#include <iostream>

#ifdef RASPBERRY_PI
#include <pigpio.h>
#else
#include "pigpio_stub.h"
#endif

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin)
    : triggerPin(triggerPin), echoPin(echoPin), motionCallback(nullptr),
      isMonitoring(true), lastDistance(0.0f), distanceThreshold(0.2f)
{
    initialize();
}

UltrasonicSensor::~UltrasonicSensor()
{
    // Clean up pigpio resources, only on Raspberry Pi
#ifdef RASPBERRY_PI
    gpioTerminate();
#endif
}

void UltrasonicSensor::initialize()
{
    // Initialize pigpio and set pin modes, only on Raspberry Pi
#ifdef RASPBERRY_PI
    if (gpioInitialise() < 0)
    {
        std::cerr << "Error: Initialisation of the GPIO Failed." << std::endl;
        return;
    }

    // Set pin modes for trigger and echo pins
    gpioSetMode(triggerPin, PI_OUTPUT);
    gpioSetMode(echoPin, PI_INPUT);
    gpioSetAlertFunc(echoPin, sonarReceiveAlertFunction);
#endif
    // More initialization as necessary
}

void UltrasonicSensor::registerMotionCallback(MotionDetectedCallback callback)
{
    this->motionCallback = callback;
}

bool UltrasonicSensor::isMotionDetected()
{
    if (!isMonitoring)
        return false;

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCheck).count() < 100)
    {
        // Check the sensor at most every 100 ms
        return false;
    }

    lastCheck = now;
    float currentDistance = calculateDistance();

    std::cout << "Current distance" << currentDistance << std::endl;
    std::cout << "lastDistance" << lastDistance << std::endl;
    if (abs(currentDistance - lastDistance) >= distanceThreshold)
    {
        if (motionCallback)
        {
            motionCallback(); // Call the callback if motion is detected
        }
    }

    lastDistance = currentDistance;
    return abs(currentDistance - lastDistance) >= distanceThreshold;
}

void UltrasonicSensor::sendPulse()
{
#ifdef RASPBERRY_PI
    gpioWrite(triggerPin, 1);
    usleep(10);
    gpioWrite(triggerPin, 0);
#endif
}

float UltrasonicSensor::calculateDistance()
{
#ifdef RASPBERRY_PI
    static uint32_t setTick;
    uint32_t diff;
    double dist;

    sendPulse();

    while (setTick == 0)
    {
        usleep(10); // Small delay to prevent busy waiting
    }

    diff = gpioTick() - setTick;
    dist = diff * 343.0 / 1000000.0 / 2;
    std::cout << "dist" << dist << std::endl;
    if (dist < 0)
        dist = 0;
    if (dist > 50)
        dist = -1;

    setTick = 0;
    return static_cast<float>(dist);
#else
    // Fallback or mock logic for non-RPi platforms
    return -1.0f; // Example fallback, adjust as needed
#endif
}

void UltrasonicSensor::sonarReceiveAlertFunction(int gpio, int level, uint32_t tick)
{
    static uint32_t setTick;
    if (level == 1)
    {
        setTick = tick;
    }
    else if (level == 0 && setTick != 0)
    {
        setTick = 0;
    }
}