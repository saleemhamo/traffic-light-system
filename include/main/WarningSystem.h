//
// Created by Saleem Hamo on 20/02/2024.
//
#include "actuators/LED.h"
#include "actuators/Buzzer.h"
#include "main/interfaces/SystemInterface.h"
#include "utils/Constants.h"

class WarningSystem : public SystemInterface
{ // Inherit from ISystem
public:
    WarningSystem();

    static const int ledPin = Constants::WarningSystemLedPin;
    static const int ledPin2 = Constants::WarningSystemLed2Pin;
    static const int ledPin3 = Constants::WarningSystemLed3Pin;
    static const int buzzerPin = Constants::WarningSystemBuzzerPin;

    bool isInitialized() const { return isInitialized_; }

    void initialize() override; // Implement ISystem methods

    void activate() override; // Implement ISystem methods

    void deactivate() override; // Implement ISystem methods

private:
    LED warningLED;
    LED warningLED2;
    LED warningLED3;
    Buzzer warningBuzzer;
    bool isInitialized_; // Example state flag
};
