//
// Created and  documented by Miguel Rosa
//
#ifndef WARNING_SYSTEM_H
#define WARNING_SYSTEM_H

#include "actuators/LED.h"
#include "actuators/Buzzer.h"
#include "main/interfaces/SystemInterface.h"
#include "utils/Constants.h"

/**
 * @class WarningSystem
 * @brief Manages a warning system with three LEDs and a buzzer.
 *
 * Inherits from SystemInterface, requiring implementation of initialization,
 * activation, and deactivation methods. Utilizes predefined pin numbers
 * from the Constants class for LED and buzzer components.
 */
class WarningSystem : public SystemInterface {
public:
    /**
     * @brief Constructs a new Warning System instance.
     *
     * Initializes LEDs and buzzer with predefined pins from Constants. The
     * system is not initialized by default.
     */
    WarningSystem();

    /**
     * @brief Initializes the warning system components.
     *
     * Sets all LEDs and the buzzer to their off state and marks the system as initialized.
     */
    void initialize() override;

    /**
     * @brief Getter of the isInitialized_ variable
     *
     * Return the value of isInitialized_.
     */
    bool isInitialized() const { return isInitialized_; }

    /**
     * @brief Activates the warning system.
     *
     * Turns on all LEDs and the buzzer if the system has been initialized.
     */
    void activate() override;

    /**
     * @brief Deactivates the warning system.
     *
     * Turns off all LEDs and the buzzer if the system has been initialized.
     */
    void deactivate() override;

    static const int ledPin = Constants::WarningSystemLedPin;     ///< Pin number for the first LED.
    static const int ledPin2 = Constants::WarningSystemLed2Pin;   ///< Pin number for the second LED.
    static const int ledPin3 = Constants::WarningSystemLed3Pin;   ///< Pin number for the third LED.
    static const int buzzerPin = Constants::WarningSystemBuzzerPin; ///< Pin number for the buzzer.

private:
    LED warningLED;       ///< First LED component.
    LED warningLED2;      ///< Second LED component.
    LED warningLED3;      ///< Third LED component.
    Buzzer warningBuzzer; ///< Buzzer component.
    bool isInitialized_;   ///< Flag indicating whether the system has been initialized.
};

#endif // WARNING_SYSTEM_H
