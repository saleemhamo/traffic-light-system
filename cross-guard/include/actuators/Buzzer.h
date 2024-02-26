//
// Created by Saleem Hamo on 20/02/2024.
//
class Buzzer {
public:
    explicit Buzzer(int pin);  // Constructor that takes the GPIO pin number
    void on();  // Turns the buzzer on
    void off();  // Turns the buzzer off

private:
    int pin;  // GPIO pin the Buzzer is attached to
};

