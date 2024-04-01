// Check if we are on a typical Raspberry Pi OS and ARM architecture
#if defined(__linux__) && defined(__arm__)
#include <pigpio.h>
#else

#include "pigpio_stub.h"

#endif

#include "actuators/Buzzer.h"

Buzzer::Buzzer(int pin) : pin(pin)
{
    gpioInitialise();            // Initialize the pigpio library
    gpioSetMode(pin, PI_OUTPUT); // Set the pin mode to output
}

void Buzzer::on()
{
    gpioWrite(pin, 1); // Set the pin to high to turn the buzzer on
}

void Buzzer::off()
{
    gpioWrite(pin, 0); // Set the pin to low to turn the buzzer off
}