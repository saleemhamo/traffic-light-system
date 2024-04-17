#define BOOST_TEST_MODULE CheckingSystemTest
#include <boost/test/included/unit_test.hpp>

#include "main/CheckingSystem.h"
#include "pigpio_stub.h"
#include "utils/Logger.h"

BOOST_AUTO_TEST_SUITE(CheckingSystemTests)

BOOST_AUTO_TEST_CASE(test_pedestrian_button_press)
{
    // Create a mock CheckingSystem instance
    CheckingSystem system;

    // Enable the pedestrians button
    system.enablePedestriansButton();

    // Set up a mock callback for the pedestrians button press
    bool buttonPressed = false;
    system.registerPedestriansButtonCallback([&]()
                                             { buttonPressed = true; });

    // Simulate a pedestrians button press
    system.onPedestriansButtonPress();

    // Verify that the callback was called
    BOOST_CHECK(buttonPressed);
}

BOOST_AUTO_TEST_CASE(test_pedestrian_motion_detection)
{
    // Create a mock CheckingSystem instance
    CheckingSystem system;

    // Enable pedestrian motion detection
    system.enablePedestriansMotionDetection();

    // Set up a mock callback for pedestrian motion detection
    bool pedestrianMotionDetected = false;
    system.registerPedestriansMotionCallback([&]()
                                             { pedestrianMotionDetected = true; });

    // Simulate pedestrian motion detection using UltrasonicSensor
    const int triggerPin = 23; // Assuming trigger pin for pedestrian sensor
    const int echoPin = 24;    // Assuming echo pin for pedestrian sensor
    UltrasonicSensor sensor(triggerPin, echoPin);
    // Simulate motion under the threshold set to trigger warning system
    const uint32_t startTick2 = 0;
    const uint32_t endTick2 = 291; // Time for 5 centimeters in microseconds (291.375us)

    simulateCallback(echoPin, 1, startTick2);
    simulateCallback(echoPin, 0, endTick2);

    // Simulate motion detection within range
    bool motionDetected = sensor.isMotionDetected(5.0f); // Adjust threshold as needed

    // Verify that the callback was called
    BOOST_CHECK(pedestrianMotionDetected == motionDetected);
}

BOOST_AUTO_TEST_CASE(test_car_motion_detection)
{
    // Create a mock CheckingSystem instance
    CheckingSystem system;

    // Enable car motion detection
    system.enableCarsMotionDetection();

    // Set up a mock callback for car motion detection
    bool carMotionDetected = false;
    system.registerCarsMotionCallback([&]()
                                      { carMotionDetected = true; });

    // Simulate car motion detection using UltrasonicSensor
    const int triggerPin = 25; // Assuming trigger pin for car sensor
    const int echoPin = 26;    // Assuming echo pin for car sensor
    UltrasonicSensor sensor(triggerPin, echoPin);
    // Simulate motion under the threshold set to trigger warning system
    const uint32_t startTick2 = 0;
    const uint32_t endTick2 = 291; // Time for 5 centimeters in microseconds (291.375us)

    simulateCallback(echoPin, 1, startTick2);
    simulateCallback(echoPin, 0, endTick2);
    // Simulate motion detection within range
    bool motionDetected = sensor.isMotionDetected(5.0f); // Adjust threshold as needed

    // Verify that the callback was called
    BOOST_CHECK(carMotionDetected == motionDetected);
}

BOOST_AUTO_TEST_SUITE_END()
