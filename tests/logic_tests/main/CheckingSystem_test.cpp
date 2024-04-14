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

    // Simulate pedestrian motion detection
    system.monitorPedestrian();

    // Verify that the callback was called
    BOOST_CHECK(pedestrianMotionDetected);
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

    // Simulate car motion detection
    system.monitorRoad();

    // Verify that the callback was called
    BOOST_CHECK(carMotionDetected);
}

BOOST_AUTO_TEST_SUITE_END()