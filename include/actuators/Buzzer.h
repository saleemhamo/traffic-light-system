//
// Created by Saleem Hamo on 20/02/2024.
//

/**
 * @class Buzzer
 * @brief A class to control a buzzer connected to a GPIO pin.
 *
 * This class provides simple interfaces to turn a buzzer on and off
 * using the specified GPIO pin on a Raspberry Pi or compatible devices.
 * It relies on the pigpio library (or its stub for non-Raspberry Pi environments)
 * for GPIO pin control.
 */
class Buzzer {
public:
    /**
     * @brief Constructs a Buzzer object associated with a specific GPIO pin.
     *
     * Initializes the GPIO library if necessary and sets the specified pin
     * as an output for the buzzer control.
     *
     * @param pin The GPIO pin number where the buzzer is connected.
     */
    explicit Buzzer(int pin);

    /**
     * @brief Turns the buzzer on by setting the GPIO pin high.
     */
    void on();

    /**
     * @brief Turns the buzzer off by setting the GPIO pin low.
     */
    void off();

private:
    int pin;  ///< GPIO pin number associated with the buzzer.
};
