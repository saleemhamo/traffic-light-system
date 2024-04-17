#define BOOST_TEST_MODULE PushButtonTest
#include <boost/test/included/unit_test.hpp>

#include "sensors/PushButton.h"
#include "pigpio_stub.h"
#include "utils/Logger.h"

BOOST_AUTO_TEST_SUITE(PushButtonTests)

// Flags to track the callback invocations
bool isButtonPressCallbackCalled = false;
bool isButtonReleaseCallbackCalled = false;

// Callback functions for button press and release events
void onButtonPress()
{
    isButtonPressCallbackCalled = true;
}

void onButtonRelease()
{
    isButtonReleaseCallbackCalled = true;
}

BOOST_AUTO_TEST_CASE(ButtonPressAndReleaseHandlerTest)
{
    // Set up the mock environment
    // Logger::setLogLevel(Logger::LogLevel::Debug);
    gpioInitialise();

    // Create a PushButton instance
    PushButton button(17, EITHER_EDGE, 50);

    // Register the callback functions
    button.registerButtonPressCallback(onButtonPress);
    button.registerButtonReleaseCallback(onButtonRelease);

    // Simulate a button press event
    // Logger::logDebug("Simulating button press event...");
    simulateCallback(17, PI_LOW, gpioTick());

    // Assertions for button press event
    BOOST_CHECK_EQUAL(gpioRead(17), PI_LOW);
    BOOST_CHECK(isButtonPressCallbackCalled);
    BOOST_CHECK(!isButtonReleaseCallbackCalled);

    // // Reset the flags
    // isButtonPressCallbackCalled = false;
    // isButtonReleaseCallbackCalled = false;

    // // Simulate a button release event
    // // Logger::logDebug("Simulating button release event...");
    // simulateCallback(17, PI_HIGH, gpioTick());

    // // Assertions for button release event
    // BOOST_CHECK_EQUAL(gpioRead(17), PI_HIGH);
    // BOOST_CHECK(!isButtonPressCallbackCalled);
    // BOOST_CHECK(isButtonReleaseCallbackCalled);

    // Tear down the mock environment
    // Logger::logDebug("Tearing down the mock environment...");
    gpioTerminate();
}

BOOST_AUTO_TEST_SUITE_END()