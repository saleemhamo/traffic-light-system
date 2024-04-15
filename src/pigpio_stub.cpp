/**
 * @file pigpio_stub.cpp
 * @brief Implementation of the stub functions for the pigpio library.
 * This stub is used for environments not running Linux on ARM hardware.
 * Created by Saleem Hamo on 20/03/2024.
 */

#if !defined(__linux__) || !defined(__arm__)

#include "pigpio_stub.h"
#include "utils/Logger.h" // Assume Logger setup is correct
#include <map>
#include <functional>
#include <vector>
#include <string>

using namespace std;

const int PI_OUTPUT = 1; ///< Output mode for GPIO pin.
const int PI_INPUT = 0;  ///< Input mode for GPIO pin.
const int PI_HIGH = 1;   ///< High level for GPIO pin state.
const int PI_LOW = 0;    ///< Low level for GPIO pin state.

/// Simulate GPIO pin states with a map
map<unsigned int, unsigned int> pinStates;

/// Map to store the registered callback functions for each GPIO pin
map<unsigned int, vector<function<void(int, int, unsigned, void *)>>> callbacks;

/// Variable to simulate the tick counter.
unsigned int simulatedTick = 0;

/**
 * @brief Initialize the GPIO simulation.
 *
 * Clears the pin states and resets the simulated tick counter.
 *
 * @return Always returns 0 in this stub implementation.
 */
int gpioInitialise()
{
    Logger::logInfo("gpioInitialise() called");
    pinStates.clear(); // Clear pin states upon initialization
    simulatedTick = 0; // Reset simulated tick on initialization
    return 0;
}

/**
 * @brief Terminate the GPIO simulation.
 *
 * Clears the pin states. Optional in this implementation.
 */
void gpioTerminate()
{
    Logger::logInfo("gpioTerminate() called");
    pinStates.clear(); // Optionally clear pin states upon termination
}

/**
 * @brief Set the mode of a GPIO pin.
 *
 * This function logs the mode setting but does not simulate it.
 *
 * @param pin The GPIO pin number.
 * @param mode The mode to set for the pin (input or output).
 */
void gpioSetMode(unsigned pin, unsigned mode)
{
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
void gpioWrite(unsigned pin, unsigned level)
{
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
int gpioRead(unsigned pin)
{
    string message = "gpioRead(pin: " + to_string(pin) + ") called";
    Logger::logInfo(message);
    // Return the stored state if available, otherwise default to LOW
    auto it = pinStates.find(pin);
    if (it != pinStates.end())
    {
        return it->second;
    }
    else
    {
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
void gpioDelay(unsigned micros)
{
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
unsigned gpioTick()
{
    Logger::logInfo("gpioTick() called");
    return simulatedTick;
}

/**
 * @brief Set an ISR function for GPIO pin interrupt events.
 *
 * This function simulates setting an ISR function for GPIO pin interrupt events.
 * It logs the function parameters but does not perform any actual ISR registration.
 *
 * @param gpio The GPIO pin number.
 * @param edge The edge (RISING_EDGE, FALLING_EDGE, or EITHER_EDGE) to trigger the interrupt.
 * @param timeout Interrupt timeout in milliseconds (<= 0 to cancel).
 * @param f The ISR function to set.
 * @param userdata Pointer to arbitrary user data.
 * @return Returns 0 if OK, otherwise returns PI_BAD_GPIO, PI_BAD_EDGE, or PI_BAD_ISR_INIT.
 */
int gpioSetISRFuncEx(unsigned pin, int edge, int timeout, void (*func)(int, int, unsigned, void *), void *user)
{
    string message = "gpioSetISRFuncEx(pin: " + to_string(pin) + ", edge: " + to_string(edge) + ", timeout: " + to_string(timeout) +
                     ", function: " + to_string(reinterpret_cast<uintptr_t>(func)) + ", userdata: " + to_string(reinterpret_cast<uintptr_t>(user)) + ") called";
    Logger::logInfo(message);
    // Store the callback function and user data for the specified pin
    callbacks[pin].emplace_back([func, user](int gpio, int level, unsigned tick, void *userData)
                                { func(gpio, level, tick, user); });

    // Return success for the stub implementation
    return 0;
}

// // This function is supposed to mimic setting the pull-up/pull-down resistors for a GPIO pin.
// void gpioSetPullUpDown(unsigned pin, unsigned pud)
// {
//     string message = "gpioSetPullUpDown(pin: " + to_string(pin) + ", pud: " + to_string(pud) + ") called";
//     Logger::logInfo(message);
//     callbacks[pin].emplace_back([pin, pud](int gpio, int level, unsigned tick, void *userData)
//                                 { gpioWrite(pin, pud); });
// }

/**
 * @brief Set a callback function for GPIO pin alert events.
 *
 * This function stores the callback function and user data for the specified GPIO pin.
 *
 * @param pin The GPIO pin number.
 * @param func The callback function to set.
 * @param user A user-defined pointer passed to the callback function.
 * @return Always returns 0 in this stub implementation.
 */
int gpioSetAlertFuncEx(unsigned pin, void (*func)(int, int, unsigned, void *), void *user)
{
    string message = "gpioSetAlertFuncEx(pin: " + to_string(pin) + ") called";
    Logger::logInfo(message);

    // Store the callback function and user data for the specified pin
    callbacks[pin].emplace_back([func, user](int gpio, int level, unsigned tick, void *userData)
                                { func(gpio, level, tick, user); });

    return 0; // Success
}

/**
 * @brief Simulate a callback function call for a specific GPIO pin.
 *
 * This function calls all the registered callback functions for the specified GPIO pin
 * with the provided level and tick values.
 *
 * @param pin The GPIO pin number for which to simulate the callback.
 * @param level The level value to pass to the callback function.
 * @param tick The tick value to pass to the callback function.
 */
void simulateCallback(unsigned pin, int level, unsigned tick)
{
    string message = "simulateCallback(pin: " + to_string(pin) + ", level: " + to_string(level) + ", tick: " + to_string(tick) + ") called";
    Logger::logInfo(message);

    // Call all registered callback functions for the specified pin
    auto it = callbacks.find(pin);
    if (it != callbacks.end())
    {
        for (const auto &callback : it->second)
        {
            callback(pin, level, tick, nullptr);
        }
    }
}

#endif
