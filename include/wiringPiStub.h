//
// Created by Saleem Hamo on 20/02/2024.
//

#if !defined(__linux__) || !defined(__arm__)
#pragma once

void pinMode(int pin, int mode);

void digitalWrite(int pin, int value);

int digitalRead(int pin);

int wiringPiSetup();

extern const int OUTPUT;
extern const int HIGH;
extern const int LOW;

#endif