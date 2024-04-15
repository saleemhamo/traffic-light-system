#include "sensors/PushButton.h"
#include <iostream>
#include <unistd.h>


/**
 * @brief Constructs a PushButton instance associated with a specific GPIO pin.
 * @param pin GPIO pin number to be used for the push button.
 */
PushButton::PushButton(int pin) : gpioPin(pin) {
}

/**
 * @brief Destructs the PushButton instance.
 *
 * This destructor ensures that the interrupt service routine is detached, preventing any callbacks
 * from being called after the object is destroyed.
 */
PushButton::~PushButton() {
#if defined(__linux__) && defined(__arm__)
    // Reset ISR handling on this pin
    // gpioSetISRFuncEx(gpioPin, FALLING_EDGE, 0, NULL, NULL);
    gpioSetAlertFunc(gpioPin, NULL);
#else

#endif
}

/**
 * @brief Initializes the PushButton hardware interface.
 *
 * This method sets up the GPIO pin as an input with an internal pull-up resistor and
 * registers the interrupt service routine to handle button presses.
 */
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
    // gpioSetISRFuncEx(gpioPin, FALLING_EDGE, 0, buttonPressHandler, this);
    gpioSetAlertFunc(gpioPin, [](int gpio, int level, uint32_t tick) {
        // This lambda function is called in the context of a new thread when the button is pressed
        std::cout << "Button Pressed " << gpio << " " << level << " " << tick << std::endl;
        // Handle the button press event here
    });
#else

#endif


}
/**
 * @brief Registers a callback to be invoked when the button is pressed.
 * @param callback The callback function to execute on a button press.
 */
void PushButton::registerButtonPressCallback(ButtonCallback callback) {
    this->buttonPressCallback = callback;
}

/**
 * @brief Handles button press events by invoking the registered callback.
 *
 * This static method is called automatically when a button press event occurs. It checks if a valid
 * callback is registered and calls it. The method logs the button press event details for debugging.
 * @param gpio GPIO pin number where the event occurred.
 * @param level New level of the GPIO pin (0 or 1).
 * @param tick System tick at the time of the event.
 * @param user User-defined data, which should be a pointer to the PushButton instance.
 */
// void PushButton::buttonPressHandler(int gpio, int level, uint32_t tick, void *user) {
//     // This function is called in the context of a new thread when the button is pressed
//     std::cout << "Button Pressed " << gpio << " " << level << " " << tick << std::endl;
//     PushButton *button = static_cast<PushButton *>(user);
//     if (button->buttonPressCallback) {
//         button->buttonPressCallback(); // Call the user's callback
//     }
// }