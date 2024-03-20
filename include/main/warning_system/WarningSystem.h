//
// Created by Saleem Hamo on 20/02/2024.
//
#include "actuators/LED.h"
#include "actuators/Buzzer.h"
#include "main/SystemInterface.h"
#include "utils/Constants.h"

class WarningSystem : public SystemInterface {  // Inherit from ISystem
public:
    WarningSystem();

    static const int ledPin = Constants::WarningSystemLedPin;
    static const int buzzerPin = Constants::WarningSystemBuzzerPin;

    void initialize() override;  // Implement ISystem methods

    void activate() override;    // Implement ISystem methods

    void deactivate() override;  // Implement ISystem methods

private:
    LED warningLED;
    Buzzer warningBuzzer;
    bool isInitialized;  // Example state flag
};

