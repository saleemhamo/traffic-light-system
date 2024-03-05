//
// Created by Saleem Hamo on 20/02/2024.
//

#ifdef __APPLE__

#include "wiringPiStub.h"

#else
#include <wiringPi.h>
#endif

#include "actuators/Buzzer.h"

Buzzer::Buzzer(int pin) : pin(pin) {
    wiringPiSetup();  // Setup the wiringPi library
    pinMode(pin, OUTPUT);  // Set the pin mode to output
}

void Buzzer::on() {
    digitalWrite(pin, HIGH);  // Set the pin to high to turn the buzzer on
}

void Buzzer::off() {
    digitalWrite(pin, LOW);  // Set the pin to low to turn the buzzer off
}