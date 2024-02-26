//
// Created by Saleem Hamo on 20/02/2024.
//
#include "../../../include/main/warning_system/WarningSystem.h"

WarningSystem::WarningSystem(int ledPin, int buzzerPin)
        : warningLED(ledPin), warningBuzzer(buzzerPin), isInitialized(false) {}

void WarningSystem::initialize() {
    // Initialize the LED and buzzer (if necessary)
    // For example, you might set an initial state or perform a self-check
    isInitialized = true;
}

void WarningSystem::activate() {
    if (isInitialized) {
        warningLED.on();
        warningBuzzer.on();  // Activate both LED and buzzer
    }
}

void WarningSystem::deactivate() {
    if (isInitialized) {
        warningLED.off();
        warningBuzzer.off();  // Deactivate both LED and buzzer
    }
}
