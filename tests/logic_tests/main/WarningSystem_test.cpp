#define BOOST_TEST_MODULE WarningSystemTest
#include <boost/test/included/unit_test.hpp>

#include "main/WarningSystem.h"
#include "pigpio_stub.h"
#include "utils/Logger.h"

BOOST_AUTO_TEST_SUITE(WarningSystemTests)

BOOST_AUTO_TEST_CASE(WarningSystem_Initialize)
{
    // Create an instance of the WarningSystem
    WarningSystem warningSystem;

    // Test the initialization of the warning system
    BOOST_CHECK(!warningSystem.isInitialized());
    warningSystem.initialize();
    BOOST_CHECK(warningSystem.isInitialized());
}

BOOST_AUTO_TEST_CASE(WarningSystem_Activate)
{
    // Create an instance of the WarningSystem
    WarningSystem warningSystem;

    // Initialize the warning system
    warningSystem.initialize();

    // Test the activation of the warning system
    warningSystem.activate();
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin2), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin3), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::buzzerPin), PI_HIGH);
}

BOOST_AUTO_TEST_CASE(WarningSystem_Deactivate)
{
    // Create an instance of the WarningSystem
    WarningSystem warningSystem;

    // Initialize the warning system
    warningSystem.initialize();

    // Test the deactivation of the warning system
    warningSystem.activate();
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin2), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin3), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::buzzerPin), PI_HIGH);

    warningSystem.deactivate();
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin), PI_LOW);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin2), PI_LOW);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::ledPin3), PI_LOW);
    BOOST_CHECK_EQUAL(gpioRead(WarningSystem::buzzerPin), PI_LOW);
}

BOOST_AUTO_TEST_SUITE_END()
