//
// Created by Saleem Hamo on 20/02/2024.
//

#ifndef CROSSGUARD_WIRINGPISTUB_H
#define CROSSGUARD_WIRINGPISTUB_H

void pinMode(int pin, int mode);

void digitalWrite(int pin, int value);

int digitalRead(int pin);

void wiringPiSetup();

int OUTPUT;
int HIGH;
int LOW;

#endif //CROSSGUARD_WIRINGPISTUB_H
