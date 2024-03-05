// Check if we are on a Mac system
#if !defined(__linux__) || !defined(__arm__)

#include "wiringPiStub.h"
#include <iostream>

using namespace std;

const int LOW = 0;
const int HIGH = 1;
const int OUTPUT = 2;

void pinMode(int pin, int mode) {
    cout << "pinMode(int pin: " << pin << ", int mode: " << mode << ") called" << endl;
}

void digitalWrite(int pin, int value) {
    cout << "digitalWrite(int pin: " << pin << ", int value: " << value << ") called" << endl;
}

int wiringPiSetup() {
    cout << "wiringPiSetup() called" << endl;
    return 0;
}

#endif
