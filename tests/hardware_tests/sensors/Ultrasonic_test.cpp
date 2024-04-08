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

    // Call the private(make it public to work around?) sonarReceiveAlertFunction to simulate sensor readings
    // sensor.sonarReceiveAlertFunction(echoPin, 1, startTick, &sensor);
    // sensor.sonarReceiveAlertFunction(echoPin, 0, endTick, &sensor);

    simulateCallback(echoPin, 1, startTick); // Rising edge
    simulateCallback(echoPin, 0, endTick);   // Falling edge

    // Calculate the distance
    float distance = sensor.calculateDistance();
    // printf("Distance: %f\n", distance);
    BOOST_TEST(std::abs(distance - 10.0f) < 0.1f, "Distance calculation is incorrect");

    Logger::close();
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

    // Call the private(make it public to work around?) sonarReceiveAlertFunction to simulate sensor readings
    // sensor.sonarReceiveAlertFunction(echoPin, 1, startTick1, &sensor);
    // sensor.sonarReceiveAlertFunction(echoPin, 0, endTick1, &sensor);

    simulateCallback(echoPin, 1, startTick1);
    simulateCallback(echoPin, 0, endTick1);

    // Check if motion was detected
    bool motionDetected = sensor.isMotionDetected(5.0f);
    // printf("Motion detected false: %d\n", motionDetected);
    BOOST_TEST(!motionDetected, "Motion should not be detected");

    // Simulate motion
    const uint32_t startTick2 = 0;
    const uint32_t endTick2 = 47058; // Time for 0.8 meters in microseconds

    // Call the private(make it public to work around?) sonarReceiveAlertFunction to simulate sensor readings
    // sensor.sonarReceiveAlertFunction(echoPin, 1, startTick2, &sensor);
    // sensor.sonarReceiveAlertFunction(echoPin, 0, endTick2, &sensor);

    simulateCallback(echoPin, 1, startTick2);
    simulateCallback(echoPin, 0, endTick2);

    // Check if motion was detected
    motionDetected = sensor.isMotionDetected(5.0f);
    // printf("Motion detected true: %d\n", motionDetected);
    BOOST_TEST(motionDetected, "Motion should be detected");

    Logger::close();
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