#define BOOST_TEST_MODULE TrafficLightTest
#include <boost/test/included/unit_test.hpp>
#include "models/TrafficLight.h"
#include "actuators/LED.h"
#include "utils/Constants.h"
#include "pigpio_stub.h"

#include <thread> // For sleep

struct TrafficLightFixture
{
    TrafficLight *trafficLight;

    TrafficLightFixture()
    {
        gpioInitialise(); // Set up the simulated GPIO environment
        trafficLight = new TrafficLight(Constants::PedestriansTrafficLightRedPin,
                                        Constants::PedestriansTrafficLightGreenPin,
                                        Constants::UnusedPin);
    }

    ~TrafficLightFixture()
    {
        delete trafficLight;
        gpioTerminate(); // Clean up the simulated GPIO environment
    }
};

BOOST_FIXTURE_TEST_SUITE(TrafficLightSuite, TrafficLightFixture)

// Test the constructor and initialization logic.
BOOST_AUTO_TEST_CASE(Initialization)
{
    trafficLight->turnRed();
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightRedPin), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightGreenPin), PI_LOW);
}

// Test turning the light to red.
BOOST_AUTO_TEST_CASE(TurnRed)
{
    trafficLight->turnRed();
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightRedPin), PI_HIGH);
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightGreenPin), PI_LOW);
}

// Test turning the light to green.
BOOST_AUTO_TEST_CASE(TurnGreen)
{
    trafficLight->turnGreen();
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightRedPin), PI_LOW);
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightGreenPin), PI_HIGH);
}

// Test turning the light to yellow.
BOOST_AUTO_TEST_CASE(TurnYellow)
{
    trafficLight->turnYellow();
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightRedPin), PI_LOW);
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightGreenPin), PI_LOW);
}

// Test turning off the light.
BOOST_AUTO_TEST_CASE(TurnOff)
{
    trafficLight->turnOff();
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightRedPin), PI_LOW);
    BOOST_CHECK_EQUAL(gpioRead(Constants::PedestriansTrafficLightGreenPin), PI_LOW);
}

BOOST_AUTO_TEST_SUITE_END()
