#define BOOST_TEST_MODULE LEDTest

#include <boost/test/included/unit_test.hpp>
#include "actuators/LED.h"
#include "pigpio_stub.h" // Make sure this path is correct
#include "utils/Logger.h"

BOOST_AUTO_TEST_CASE(buzzer_on_off_test) {
    Logger::init("test.log");

    LED led(17); // Using pin 17 for this example, adjust as needed

    led.on();
    BOOST_CHECK_EQUAL(gpioRead(17), 1); // Assuming gpioRead returns the state of the pin

    led.off();
    BOOST_CHECK_EQUAL(gpioRead(17), 0); // Check if the pin state is off after calling off()

    Logger::close();
}
