#define BOOST_TEST_MODULE PushButtonTest
#include <boost/test/included/unit_test.hpp>
#include "sensors/PushButton.h"
#include "pigpio_stub.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(PushButtonTests)

BOOST_AUTO_TEST_CASE(ButtonPressCallback)
{
    // Set up the test
    int testPin = 17;
    bool callbackCalled = false;
    PushButton button(testPin);
    button.registerButtonPressCallback([&]()
                                       { callbackCalled = true; });
    button.initialize();

    // Simulate a button press
    simulateCallback(testPin, PI_LOW, gpioTick());

    // Verify the callback is called
    BOOST_CHECK(callbackCalled);
}

BOOST_AUTO_TEST_CASE(PullUpResistorConfiguration)
{
    // Set up the test
    int testPin = 18;
    PushButton button(testPin);
    button.initialize();

    // Verify the pin mode is set to input with pull-up
    BOOST_CHECK_EQUAL(gpioRead(testPin), PI_HIGH);
}

BOOST_AUTO_TEST_SUITE_END()