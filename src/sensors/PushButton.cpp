#include "sensors/PushButton.h"
#include <iostream>
#include <unistd.h>

PushButton::PushButton(int pin) : gpioPin(pin)
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
#if defined(__linux__) && defined(__arm__)
    gpioSetMode(gpioPin, PI_INPUT);
    gpioSetPullUpDown(gpioPin, PI_PUD_UP);
#else
    gpioSetMode(gpioPin, PI_INPUT);
    gpioSetPullUpDown(gpioPin, PI_PUD_UP);
#endif
    // Register the interrupt service routine to handle button presses
    attachInterruptHandler();
}

void PushButton::registerButtonPressCallback(ButtonCallback callback)
{
    this->buttonPressCallback = callback;
}

void PushButton::attachInterruptHandler()
{
#if defined(__linux__) && defined(__arm__)
    // Attach the interrupt service routine to the GPIO pin
    gpioSetAlertFunc(gpioPin, &PushButton::buttonPressHandler);
#else
    gpioSetAlertFuncEx(gpioPin, &PushButton::buttonPressHandler, this);
#endif
}

void PushButton::detachInterruptHandler()
{
#if defined(__linux__) && defined(__arm__)
    // Detach the interrupt service routine from the GPIO pin
    gpioSetAlertFunc(gpioPin, nullptr);
#else
    gpioSetAlertFuncEx(gpioPin, nullptr, nullptr);
#endif
}

void PushButton::buttonPressHandler(int gpio, int level, uint32_t tick, void *user)
{
    PushButton *button = static_cast<PushButton *>(user);
    // Check if a valid callback is registered
    if (button->buttonPressCallback)
    {
        button->buttonPressCallback();
    }
    else
    {
        // No callback registered, print the button press event details
        std::cout << "Button Pressed " << gpio << " " << level << " " << tick << std::endl;
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