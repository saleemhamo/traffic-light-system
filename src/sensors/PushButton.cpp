#include "sensors/PushButton.h"
#include <iostream>

PushButton::PushButton(int pin) : gpioPin(pin) {
}

PushButton::~PushButton() {
#if defined(__linux__) && defined(__arm__)
    // Reset ISR handling on this pin
    gpioSetISRFuncEx(gpioPin, FALLING_EDGE, 0, NULL, NULL);
#else

#endif
}

void PushButton::initialize() {
#if defined(__linux__) && defined(__arm__)
    // Initialize pigpio and set pin modes, only on Raspberry Pi
    if (gpioInitialise() < 0) {
        std::cerr << "Unable to connect PIGPIO, exiting" << std::endl;
        return;
    }
    gpioSetMode(gpioPin, PI_INPUT);
    gpioSetPullUpDown(gpioPin, PI_PUD_UP);
    // Set ISR for falling edge (button press)
    gpioSetISRFuncEx(gpioPin, FALLING_EDGE, 0, buttonPressHandler, this);
    //  More initialization as necessary
#else

#endif


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