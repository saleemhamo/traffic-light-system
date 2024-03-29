#include <wiringPi.h>
#include <iostream>
#include <unistd.h> // For sleep and usleep

// Class for controlling an LED
class LEDControl {
public:
    int pin; // GPIO pin associated with the LED
    // Constructor to initialize the LED with the specified GPIO pin
    LEDControl(int gpioPin) : pin(gpioPin) {
        pinMode(pin, OUTPUT); // Set the GPIO pin to output mode
    }
    // Method to turn the LED on
    void on() {
        digitalWrite(pin, HIGH); // Set the GPIO pin high to turn the LED on
    }
    // Method to turn the LED off
    void off() {
        digitalWrite(pin, LOW); // Set the GPIO pin low to turn the LED off
    }
    // Method to toggle the LED state
    void toggle() {
        // Read the current state and set the opposite state
        digitalWrite(pin, !digitalRead(pin));
    }
};

// Class for handling a button
class Button {
public:
    int pin; // GPIO pin associated with the button
    // Constructor to initialize the button with the specified GPIO pin
    Button(int gpioPin) : pin(gpioPin) {
        pinMode(pin, INPUT); // Set the GPIO pin to input mode
        // Enable the internal pull-up resistor to make the button logic active-low
        pullUpDnControl(pin, PUD_UP);
    }
    // Method to check if the button is pressed
    bool isPressed() {
        // Return true if the button is pressed (logic level is LOW due to pull-up resistor)
        return digitalRead(pin) == LOW;
    }
};

// Function to control an LED based on button press events
void buttonLEDControl(Button& button, LEDControl& led) {
    bool lastState = false; // Variable to store the last state of the button
    while (true) { // Infinite loop to continuously check the button state
        bool currentState = button.isPressed(); // Read the current state of the button
        if (currentState != lastState) { // Check if the button state has changed
            if (currentState) { // If the button is currently pressed
                led.toggle(); // Toggle the LED state
            }
            lastState = currentState; // Update the lastState with the current state
        }
        usleep(100000); // Add a debounce delay of 100 milliseconds
    }
}

// Main function
int main() {
    wiringPiSetupGpio(); // Initialize wiringPi to use the Broadcom GPIO pin numbers

    Button button(23); // Create a Button object for GPIO 23
    LEDControl led(24); // Create an LEDControl object for GPIO 24

    buttonLEDControl(button, led); // Call the buttonLEDControl function to start the control logic

    return 0; // End of program
}
