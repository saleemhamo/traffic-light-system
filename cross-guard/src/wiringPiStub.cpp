// Check if we are on a Mac system
#if !defined(__linux__) || !defined(__arm__)

#include "wiringPiStub.h"
#include <iostream>

using namespace std;

const int LOW = 0;
const int HIGH = 1;
const int OUTPUT = 2;

void pinMode(int pin, int mode) {
    cout << "pinMode(int pin, int mode) called" << endl;
    // Stub function: do nothing
}

void digitalWrite(int pin, int value) {
    // Stub function: do nothing
    cout << "digitalWrite(int pin, int value) called" << endl;
}

int wiringPiSetup() {
    // Stub function: return 0 for success
    cout << "wiringPiSetup() called" << endl;
    return 0;
}

#endif
