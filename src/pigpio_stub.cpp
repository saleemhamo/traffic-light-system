// pigpio_stub.cpp - Implementation of the stub functions for pigpio library
// Created by Saleem Hamo on 20/03/2024.

#if !defined(__linux__) || !defined(__arm__)

#include "pigpio_stub.h"
#include "utils/Logger.h" // Make sure to have a Logger class similar to your current setup

using namespace std;

const int PI_OUTPUT = 1;
const int PI_INPUT = 0;
const int PI_HIGH = 1;
const int PI_LOW = 0;

// Adding a variable to simulate the tick counter.
unsigned int simulatedTick = 0;

int gpioInitialise() {
    Logger::logInfo("gpioInitialise() called");
    simulatedTick = 0; // Reset simulated tick on initialization
    return 0;
}

void gpioTerminate() {
    Logger::logInfo("gpioTerminate() called");
}

void gpioSetMode(unsigned pin, unsigned mode) {
    string message = "gpioSetMode(unsigned pin: " + to_string(pin) + ", unsigned mode: " + to_string(mode) + ") called";
    Logger::logInfo(message);
}

void gpioWrite(unsigned pin, unsigned level) {
    string message = "gpioWrite(unsigned pin: " + to_string(pin) + ", unsigned level: " + to_string(level) + ") called";
    Logger::logInfo(message);
}

int gpioRead(unsigned pin) {
    string message = "gpioRead(unsigned pin: " + to_string(pin) + ") called";
    Logger::logInfo(message);
    // Simulating a read might involve conditional logic based on your test setup.
    return PI_LOW; // Default to LOW, adjust as needed for your testing.
}

void gpioDelay(unsigned micros) {
    string message = "gpioDelay(" + to_string(micros) + " microseconds) called";
    Logger::logInfo(message);
    // Simulate delay by incrementing the simulatedTick counter
    simulatedTick += micros;
}

unsigned gpioTick() {
    Logger::logInfo("gpioTick() called");
    // Return the current value of simulatedTick
    // In a real application, this would wrap around at the max value of unsigned int
    return simulatedTick;
}

#endif
