/**
 * @file pigpio_stub.cpp
 * @brief Implementation of the stub functions for the pigpio library.
 * This stub is used for environments not running Linux on ARM hardware.
 * Created by Saleem Hamo on 20/03/2024.
 */

#if !defined(__linux__) || !defined(__arm__)

#include "pigpio_stub.h"
#include "utils/Logger.h"  // Assume Logger setup is correct
#include <map>
#include <string>

using namespace std;

const int PI_OUTPUT = 1; ///< Output mode for GPIO pin.
const int PI_INPUT = 0;  ///< Input mode for GPIO pin.
const int PI_HIGH = 1;   ///< High level for GPIO pin state.
const int PI_LOW = 0;    ///< Low level for GPIO pin state.

/// Simulate GPIO pin states with a map
map<unsigned int, unsigned int> pinStates;

/// Variable to simulate the tick counter.
unsigned int simulatedTick = 0;

/**
 * @brief Initialize the GPIO simulation.
 *
 * Clears the pin states and resets the simulated tick counter.
 *
 * @return Always returns 0 in this stub implementation.
 */
int gpioInitialise() {
    Logger::logInfo("gpioInitialise() called");
    pinStates.clear();  // Clear pin states upon initialization
    simulatedTick = 0;  // Reset simulated tick on initialization
    return 0;
}

/**
 * @brief Terminate the GPIO simulation.
 *
 * Clears the pin states. Optional in this implementation.
 */
void gpioTerminate() {
    Logger::logInfo("gpioTerminate() called");
    pinStates.clear();  // Optionally clear pin states upon termination
}

/**
 * @brief Set the mode of a GPIO pin.
 *
 * This function logs the mode setting but does not simulate it.
 *
 * @param pin The GPIO pin number.
 * @param mode The mode to set for the pin (input or output).
 */
void gpioSetMode(unsigned pin, unsigned mode) {
    string message = "gpioSetMode(pin: " + to_string(pin) + ", mode: " + to_string(mode) + ") called";
    Logger::logInfo(message);
    // Mode setting not simulated in pinStates map, as it's primarily for direction
}

/**
 * @brief Write a level to a GPIO pin.
 *
 * Saves the level of the pin in a simulation map.
 *
 * @param pin The GPIO pin number.
 * @param level The level to write to the pin (high or low).
 */
void gpioWrite(unsigned pin, unsigned level) {
    string message = "gpioWrite(pin: " + to_string(pin) + ", level: " + to_string(level) + ") called";
    Logger::logInfo(message);
    // Save the level of the pin in the map
    pinStates[pin] = level;
}

/**
 * @brief Read the level of a GPIO pin.
 *
 * Returns the stored state if available, otherwise defaults to LOW.
 *
 * @param pin The GPIO pin number to read.
 * @return The level of the pin (high or low).
 */
int gpioRead(unsigned pin) {
    string message = "gpioRead(pin: " + to_string(pin) + ") called";
    Logger::logInfo(message);
    // Return the stored state if available, otherwise default to LOW
    auto it = pinStates.find(pin);
    if (it != pinStates.end()) {
        return it->second;
    } else {
        return PI_LOW; // Default to LOW if not set
    }
}

/**
 * @brief Simulate a delay in microseconds.
 *
 * Increments the simulatedTick counter by the delay amount.
 *
 * @param micros The number of microseconds to delay.
 */
void gpioDelay(unsigned micros) {
    string message = "gpioDelay(" + to_string(micros) + " microseconds) called";
    Logger::logInfo(message);
    // Simulate delay by incrementing the simulatedTick counter
    simulatedTick += micros;
}

/**
 * @brief Get the current value of the simulated tick counter.
 *
 * @return The current simulated tick value.
 */
unsigned gpioTick() {
    Logger::logInfo("gpioTick() called");
    return simulatedTick;
}

/**
 * @brief Set a callback function for GPIO pin alert events.
 *
 * This function logs the setting of a callback but does not simulate the callback mechanism.
 *
 * @param pin The GPIO pin number.
 * @param func The callback function to set.
 * @param user A user-defined pointer passed to the callback function.
 * @return Always returns 0 in this stub implementation.
 */
int gpioSetAlertFuncEx(unsigned pin, void (*func)(int, int, unsigned, void *), void *user) {
    string message = "gpioSetAlertFuncEx(pin: " + to_string(pin) + ") called";
    Logger::logInfo(message);
    // Callback mechanism simulation is beyond the scope of this stub.

    return 0; // Success
}

#endif
