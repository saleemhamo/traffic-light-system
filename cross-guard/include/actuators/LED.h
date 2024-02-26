//
// Created by Saleem Hamo on 20/02/2024.
//

#pragma once

class LED {
public:
    LED(int pin);  // Constructor that takes the GPIO pin number
    void on();  // Turns the LED on
    void off();  // Turns the LED off

private:
    int pin;  // GPIO pin the LED is attached to
};
