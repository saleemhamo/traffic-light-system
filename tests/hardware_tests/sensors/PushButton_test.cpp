#define BOOST_TEST_MODULE PushButtonTest
#include <boost/test/included/unit_test.hpp>

#include "sensors/PushButton.h"
#include "pigpio_stub.h"
#include "utils/Logger.h"

BOOST_AUTO_TEST_SUITE(PushButtonTests)

// Mock callback function for button press events
bool isButtonPressCallbackCalled = false;
void mockButtonPressCallback()
{
    isButtonPressCallbackCalled = true;
}

BOOST_AUTO_TEST_CASE(ButtonPressHandlerTest)
{
    // Set up the mock environment
    gpioInitialise();

    // Create a PushButton instance
    PushButton button(17);

    // Register the mock callback function
    button.registerButtonPressCallback(mockButtonPressCallback);

    // Simulate a button press event
    simulateCallback(17, PI_LOW, gpioTick());

    // Assertions
    BOOST_CHECK_EQUAL(gpioRead(17), PI_LOW);
    BOOST_CHECK(isButtonPressCallbackCalled);

    // Tear down the mock environment
    gpioTerminate();
}

BOOST_AUTO_TEST_CASE(ButtonReleaseHandlerTest)
{
    // Set up the mock environment
    gpioInitialise();

    // Create a PushButton instance
    PushButton button(17);

    // Register the mock callback function
    button.registerButtonPressCallback(mockButtonPressCallback);

    // Simulate a button release event
    simulateCallback(17, PI_HIGH, gpioTick());

    // Assertions
    BOOST_CHECK_EQUAL(gpioRead(17), PI_HIGH);
    BOOST_CHECK(!isButtonPressCallbackCalled); // Callback should not be called on button release

    // Tear down the mock environment
    gpioTerminate();
}

BOOST_AUTO_TEST_SUITE_END()