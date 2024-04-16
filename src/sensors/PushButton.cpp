#include "sensors/PushButton.h"
#include <iostream>
#include <unistd.h>

PushButton::PushButton(int pin, int edge, int debounceMs)
    : gpioPin(pin), edgeMode(edge), debounceMs(debounceMs), buttonPressCallback(nullptr), buttonReleaseCallback(nullptr)
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

    // Register the interrupt service routine to handle button presses and releases
    attachInterruptHandler();
}

void PushButton::registerButtonPressCallback(ButtonCallback callback)
{
    buttonPressCallback = callback;
}

void PushButton::registerButtonReleaseCallback(ButtonCallback callback)
{
    buttonReleaseCallback = callback;
}

void PushButton::attachInterruptHandler()
{
    // Attach the interrupt service routine to the GPIO pin
    gpioSetISRFuncEx(gpioPin, edgeMode, debounceMs, &PushButton::buttonEventHandler, this);
}

void PushButton::detachInterruptHandler()
{
    // Detach the interrupt service routine from the GPIO pin
    gpioSetISRFuncEx(gpioPin, edgeMode, debounceMs, nullptr, nullptr);
}

void PushButton::buttonEventHandler(int gpio, int level, uint32_t tick, void *user)
{
    // Cast the user data to the PushButton instance
    PushButton *button = static_cast<PushButton *>(user);

    // Determine if it's a button press or release event
    if (level == PI_LOW)
    {
        // Button press event
        if (button->buttonPressCallback)
        {
            button->buttonPressCallback();
        }
    }
    else
    {
        // Button release event
        if (button->buttonReleaseCallback)
        {
            button->buttonReleaseCallback();
        }
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