/**
 * @file Buzzer.cpp
 * @brief Controls a buzzer connected to a GPIO pin on a Raspberry Pi.
 *
 * This file contains the implementation of the Buzzer class, which provides methods
 * to turn a buzzer on and off. The class abstracts the details of using the pigpio
 * library (or its stub for non-Raspberry Pi or non-ARM Linux environments) to
 * manage GPIO pins.
 *
 * If running on a typical Raspberry Pi OS and ARM architecture, the pigpio library
 * is used. Otherwise, a stub implementation is utilized.
 */

// Conditional inclusion of pigpio library or stub based on the platform
#if defined(__linux__) && defined(__arm__)
#include <pigpio.h>
#else

#include "pigpio_stub.h"

#endif

#include "actuators/Buzzer.h"

/**
 * @brief Constructor for the Buzzer class.
 *
 * Initializes the GPIO pin used by the buzzer and sets it to output mode.
 *
 * @param pin GPIO pin number connected to the buzzer.
 */
Buzzer::Buzzer(int pin) : pin(pin) {
    gpioInitialise();            // Initialize the pigpio library
    gpioSetMode(pin, PI_OUTPUT); // Set the pin mode to output
}

/**
 * @brief Turn the buzzer on.
 *
 * Sets the GPIO pin to high, activating the buzzer.
 */
void Buzzer::on() {
    gpioWrite(pin, PI_HIGH); // Set the pin to high to turn the buzzer on
}

/**
 * @brief Turn the buzzer off.
 *
 * Sets the GPIO pin to low, deactivating the buzzer.
 */
void Buzzer::off() {
    gpioWrite(pin, PI_LOW); // Set the pin to low to turn the buzzer off
}
