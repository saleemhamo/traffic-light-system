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
     * @param edge The edge to trigger the interrupt on (RISING_EDGE, FALLING_EDGE, or EITHER_EDGE).
     * @param debounceMs The debounce time in milliseconds.
     */
    PushButton(int pin, int edge, int debounceMs = 0);

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
     * @brief Detaches the interrupt service routine from the GPIO pin.
     */
    void detachInterruptHandler();

    /**
     * @brief Attaches the interrupt service routine to the GPIO pin.
     */
    void attachInterruptHandler();

    /**
     * @brief Initializes the GPIO pin as an input.
     */
    void gpioInit();

    /**
     * @brief Registers a callback function to be called when the button is pressed.
     * @param callback The function to call when the button is pressed.
     */
    void registerButtonPressCallback(ButtonCallback callback);

    /**
     * @brief Registers a callback function to be called when the button is released.
     * @param callback The function to call when the button is released.
     */
    void registerButtonReleaseCallback(ButtonCallback callback);

    // Disabling copy constructor and assignment operator
    PushButton(const PushButton &) = delete;

    PushButton &operator=(const PushButton &) = delete;


private:
    int gpioPin;  ///< GPIO pin number.
    int edgeMode; ///< Edge to trigger the interrupt on (RISING_EDGE, FALLING_EDGE, or EITHER_EDGE).
    int debounceMs;  ///< Debounce time in milliseconds.
    ButtonCallback buttonPressCallback;  ///< User-defined callback function to handle button press events.
    ButtonCallback buttonReleaseCallback;  ///< User-defined callback function to handle button release events.

    /**
     * @brief Static method used as the interrupt service routine for button presses.
     * @param gpio GPIO pin number where the interrupt occurred.
     * @param level New level of the GPIO pin after the interrupt.
     * @param tick System tick counter value at the time of the interrupt.
     * @param user User-defined data, expected to be a pointer to the PushButton instance.
     */
    static void buttonEventHandler(int gpio, int level, uint32_t tick, void *user); // Static ISR handler
};


#endif //CROSSGUARD_PUSHBUTTON_H