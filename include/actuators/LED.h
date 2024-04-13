//
// Created by Saleem Hamo on 20/02/2024. Documented by Miguel Rosa
//
#pragma once
/**
 * @file LED.h
 * @brief Header file for the LED class, which controls an LED via a GPIO pin.
 
 */

/**
 * @class LED
 * @brief Controls an LED connected to a GPIO pin.
 *
 * This class provides methods to turn an LED on and off, abstracting the
 * hardware interfacing details.
 */
class LED {
public:
    /**
     * @brief Constructor that initializes an LED object attached to a specified GPIO pin.
     * @param pin GPIO pin number that the LED is connected to.
     */
    LED(int pin);

    /**
     * @brief Turns the LED on by setting the GPIO pin high.
     */
    void on();

    /**
     * @brief Turns the LED off by setting the GPIO pin low.
     */
    void off();

private:
    int pin;  ///< GPIO pin number the LED is attached to.
};