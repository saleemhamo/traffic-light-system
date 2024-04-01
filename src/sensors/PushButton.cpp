#include "sensors/PushButton.h"
#include <iostream>

PushButton::PushButton(int pin) : gpioPin(pin) {
}

PushButton::~PushButton() {
//#ifdef RASPBERRY_PI
    // Reset ISR handling on this pin
    gpioSetAlertFunc(gpioPin, NULL);
//#endif
    // Optional: gpioTerminate(); // Consider if you want to terminate pigpio on destruction. Beware if using multiple GPIO devices.
}

void PushButton::initialize() {
    // Initialize pigpio and set pin modes, only on Raspberry Pi
//#ifdef RASPBERRY_PI
    if (gpioInitialise() < 0)
    {
        std::cerr << "Unable to connect PIGPIO, exiting" << std::endl;
        return;
    }
    gpioSetMode(gpioPin, PI_INPUT);
    gpioSetPullUpDown(gpioPin, PI_PUD_UP);
    // Set ISR for falling edge (button press)
    gpioSetAlertFunc(gpioPin, buttonPressHandler);
//#endif
    // More initialization as necessary
}

void PushButton::registerButtonPressCallback(ButtonCallback callback) {
    this->buttonPressCallback = callback;
}

void PushButton::buttonPressHandler(int gpio, int level, uint32_t tick, void *user) {
    // This function is called in the context of a new thread when the button is pressed
    std::cout << "Button Pressed " << gpio << " " << level << " " << tick << std::endl;
    PushButton *button = static_cast<PushButton *>(user);
    if (button->buttonPressCallback) {
        button->buttonPressCallback(); // Call the user's callback
    }
}