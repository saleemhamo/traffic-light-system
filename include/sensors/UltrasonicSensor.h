#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

#if defined(__linux__) && defined(__arm__)
#include <pigpio.h>
#else

#include "pigpio_stub.h"

#endif

/**
 * @class UltrasonicSensor
 * @brief Provides functionality for interfacing with an ultrasonic sensor for distance measurement.
 *
 * This class handles initialization, distance measurement, and motion detection using an ultrasonic sensor
 * connected to specified GPIO pins on a Raspberry Pi. It encapsulates details of sending pulses and measuring
 * response times to calculate distances.
 */
class UltrasonicSensor
{
public:
    /**
     * @brief Constructs an UltrasonicSensor with specified GPIO pins.
     * @param triggerPin The GPIO pin used to trigger the sensor.
     * @param echoPin The GPIO pin used to receive the echo signal from the sensor.
     */
    UltrasonicSensor(int triggerPin, int echoPin);
    /**
     * @brief Destructs the UltrasonicSensor instance.
     *
     * Ensures proper shutdown of the GPIO functionality, primarily used on systems
     * where GPIO pins require manual cleanup.
     */
    ~UltrasonicSensor();
     /**
     * @brief Initializes the sensor and prepares it for distance measurements.
     *
     * Sets the GPIO modes for the trigger and echo pins, and registers the echo
     * reception callback.
     */
    void initialize();
    /**
     * @brief Calculates the distance to an object in front of the sensor.
     * @return The measured distance in centimeters.
     */
    float calculateDistance();
     /**
     * @brief Checks for motion detection based on changes in measured distance.
     * @param distanceThreshold The minimum change in distance to consider as motion (default is 5.0 cm).
     * @return True if motion is detected, false otherwise.
     */
    bool isMotionDetected(float distanceThreshold = 5.0f); // Threshold in cm

private:
    int triggerPin, echoPin;///< GPIO pin number used for triggering the sensor. GPIO pin number used for receiving the echo.
    float lastDistance = 0.0f;///< Last measured distance.
    std::chrono::steady_clock::time_point lastCheck = std::chrono::steady_clock::now();///< Last time the distance was checked.

    static void sonarReceiveAlertFunction(int gpio, int level, uint32_t tick, void *user);///< Callback function for receiving echo.

     uint32_t startTick, endTick; ///< Timestamps captured at the start and end of echo.
    bool measuring = false; ///< Flag to indicate if measurement is ongoing.

    /**
     * @brief Sends a pulse to trigger the sensor.
     */
    void sendPulse();

    /**
     * @brief Converts time duration into a distance.
     * @param time Time in microseconds between pulse send and echo receive.
     * @return Distance in centimeters.
     */
    static float timeToDistance(uint32_t time);
};

#endif // ULTRASONICSENSOR_H
