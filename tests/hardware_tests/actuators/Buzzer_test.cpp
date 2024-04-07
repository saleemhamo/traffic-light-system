#define BOOST_TEST_MODULE BuzzerTest

#include <boost/test/included/unit_test.hpp>
#include "actuators/Buzzer.h"
#include "pigpio_stub.h" // Make sure this path is correct
#include "utils/Logger.h"

BOOST_AUTO_TEST_CASE(buzzer_on_off_test) {
    Logger::init("test.log");

    Buzzer buzzer(17); // Using pin 17 for this example, adjust as needed

    buzzer.on();
    BOOST_CHECK_EQUAL(gpioRead(17), 1); // Assuming gpioRead returns the state of the pin

    buzzer.off();
    BOOST_CHECK_EQUAL(gpioRead(17), 0); // Check if the pin state is off after calling off()

    Logger::close();
}
