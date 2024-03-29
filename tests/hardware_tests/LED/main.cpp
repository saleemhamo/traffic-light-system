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
    // Constructor uses base class constructor to initialize the GPIO pin
    AlarmLED(int gpioPin) : LEDControl(gpioPin) {}
    // Additional functionality specific to Alarm LEDs can be added here
};

// Derived class for controlling Pedestrian LEDs
class PedestrianLED : public LEDControl {
public:
    PedestrianLED(int gpioPin) : LEDControl(gpioPin) {}
    // Pedestrian LED specific functions can be added here
};

// Derived class for controlling Traffic Light LEDs
class TrafficLightLED : public LEDControl {
public:
    TrafficLightLED(int gpioPin) : LEDControl(gpioPin) {}
    // Traffic light specific functions can be added here
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

    // Function to test all LED groups
    void testAll() {
        testAlarmLEDs();
        testPedestrianLEDs();
        testTrafficLightLEDs();
    }

    // Function to test Alarm LEDs by turning each on then off sequentially
    void testAlarmLEDs() {
        for (int i = 0; i < 3; ++i) {
            alarmLEDs[i]->on();
            sleep(1);
            alarmLEDs[i]->off();
        }
    }

    // Function to test Pedestrian LEDs by simulating a pedestrian crossing signal
    void testPedestrianLEDs() {
        pedestrianLEDs[0]->on(); // Turn on Red LED
        sleep(2);
        pedestrianLEDs[0]->off();
        pedestrianLEDs[1]->on(); // Turn on Green LED
        sleep(2);
        pedestrianLEDs[1]->off();
    }

    // Function to test Traffic Light LEDs by simulating a traffic light sequence
    void testTrafficLightLEDs() {
        trafficLightLEDs[0]->on(); // Turn on Red LED
        sleep(3);
        trafficLightLEDs[0]->off();
        trafficLightLEDs[1]->on(); // Turn on Green LED
        sleep(3);
        trafficLightLEDs[1]->off();
        trafficLightLEDs[2]->on(); // Turn on Yellow LED
        sleep(2);
        trafficLightLEDs[2]->off();
	trafficLightLEDs[0]->on(); // Turn on Red LED again 
        sleep(1);
        trafficLightLEDs[0]->off();
    }

    // Function to turn all LEDs on, then all off
    void allOnThenOff() {
        for (int i = 0; i < 3; ++i) alarmLEDs[i]->on();
        for (int i = 0; i < 2; ++i) pedestrianLEDs[i]->on();
        for (int i = 0; i < 3; ++i) trafficLightLEDs[i]->on();
        sleep(2);
        for (int i = 0; i < 3; ++i) alarmLEDs[i]->off();
        for (int i = 0; i < 2; ++i) pedestrianLEDs[i]->off();
        for (int i = 0; i < 3; ++i) trafficLightLEDs[i]->off();
    }

    // Destructor to clean up dynamically allocated LED objects
    ~LEDController() {
        for (int i = 0; i < 3; ++i) delete alarmLEDs[i];
        for (int i = 0; i < 2; ++i) delete pedestrianLEDs[i];
        for (int i = 0; i < 3; ++i) delete trafficLightLEDs[i];
    }
};

// Main function to initialize the controller and run tests
int main() {
    wiringPiSetupGpio(); // Initialize wiringPi using Broadcom GPIO numbering
    LEDController controller;

    controller.testAll(); // Run all tests
    controller.allOnThenOff(); // Run additional mode example

    return 0;
}
