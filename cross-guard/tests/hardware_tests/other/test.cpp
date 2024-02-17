#include <iostream>
#include <wiringPi.h>

// Define GPIO pin numbers
const int PEDESTRIAN_RED_PIN = 4;
const int PEDESTRIAN_GREEN_PIN = 17;
const int TRAFFIC_GREEN_PIN = 24;
const int TRAFFIC_YELLOW_PIN = 25;
const int TRAFFIC_RED_PIN = 5;
const int BUZZER_PIN = 13;
const int SWITCH_PIN = 23;
const int ECHO1_PIN = 18;
const int TRIG1_PIN = 27;
const int ECHO2_PIN = 6;
const int TRIG2_PIN = 12;
const int ALARM1_PIN = 21;
const int ALARM2_PIN = 19;
const int ALARM3_PIN = 16;

int main() {
    // Initialize WiringPi library
    if (wiringPiSetup() == -1) {
        std::cerr << "Failed to initialize WiringPi library" << std::endl;
        return 1;
    }

    // Set GPIO pins as output or input
    pinMode(PEDESTRIAN_RED_PIN, OUTPUT);
    pinMode(PEDESTRIAN_GREEN_PIN, OUTPUT);
    pinMode(TRAFFIC_GREEN_PIN, OUTPUT);
    pinMode(TRAFFIC_YELLOW_PIN, OUTPUT);
    pinMode(TRAFFIC_RED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(SWITCH_PIN, INPUT);
    pinMode(ECHO1_PIN, INPUT);
    pinMode(TRIG1_PIN, OUTPUT);
    pinMode(ECHO2_PIN, INPUT);
    pinMode(TRIG2_PIN, OUTPUT);
    pinMode(ALARM1_PIN, OUTPUT);
    pinMode(ALARM2_PIN, OUTPUT);
    pinMode(ALARM3_PIN, OUTPUT);

    // Turn on pedestrian red light and traffic green light
    digitalWrite(PEDESTRIAN_RED_PIN, HIGH);
    digitalWrite(PEDESTRIAN_GREEN_PIN, LOW);
    digitalWrite(TRAFFIC_GREEN_PIN, HIGH);
    digitalWrite(TRAFFIC_YELLOW_PIN, LOW);
    digitalWrite(TRAFFIC_RED_PIN, LOW);

    // Main program loop
    while (true) {
        // Your logic here
        
        // Example: Toggle pedestrian green light every 10 seconds
        delay(10000);
        digitalWrite(PEDESTRIAN_RED_PIN, LOW);
        digitalWrite(PEDESTRIAN_GREEN_PIN, HIGH);
        delay(10000);
        digitalWrite(PEDESTRIAN_RED_PIN, HIGH);
        digitalWrite(PEDESTRIAN_GREEN_PIN, LOW);
    }

    return 0;
}
