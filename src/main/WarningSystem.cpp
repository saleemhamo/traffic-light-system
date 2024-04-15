//
// Created by Miguel Rosa
//

#include "main/WarningSystem.h"

/**
 * @brief Constructor for WarningSystem initializes hardware components.
 *
 * The constructor initializes LED and Buzzer objects using predefined pins
 * from the Constants class. Initially sets the system to an uninitialized state.
 */
WarningSystem::WarningSystem() 
    : warningLED(ledPin),
      warningLED2(ledPin2),
      warningLED3(ledPin3),
      warningBuzzer(buzzerPin),
      isInitialized(false) {}

/**
 * @brief Initializes the warning system by setting all components to the off state.
 *
 * This method prepares the system for operation by ensuring all LEDs and the buzzer
 * start in the off state and sets the system as initialized.
 */
void WarningSystem::initialize() {
    warningLED.off();
    warningLED2.off();
    warningLED3.off();
    warningBuzzer.off();
    isInitialized = true;
}

/**
 * @brief Activates the warning system by turning on all LEDs and the buzzer.
 *
 * If the system has been initialized, this method activates all three LEDs
 * and the buzzer to signal a warning state.
 */
void WarningSystem::activate() {
    if (isInitialized) {
        warningLED.on();
        warningLED2.on();
        warningLED3.on();
        warningBuzzer.on();
    }
}

/**
 * @brief Deactivates the warning system by turning off all LEDs and the buzzer.
 *
 * Ensures that all warning signals are turned off if the system has been initialized,
 * returning the system to a non-alert state.
 */
void WarningSystem::deactivate() {
    if (isInitialized) {
        warningLED.off();
        warningLED2.off();
        warningLED3.off();
        warningBuzzer.off();
    }
}
