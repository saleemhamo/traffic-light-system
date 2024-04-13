// Created by Saleem Hamo on 26/02/2024.
#include "sensors/UltrasonicSensor.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 * @brief Initializes an UltrasonicSensor and starts its initialization.
 * @param triggerPin GPIO pin used to trigger the sensor.
 * @param echoPin GPIO pin used to receive the echo signal.
 */
UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin) : triggerPin(triggerPin), echoPin(echoPin),
                                                                  startTick(0), endTick(0)
{
    initialize();
}
/**
 * @brief Cleans up GPIO resources.
 */
UltrasonicSensor::~UltrasonicSensor()
{
    gpioTerminate();
}
/**
 * @brief Sets up the sensor hardware and prepares it for operation.
 *
 * Initializes the GPIO library, sets the GPIO modes for the pins, and registers
 * the callback function for echo detection.
 */
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

    lastDistance = calculateDistance();// Measure distance initially to set a baseline.
}
}
/**
 * @brief Sends a trigger pulse to the sensor.
 *
 * Sends a brief high pulse to the trigger pin to start a distance measurement by the sensor.
 */
void UltrasonicSensor::sendPulse()
{
    gpioWrite(triggerPin, 1);
    std::this_thread::sleep_for(std::chrono::microseconds(10)); // 10us pulse
    gpioWrite(triggerPin, 0);
}
/**
 * @brief Measures the distance by timing how long it takes for an echo to return.
 *
 * This method triggers the sensor, waits for the echo, and calculates the distance
 * based on the time delay between sending the pulse and receiving the echo.
 * @return Distance to the nearest object in centimeters.
 */
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
/**
 * @brief Detects motion based on changes in measured distances.
 *
 * Measures the current distance and compares it to the previous measurement.
 * If the change exceeds the specified threshold and is within a practical range,
 * motion is considered detected.
 * @param distanceThreshold Minimum distance change to qualify as motion.
 * @return True if motion is detected, otherwise false.
 */
bool UltrasonicSensor::isMotionDetected(float distanceThreshold)
{
    float currentDistance = calculateDistance();
    // std::cout << "currentDistance: " << currentDistance << " " << triggerPin << std::endl;
    if (currentDistance < 0)
        return false; // Invalid reading
    bool motionDetected = std::fabs(currentDistance - lastDistance) >= distanceThreshold && currentDistance < 25.0f;
    lastDistance = currentDistance;
    return motionDetected;
}
/**
 * @brief Static callback function that handles GPIO pin level changes.
 *
 * This function is invoked by the GPIO library when an echo is detected. It records the time
 * of the rising and falling edges of the echo signal, allowing the distance calculation.
 * @param gpio GPIO pin associated with the echo.
 * @param level New pin level.
 * @param tick System tick count at the time of the level change.
 * @param user Pointer to the UltrasonicSensor instance.
 */
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
/**
 * @brief Converts a time interval (in microseconds) to a distance in centimeters.
 *
 * Uses the speed of sound in air (34320 cm/s) to calculate the distance based on the echo travel time.
 * The calculation assumes the sound travels to the target and back, so the distance is halved.
 * @param time Time in microseconds between the pulse and the echo.
 * @return The calculated distance in centimeters.
 */
float UltrasonicSensor::timeToDistance(uint32_t time)
{
    // Speed of sound in air (34320 cm/s) divided by 2 (to and back)
    return ((static_cast<float>(time) / 1000000.0f) * 34320.0f) / 2.0f;
}
