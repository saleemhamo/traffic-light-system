#include <wiringPi.h>
#include <iostream>
#include <unistd.h> // For sleep()

// Base class for controlling a single LED
class LEDControl {
protected:
    int pin; // GPIO pin associated with the LED
public:
    // Constructor initializes the LED by setting the pin mode
    LEDControl(int gpioPin) : pin(gpioPin) {
        pinMode(pin, OUTPUT); // Set the GPIO pin to output mode
    }
    // Turns the LED on
    void on() {
        digitalWrite(pin, HIGH); // Set the GPIO pin high to turn the LED on
    }
    // Turns the LED off
    void off() {
        digitalWrite(pin, LOW); // Set the GPIO pin low to turn the LED off
    }
};

// Derived class for controlling Alarm LEDs
class AlarmLED : public LEDControl {
public:
    AlarmLED(int gpioPin) : LEDControl(gpioPin) {}
};

// Derived class for controlling Pedestrian LEDs
class PedestrianLED : public LEDControl {
public:
    PedestrianLED(int gpioPin) : LEDControl(gpioPin) {}
};

// Derived class for controlling Traffic Light LEDs
class TrafficLightLED : public LEDControl {
public:
    TrafficLightLED(int gpioPin) : LEDControl(gpioPin) {}
};

class Button {
public:
    int pin;
    Button(int gpioPin) : pin(gpioPin) {
        pinMode(pin, INPUT);
        pullUpDnControl(pin, PUD_UP); // Enable pull-up resistor
    }
    bool isPressed() {
        return digitalRead(pin) == LOW; // Button press detected when LOW
    }
};

// Controller class to manage all LEDs and implement test modes
class LEDController {
private:
    AlarmLED* alarmLEDs[3]; // Array of pointers to AlarmLED objects
    PedestrianLED* pedestrianLEDs[2]; // Array of pointers to PedestrianLED objects
    TrafficLightLED* trafficLightLEDs[3]; // Array of pointers to TrafficLightLED objects

public:
    // Constructor initializes all LED objects with their respective GPIO pins
    LEDController() {
        alarmLEDs[0] = new AlarmLED(21);
        alarmLEDs[1] = new AlarmLED(19);
        alarmLEDs[2] = new AlarmLED(16);

        pedestrianLEDs[0] = new PedestrianLED(4); // Red
        pedestrianLEDs[1] = new PedestrianLED(17); // Green

        trafficLightLEDs[0] = new TrafficLightLED(5); // Red
        trafficLightLEDs[1] = new TrafficLightLED(24); // Green
        trafficLightLEDs[2] = new TrafficLightLED(25); // Yellow
    }

    void testAlarmLEDs() {
        for (int i = 0; i < 3; ++i) {
            alarmLEDs[i]->on();
            sleep(1);
            alarmLEDs[i]->off();
        }
    }

    void testPedestrianLEDs() {
        pedestrianLEDs[0]->on();
        sleep(2);
        pedestrianLEDs[0]->off();
        pedestrianLEDs[1]->on();
        sleep(2);
        pedestrianLEDs[1]->off();
    }

    void testTrafficLightLEDs() {
        trafficLightLEDs[0]->on();
        sleep(3);
        trafficLightLEDs[0]->off();
        trafficLightLEDs[1]->on();
        sleep(3);
        trafficLightLEDs[1]->off();
        trafficLightLEDs[2]->on();
        sleep(2);
        trafficLightLEDs[2]->off();
        trafficLightLEDs[0]->on(); // Turn on Red LED again 
        sleep(1);
        trafficLightLEDs[0]->off();
    }

    void allOnThenOff() {
        for (int i = 0; i < 3; ++i) alarmLEDs[i]->on();
        for (int i = 0; i < 2; ++i) pedestrianLEDs[i]->on();
        for (int i = 0; i < 3; ++i) trafficLightLEDs[i]->on();
        sleep(2);
        for (int i = 0; i < 3; ++i) alarmLEDs[i]->off();
        for (int i = 0; i < 2; ++i) pedestrianLEDs[i]->off();
        for (int i = 0; i < 3; ++i) trafficLightLEDs[i]->off();
    }
	
void progressOnButtonPress(Button &button) {
    int currentState = 0;
    while (true) {
        if (button.isPressed()) {
            // Debounce delay
            delay(200); // 200 milliseconds
            std::cout << "Button pressed. Progressing to state: " << currentState << std::endl;
            switch (currentState) {
                case 0:
                    std::cout << "Testing Alarm LEDs..." << std::endl;
                    testAlarmLEDs();
                    break;
                case 1:
                    std::cout << "Testing Pedestrian LEDs..." << std::endl;
                    testPedestrianLEDs();
                    break;
                case 2:
                    std::cout << "Testing Traffic Light LEDs..." << std::endl;
                    testTrafficLightLEDs();
                    break;
                case 3:
                    std::cout << "Turning all LEDs on, then off..." << std::endl;
                    allOnThenOff();
                    break;
            }
            currentState = (currentState + 1) % 4; // Loop back after the last state
            
            std::cout << "Move to next state: " << currentState << std::endl;

            // Wait for button release to avoid multiple triggers
            while (button.isPressed()) {
                delay(100); // Check every 100 milliseconds
            }
        }
        delay(100); // Polling delay
    }
}

    ~LEDController() {
        for (int i = 0; i < 3; ++i) delete alarmLEDs[i];
        for (int i = 0; i < 2; ++i) delete pedestrianLEDs[i];
        for (int i = 0; i < 3; ++i) delete trafficLightLEDs[i];
    }
};

int main() {
    wiringPiSetupGpio(); // Initialize wiringPi using Broadcom GPIO numbering
    LEDController controller;
    Button button(23); // Assuming GPIO 23 is used for the button

    controller.progressOnButtonPress(button); // Start interactive LED test sequence

    return 0;
}
