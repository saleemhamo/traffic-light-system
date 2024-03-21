//
// Created by Saleem Hamo on 26/02/2024.
//
#include "sensors/UltrasonicSensor.h"
#include <chrono>
#include <thread>
#include <iostream>

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin)
        : triggerPin(triggerPin), echoPin(echoPin), motionCallback(nullptr) {
}

UltrasonicSensor::~UltrasonicSensor() {
    // Clean up resources, stop pigpio, etc.
}

void UltrasonicSensor::initialize() {
    // Initialize pigpio and set pin modes, only on Raspberry Pi
#ifdef RASPBERRY_PI
    gpioInitialise();
    gpioSetMode(triggerPin, PI_OUTPUT);
    gpioSetMode(echoPin, PI_INPUT);
#endif
    // More initialization as necessary
}

void UltrasonicSensor::registerMotionCallback(MotionDetectedCallback callback) {
    this->motionCallback = callback;
}

bool UltrasonicSensor::isMotionDetected() {
    if (!isMonitoring) return false;

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastCheck).count() < 100) {
        // Check the sensor at most every 100 ms
        return false;
    }
    lastCheck = now;
    bool isMotionDetected = false;

    float currentDistance = calculateDistance();
    if (abs(currentDistance - lastDistance) >= distanceThreshold) {
        isMotionDetected = true;
//        if (motionCallback) {
//            motionCallback(); // Call the callback if motion is detected
//        }
    }
    lastDistance = currentDistance;

    return isMotionDetected;
}

void UltrasonicSensor::sendPulse() {
    // Code to send a pulse through the trigger pin
}

float UltrasonicSensor::calculateDistance() {
#ifdef RASPBERRY_PI
    // Ensure trigger pin is LOW for a short period to ensure a clean HIGH pulse
    gpioWrite(triggerPin, 0);
    gpioDelay(2); // Delay 2 microseconds for a clean pulse

    // Send a pulse
    gpioWrite(triggerPin, 1);
    gpioDelay(10); // 10-microsecond pulse to trigger the measurement
    gpioWrite(triggerPin, 0);

    // Wait for echo start
    int timeout = 5000; // Timeout after 5 ms if no echo is received
    int startTime = gpioTick();
    while (gpioRead(echoPin) == 0) {
        if ((gpioTick() - startTime) > timeout) {
            return -1.0f; // Return -1 to indicate timeout/error
        }
    }

    // Measure the time until the echo is received
    int echoStart = gpioTick();
    while (gpioRead(echoPin) == 1) {
        if ((gpioTick() - echoStart) > timeout) {
            return -1.0f; // Return -1 to indicate timeout/error
        }
    }
    int echoEnd = gpioTick();

    // Calculate the duration of the echo pulse
    long timeForEcho = echoEnd - echoStart;

    // Convert time to distance (cm). The "58" is a rough conversion factor; check your sensor's specs.
    float distance = timeForEcho / 58.0;

    return distance;

#else
    // Fallback or mock logic for non-RPi platforms
    // You might want to return a mock distance or simulate sensor behavior
    return -1.0f; // Example fallback, adjust as needed
#endif
}
