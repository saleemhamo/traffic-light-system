// pigpio_stub.h - Stub for pigpio library functions
// Created by Saleem Hamo on 20/03/2024.

#if !defined(__linux__) || !defined(__arm__)
#pragma once

#include <iostream>
#include <functional>

// Define constants to mimic the pigpio library's constants for pin states and modes.
extern const int PI_OUTPUT;
extern const int PI_INPUT;
extern const int PI_HIGH;
extern const int PI_LOW;

// Constants for pull-up/downs and interrupt edges
#define PI_PUD_UP 0
#define PI_PUD_DOWN 0
#define PI_PUD_OFF 0

// Constants for interrupt edges (RISING_EDGE, FALLING_EDGE, EITHER_EDGE)
#define RISING_EDGE 0
#define FALLING_EDGE 1
#define EITHER_EDGE 2

// GPIO pin number
using GpioPin = int;

// Function declarations to mimic those in the pigpio library.
int gpioInitialise();

void gpioTerminate();

void gpioSetMode(unsigned pin, unsigned mode);

void gpioWrite(unsigned pin, unsigned level);

int gpioRead(unsigned pin);

// Simulate a delay for a specified number of microseconds.
void gpioDelay(unsigned micros);

// Simulate a microsecond tick counter.
unsigned gpioTick();

// Simulate setting a GPIO alert function with an additional user parameter.
int gpioSetAlertFuncEx(unsigned pin, void (*func)(int, int, unsigned, void *), void *user);

// Function to mimic setting an interrupt service routine (ISR) for a GPIO pin, with an additional user parameter.
bool gpioSetISRFuncEx(GpioPin pin, int edge, int debounceMs, void (*func)(int, int, uint32_t, void *), void *userData);

// Add the function declaration for gpioSetPullUpDown
// This function is supposed to mimic setting the pull-up/pull-down resistors for a GPIO pin.
void gpioSetPullUpDown(unsigned pin, unsigned pud);

// Simulate a callback function for a GPIO pin.
void simulateCallback(unsigned pin, int level, unsigned tick);

#endif
