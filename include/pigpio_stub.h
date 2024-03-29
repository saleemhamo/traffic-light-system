// pigpio_stub.h - Stub for pigpio library functions
// Created by Saleem Hamo on 20/03/2024.

#if !defined(__linux__) || !defined(__arm__)
#pragma once

#include <iostream>

// Define constants to mimic the pigpio library's constants for pin states and modes.
extern const int PI_OUTPUT;
extern const int PI_INPUT;
extern const int PI_HIGH;
extern const int PI_LOW;

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

#endif
