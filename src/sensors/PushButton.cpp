#include "sensors/PushButton.h"

PushButton::PushButton(int pin) : gpioPin(pin) {
}

PushButton::~PushButton() {
#ifdef RASPBERRY_PI
    // Reset ISR handling on this pin
    gpioSetISRFuncEx(gpioPin, FALLING_EDGE, 0, NULL, NULL);
#endif
    // Optional: gpioTerminate(); // Consider if you want to terminate pigpio on destruction. Beware if using multiple GPIO devices.
}

void PushButton::initialize() {
    // Initialize pigpio and set pin modes, only on Raspberry Pi
#ifdef RASPBERRY_PI
    gpioInitialise();
    gpioSetPullUpDown(gpioPin, PI_PUD_UP);
    // Set ISR for falling edge (button press)
    gpioSetISRFuncEx(gpioPin, FALLING_EDGE, 0, buttonPressHandler, this);

#endif
    // More initialization as necessary
}

void PushButton::registerMotionCallback(ButtonCallback callback) {
    this->buttonPressCallback = callback;
}

void PushButton::buttonPressHandler(int gpio, int level, uint32_t tick, void *user) {
    // This function is called in the context of a new thread when the button is pressed
    PushButton *button = static_cast<PushButton *>(user);
    if (button->buttonPressCallback) {
        button->buttonPressCallback(); // Call the user's callback
    }
}