//
// Created by Saleem Hamo on 20/02/2024.
//

#ifdef __APPLE__

#include "wiringPiStub.h"

#else
#include <wiringPi.h>
#endif

#include "actuators/LED.h"


LED::LED(int pin) : pin(pin) {
    wiringPiSetup();  // Setup the wiringPi library
    pinMode(pin, OUTPUT);  // Set the pin mode to output
}

void LED::on() {
    digitalWrite(pin, HIGH);  // Set the pin to high to turn the LED on
}

void LED::off() {
    digitalWrite(pin, LOW);  // Set the pin to low to turn the LED off
}
