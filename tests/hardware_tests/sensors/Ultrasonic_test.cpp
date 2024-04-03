#define BOOST_TEST_MODULE UltrasonicSensorTests
#include <boost/test/included/unit_test.hpp>

// Include the header file for the Ultrasonic class
#include "sensors/UltrasonicSensor.h"
#include "pigpio_stub.h"
#include "utils/Logger.h"

// Test the calculateDistance function of the Ultrasonic class
// This test assumes that the measureDistance function is working correctly
BOOST_AUTO_TEST_CASE(CalculateDistanceTest)
{
    Logger::init("test.log");

    // Create an instance of the Ultrasonic class
    const int triggerPin = 23;
    const int echoPin = 24;
    UltrasonicSensor sensor(triggerPin, echoPin);

    // Simulate a distance of 1 meter
    const uint32_t startTick = 0;
    const uint32_t endTick = 58823; // Time for 1 meter in microseconds

    // Call the private sonarReceiveAlertFunction to simulate sensor readings
    simulateCallback(echoPin, 1, startTick);
    simulateCallback(echoPin, 0, endTick);

    float distance = sensor.calculateDistance();
    BOOST_TEST(std::abs(distance - 1.0f) < 0.01f, "Distance calculation is incorrect");
}

// Test the isMotionDetected function of the Ultrasonic class
// This test assumes that the calculateDistance function is working correctly
BOOST_AUTO_TEST_CASE(MotionDetectionTest)
{
    Logger::init("test.log");

    // Create an instance of the Ultrasonic class
    const int triggerPin = 23;
    const int echoPin = 24;
    UltrasonicSensor sensor(triggerPin, echoPin);

    // Simulate no motion
    const uint32_t startTick1 = 0;
    const uint32_t endTick1 = 58823; // Time for 1 meter in microseconds

    simulateCallback(echoPin, 1, startTick1);
    simulateCallback(echoPin, 0, endTick1);

    bool motionDetected = sensor.isMotionDetected(0.2f); // Threshold of 0.2 meters
    BOOST_TEST(!motionDetected, "Motion should not be detected");

    // Simulate motion
    const uint32_t startTick2 = 0;
    const uint32_t endTick2 = 47058; // Time for 0.8 meters in microseconds

    simulateCallback(echoPin, 1, startTick2);
    simulateCallback(echoPin, 0, endTick2);

    motionDetected = sensor.isMotionDetected(0.2f);
    BOOST_TEST(motionDetected, "Motion should be detected");
}

// BOOST_AUTO_TEST_CASE(UltrasonicTest)
// {
//     Logger::init("test.log");
//     // Create an instance of the Ultrasonic class
//     const int triggerPin = 23;
//     const int echoPin = 24;
//     UltrasonicSensor sensor(triggerPin, echoPin);

//     // Set the expected distance value
//     double expectedDistance = 10.0;

//     // Simulate the ultrasonic measurement
//     double measuredDistance = ultrasonic.measureDistance();

//     // Check if the measured distance matches the expected distance
//     BOOST_CHECK_CLOSE(measuredDistance, expectedDistance, 0.01);
// }