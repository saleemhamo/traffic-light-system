#include <wiringPi.h>

// Define GPIO pin numbers for LEDs
const int RED_LED_PIN = 24;
const int YELLOW_LED_PIN = 25;
const int GREEN_LED_PIN = 5;

int main() {
    // Initialize WiringPi library
    if (wiringPiSetup() == -1) {
        // Handle initialization error
        return 1;
    }

    // Set GPIO pins as output
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(YELLOW_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);

    // Turn on the traffic lights (assuming active-low configuration)
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, LOW);

    // Simulate a delay (e.g., for pedestrian crossing)
    delay(5000);  // 5 seconds

    // Change lights to allow pedestrian crossing
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);

    // Simulate pedestrian crossing
    delay(10000);  // 10 seconds

    // Change lights back to normal traffic flow
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(YELLOW_LED_PIN, HIGH);

    // Simulate a brief transition period
    delay(2000);  // 2 seconds

    // Turn off yellow light and turn on red light
    digitalWrite(YELLOW_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);

    // End of simulation
    return 0;
}
