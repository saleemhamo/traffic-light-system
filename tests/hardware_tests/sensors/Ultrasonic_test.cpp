#define BOOST_TEST_MODULE UltrasonicSensorTests

#include <boost/test/included/unit_test.hpp>

// Include the header file for the Ultrasonic class
#include "sensors/UltrasonicSensor.h"
#include "pigpio_stub.h"
#include "utils/Logger.h"

BOOST_AUTO_TEST_SUITE(UltrasonicTest)

    // Test the calculateDistance function of the Ultrasonic class
    // This test assumes that the measureDistance function is working correctly
    BOOST_AUTO_TEST_CASE(CalculateDistanceTest)
    {
        // Logger::init("test.log");

        // Create an instance of the Ultrasonic class
        const int triggerPin = 23;
        const int echoPin = 24;
        UltrasonicSensor sensor(triggerPin, echoPin);


        // Simulate a distance of 10 centimeters
        const uint32_t startTick = 0;
        const uint32_t endTick = 583; // Time for 10 centimeters in microseconds (582.75us)

        simulateCallback(echoPin, 1, startTick); // Rising edge
        simulateCallback(echoPin, 0, endTick);   // Falling edge

        // Calculate the distance
        float distance = sensor.calculateDistance();
        //    printf("Distance: %f\n", distance);
        BOOST_TEST(std::abs(distance - 10.0f) < 0.1f, "Distance calculation is incorrect");

        // Logger::close();
    }

    // Test the isMotionDetected function of the Ultrasonic class
    // This test assumes that the calculateDistance function is working correctly
    BOOST_AUTO_TEST_CASE(MotionDetectionTest)
    {
        // Logger::init("test.log");

        // Create an instance of the Ultrasonic class
        const int triggerPin = 23;
        const int echoPin = 24;
        UltrasonicSensor sensor(triggerPin, echoPin);


        // First, simulate an initial distance measurement to set lastDistance
        // This simulates the sensor being at a stable position before the test begins
        const uint32_t initStartTick = 0;
        const uint32_t initEndTick = 500;            // Arbitrary initial distance
        simulateCallback(echoPin, 1, initStartTick); // Rising edge for initial distance
        simulateCallback(echoPin, 0, initEndTick);   // Falling edge for initial distance

        // Calculate the initial distance to set lastDistance inside the sensor
        sensor.calculateDistance();
        sensor.isMotionDetected(5.0f);
        //    printf("Distance: %f\n", sensor.calculateDistance());


        // Simulate no motion triggers warning system
        const uint32_t startTick1 = 0;
        const uint32_t endTick1 = 583; // Time for 10 centimeters in microseconds (582.75us)

        simulateCallback(echoPin, 1, startTick1);
        simulateCallback(echoPin, 0, endTick1);

        // Check if motion was not detected
        bool motionDetected = sensor.isMotionDetected(5.0f);
        //    printf("Motion detected: %s\n", motionDetected ? "TRUE" : "FALSE");
        BOOST_TEST(!motionDetected, "Motion should not be detected");


        // Simulate motion under the threshold set to trigger warning system
        const uint32_t startTick2 = 0;
        const uint32_t endTick2 = 291; // Time for 5 centimeters in microseconds (291.375us)

        simulateCallback(echoPin, 1, startTick2);
        simulateCallback(echoPin, 0, endTick2);

////         Check if motion was detected
//        motionDetected = sensor.isMotionDetected(5.0f);
//        //    printf("Motion detected: %s\n", motionDetected ? "TRUE" : "FALSE");
//        BOOST_TEST(motionDetected, "Motion should not be detected");
//
//        // Simulate motion under the threshold set to trigger warning system
//        const uint32_t startTick3 = 0;
//        const uint32_t endTick3 = 7910; // Time for 5 centimeters in microseconds (291.375us)
//
//        simulateCallback(echoPin, 1, startTick3);
//        simulateCallback(echoPin, 0, endTick3);
//
//        // Check if motion was detected
//        motionDetected = sensor.isMotionDetected(5.0f);
//        //    printf("Motion detected: %s\n", motionDetected ? "TRUE" : "FALSE");
//        BOOST_TEST(motionDetected, "Motion should be detected");


        // Logger::close();
    }

BOOST_AUTO_TEST_SUITE_END()