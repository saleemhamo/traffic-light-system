/**
 * @file LED.cpp
 * @brief Controls an LED connected to a GPIO pin on a Raspberry Pi.
 *
 * This file provides the implementation of the LED class, which includes methods
 * to turn an LED on and off. The class abstracts the hardware details by using
 * the pigpio library (or a stub for environments not supported by pigpio) to
 * manage GPIO pin states.
 *
 * Conditional compilation checks ensure the correct inclusion of the pigpio
 * library for Raspberry Pi OS and ARM architecture, or the inclusion of a stub
 * for other environments.
 */

// Conditional inclusion based on the operating system and architecture
#if defined(__linux__) && defined(__arm__)
#include <pigpio.h>
#else
#include "pigpio_stub.h"
#endif

#include "actuators/LED.h"

/**
 * @brief Constructor for the LED class.
 *
 * This constructor initializes the GPIO pin used by the LED and sets it to
 * output mode, preparing the LED for use.
 *
 * @param pin The GPIO pin number connected to the LED.
 */
LED::LED(int pin) : pin(pin) {
    gpioInitialise();            // Initialize the pigpio library
    gpioSetMode(pin, PI_OUTPUT); // Set the pin mode to output
}

/**
 * @brief Turn the LED on.
 *
 * This method sets the GPIO pin to high, which turns the LED on.
 */
void LED::on() {
    gpioWrite(pin, PI_HIGH); // Set the pin to high to turn the LED on
}

/**
 * @brief Turn the LED off.
 *
 * This method sets the GPIO pin to low, turning the LED off.
 */
void LED::off() {
    gpioWrite(pin, PI_LOW); // Set the pin to low to turn the LED off
}
