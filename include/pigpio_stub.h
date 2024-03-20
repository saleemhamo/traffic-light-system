// pigpio_stub.h - Stub for pigpio library functions
// Created by Saleem Hamo on 20/03/2024.

#if !defined(__linux__) || !defined(__arm__)
#pragma once

#include <iostream>

extern const int PI_OUTPUT;
extern const int PI_INPUT;
extern const int PI_HIGH;
extern const int PI_LOW;

void gpioInitialise();

void gpioTerminate();

void gpioSetMode(unsigned pin, unsigned mode);

void gpioWrite(unsigned pin, unsigned level);

int gpioRead(unsigned pin);

#endif
