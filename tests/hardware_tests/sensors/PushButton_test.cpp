#define BOOST_TEST_MODULE PushButtonTest

// Boost headers
#include <boost/test/included/unit_test.hpp>
#include "sensors/PushButton.h"
#include "pigpio_stub.h"

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

BOOST_AUTO_TEST_SUITE_END()