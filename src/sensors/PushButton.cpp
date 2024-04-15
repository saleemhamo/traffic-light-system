#include "sensors/PushButton.h"
#include <iostream>
#include <unistd.h>

PushButton::PushButton(int pin) : gpioPin(pin), buttonPressCallback(nullptr)
{
    // Initialize the GPIO pin and register the interrupt service routine
    initialize();
}

PushButton::~PushButton()
{
    // Detach the interrupt service routine to prevent any callbacks after the object is destroyed
    detachInterruptHandler();
}

void PushButton::initialize()
{
    // Initialize the GPIO pin as an input with a pull-up resistor
    gpioInit();
    gpioSetMode(gpioPin, PI_INPUT);
    gpioSetPullUpDown(gpioPin, PI_PUD_UP);

    // Register the interrupt service routine to handle button presses
    attachInterruptHandler();
}

void PushButton::registerButtonPressCallback(ButtonCallback callback)
{
    buttonPressCallback = callback;
}

void PushButton::attachInterruptHandler()
{
    // Attach the interrupt service routine to the GPIO pin
    gpioSetAlertFuncEx(gpioPin, &PushButton::buttonPressHandler, this);
}

void PushButton::detachInterruptHandler()
{
    // Detach the interrupt service routine from the GPIO pin
    gpioSetAlertFuncEx(gpioPin, nullptr, nullptr);
}

void PushButton::buttonPressHandler(int gpio, int level, uint32_t tick, void *user)
{
    // Cast the user data to the PushButton instance
    PushButton *button = static_cast<PushButton *>(user);

    // Invoke the registered callback, if any
    if (button->buttonPressCallback)
    {
        button->buttonPressCallback();
    }
}

void PushButton::gpioInit()
{
    // Initialize the GPIO library
    if (gpioInitialise() < 0)
    {
        std::cerr << "Unable to connect PIGPIO, exiting" << std::endl;
        throw std::runtime_error("Failed to initialize PIGPIO");
    }
}