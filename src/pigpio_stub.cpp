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

void gpioInitialise() {
    Logger::logInfo("gpioInitialise() called");
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
    return PI_LOW; // Default to LOW, adjust as needed for your testing.
}

#endif
