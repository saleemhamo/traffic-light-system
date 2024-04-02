//
// Created by Saleem Hamo on 20/02/2024.
//
#include "main/WarningSystem.h"

WarningSystem::WarningSystem() :
        warningLED(ledPin),
        warningLED2(ledPin2),
        warningLED3(ledPin3),
        warningBuzzer(buzzerPin),
        isInitialized(false) {}

void WarningSystem::initialize() {
    // Initialize the LED and buzzer (if necessary)
    // For example, you might set an initial state or perform a self-check
    isInitialized = true;
}

void WarningSystem::activate() {
    if (isInitialized) {
        warningLED.on();
        warningLED2.on();
        warningLED3.on();
        warningBuzzer.on();  // Activate both LEDs and buzzer
    }
}

void WarningSystem::deactivate() {
    if (isInitialized) {
        warningLED.off();
        warningLED2.off();
        warningLED3.off();
        warningBuzzer.off();  // Deactivate both LEDs and buzzer
    }
}
