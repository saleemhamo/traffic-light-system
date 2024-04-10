#define BOOST_TEST_MODULE UltrasonicSensorTests
#include <boost/test/included/unit_test.hpp>

// Include the header file for the Ultrasonic class
#include "sensors/UltrasonicSensor.h"
#include "pigpio_stub.h"
#include "utils/Logger.h"

BOOST_AUTO_TEST_SUITE(UltrasonicTest)

BOOST_AUTO_TEST_CASE(CalculateDistanceTest)
{
    // Logger::init("test.log");
    const int triggerPin = 23;
    const int echoPin = 24;
    UltrasonicSensor sensor(triggerPin, echoPin);

    // Simulate three distance measurements
    const uint32_t startTick1 = 0, endTick1 = 583;  // 10 cm
    const uint32_t startTick2 = 0, endTick2 = 291;  // 5 cm
    const uint32_t startTick3 = 0, endTick3 = 1166; // 20 cm

    simulateCallback(echoPin, 1, startTick1);
    simulateCallback(echoPin, 0, endTick1);
    float distance1 = sensor.calculateDistance();
    printf("Distance: %f\n", distance1);
    simulateCallback(echoPin, 1, startTick2);
    simulateCallback(echoPin, 0, endTick2);
    float distance2 = sensor.calculateDistance();
    printf("Distance: %f\n", distance2);
    simulateCallback(echoPin, 1, startTick3);
    simulateCallback(echoPin, 0, endTick3);
    float distance3 = sensor.calculateDistance();
    printf("Distance: %f\n", distance3);

    // Check if the distance calculation is within the expected range

    // float distance = sensor.calculateDistance();
    // printf("Distance: %f\n", distance);
    // // BOOST_TEST(std::abs(distance - 10.0f) < 0.1f, "Distance calculation is incorrect");
    // BOOST_TEST(distance >= 5.0f, "Distance calculation is lower than expected");
    // BOOST_TEST(distance <= 15.0f, "Distance calculation is higher than expected");
    BOOST_TEST(std::abs(distance1 - 10.0f) < 0.1f, "First distance calculation is incorrect");
    BOOST_TEST(std::abs(distance2 - 5.0f) < 0.1f, "Second distance calculation is incorrect");
    BOOST_TEST(std::abs(distance3 - 20.0f) < 0.1f, "Third distance calculation is incorrect");
    // Logger::close();
}

BOOST_AUTO_TEST_CASE(MotionDetectionTest)
{
    // Logger::init("test.log");
    const int triggerPin = 23;
    const int echoPin = 24;
    UltrasonicSensor sensor(triggerPin, echoPin);

    // Simulate an initial distance measurement
    const uint32_t initStartTick = 0, initEndTick = 500;
    simulateCallback(echoPin, 1, initStartTick);
    simulateCallback(echoPin, 0, initEndTick);
    sensor.calculateDistance();
    sensor.isMotionDetected(5.0f);

    // Simulate no motion
    const uint32_t startTick1 = 0, endTick1 = 583; // 10 cm
    simulateCallback(echoPin, 1, startTick1);
    simulateCallback(echoPin, 0, endTick1);
    bool motionDetected = sensor.isMotionDetected(5.0f);
    BOOST_TEST(!motionDetected, "Motion should not be detected");

    // Simulate motion under the threshold
    const uint32_t startTick2 = 0, endTick2 = 291; // 5 cm
    simulateCallback(echoPin, 1, startTick2);
    simulateCallback(echoPin, 0, endTick2);
    motionDetected = sensor.isMotionDetected(5.0f);
    BOOST_TEST(motionDetected, "Motion should be detected");
    // Logger::close();
}

BOOST_AUTO_TEST_SUITE_END()