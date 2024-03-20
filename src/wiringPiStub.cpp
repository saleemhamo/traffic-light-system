// Check if we are on a Mac system

#ifndef CROSSGUARD_WIRING_STUB
#define CROSSGUARD_WIRING_STUB

#if !defined(__linux__) || !defined(__arm__)


#include "wiringPiStub.h"
#include <iostream>
#include "utils/Logger.h"

using namespace std;

const int LOW = 0;
const int HIGH = 1;
const int OUTPUT = 2;

void pinMode(int pin, int mode) {
    string message = "pinMode(int pin: " + to_string(pin) + ", int mode: " + to_string(mode) + ") called";
    Logger::logInfo(message);
}

void digitalWrite(int pin, int value) {
    string message = "digitalWrite(int pin: " + to_string(pin) + ", int value: " + to_string(value) + ") called";
    Logger::logInfo(message);
}

int wiringPiSetup() {
    Logger::logInfo("wiringPiSetup() called");
    return 0;
}

#endif
#endif
