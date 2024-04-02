// pigpio_stub.cpp - Implementation of the stub functions for pigpio library
// Created by Saleem Hamo on 20/03/2024.

#if !defined(__linux__) || !defined(__arm__)

#include "pigpio_stub.h"
#include "utils/Logger.h"  // Assume Logger setup is correct
#include <map>
#include <string>

using namespace std;

const int PI_OUTPUT = 1;
const int PI_INPUT = 0;
const int PI_HIGH = 1;
const int PI_LOW = 0;

// Simulate GPIO pin states with a map
map<unsigned int, unsigned int> pinStates;

// Adding a variable to simulate the tick counter.
unsigned int simulatedTick = 0;

int gpioInitialise() {
    Logger::logInfo("gpioInitialise() called");
    pinStates.clear();  // Clear pin states upon initialization
    simulatedTick = 0;  // Reset simulated tick on initialization
    return 0;
}

void gpioTerminate() {
    Logger::logInfo("gpioTerminate() called");
    pinStates.clear();  // Optionally clear pin states upon termination
}

void gpioSetMode(unsigned pin, unsigned mode) {
    string message = "gpioSetMode(pin: " + to_string(pin) + ", mode: " + to_string(mode) + ") called";
    Logger::logInfo(message);
    // Mode setting not simulated in pinStates map, as it's primarily for direction
}

void gpioWrite(unsigned pin, unsigned level) {
    string message = "gpioWrite(pin: " + to_string(pin) + ", level: " + to_string(level) + ") called";
    Logger::logInfo(message);
    // Save the level of the pin in the map
    pinStates[pin] = level;
}

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

void gpioDelay(unsigned micros) {
    string message = "gpioDelay(" + to_string(micros) + " microseconds) called";
    Logger::logInfo(message);
    // Simulate delay by incrementing the simulatedTick counter
    simulatedTick += micros;
}

unsigned gpioTick() {
    Logger::logInfo("gpioTick() called");
    return simulatedTick;
}

int gpioSetAlertFuncEx(unsigned pin, void (*func)(int, int, unsigned, void *), void *user) {
    string message = "gpioSetAlertFuncEx(pin: " + to_string(pin) + ") called";
    Logger::logInfo(message);
    // Callback mechanism simulation is beyond the scope of this stub.

    return 0; // Success
}

#endif
