#ifndef CROSSGUARD_PUSHBUTTON_H
#define CROSSGUARD_PUSHBUTTON_H

#include <cstdint>

#if defined(__linux__) && defined(__arm__)
#include <pigpio.h>
#else

#include "pigpio_stub.h"

#endif

#include <functional>

/**
 * @class PushButton
 * @brief Manages the interaction with a physical push button connected to a GPIO pin.
 *
 * This class encapsulates the setup and usage of a GPIO pin as a push button input on a Raspberry Pi,
 * including debouncing and handling button press events via callbacks. The class is designed to be used
 * on systems where the PiGPIO library is available but also includes a stub for non-Raspberry Pi systems.
 */

class PushButton {
public:
    using ButtonCallback = std::function<void()>; ///< Callback type for button press events.

    /**
     * @brief Constructor that initializes a PushButton with a specific GPIO pin.
     * @param pin The GPIO pin number associated with the button.
     */
    PushButton(int pin);
    
     /**
     * @brief Destructor that cleans up ISR handling if necessary.
     */
    ~PushButton();
    
    /**
     * @brief Initializes the button's GPIO pin and sets up the interrupt service routine.
     *
     * This method sets the GPIO pin as an input and attaches an interrupt handler
     * that is triggered on the falling edge (button press).
     */
    void initialize();
    
    /**
     * @brief Registers a callback function to be called when the button is pressed.
     * @param callback The function to call when the button is pressed.
     */
    void registerButtonPressCallback(ButtonCallback callback);
    void attachInterruptHandler();
    void detachInterruptHandler();
    void gpioInit();
    /**
     * @brief Static method used as the interrupt service routine for button presses.
     * @param gpio GPIO pin number where the interrupt occurred.
     * @param level New level of the GPIO pin after the interrupt.
     * @param tick System tick counter value at the time of the interrupt.
     * @param user User-defined data, expected to be a pointer to the PushButton instance.
     */
    static void buttonPressHandler(int gpio, int level, uint32_t tick, void *user); // Static ISR handler

    // Disabling copy constructor and assignment operator
    PushButton(const PushButton &) = delete;

    PushButton &operator=(const PushButton &) = delete;


private:
    int gpioPin;  ///< GPIO pin number.
    ButtonCallback buttonPressCallback;  ///< User-defined callback function to handle button press events.
};

#endif //CROSSGUARD_PUSHBUTTON_H
