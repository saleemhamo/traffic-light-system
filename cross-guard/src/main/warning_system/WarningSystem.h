//
// Created by Saleem Hamo on 20/02/2024.
//
#include "../../actuators/LED.h"
#include "../../actuators/Buzzer.h"
#include "../SystemInterface.h"

class WarningSystem : public SystemInterface {  // Inherit from ISystem
public:
    WarningSystem(int ledPin, int buzzerPin);  // Constructor
    void initialize() override;  // Implement ISystem methods
    void activate() override;    // Implement ISystem methods
    void deactivate() override;  // Implement ISystem methods

private:
    LED warningLED;
    Buzzer warningBuzzer;
    bool isInitialized;  // Example state flag
};

