#include <wiringPi.h>
#include <stdio.h>

#define LED_PIN 7 // WiringPi pin 7 corresponds to GPIO 4 (physical pin 7)

int main(void) {
    if (wiringPiSetup() == -1) {
        printf("setup wiringPi failed!\n");
        return 1;
    }

    pinMode(LED_PIN, OUTPUT); // Set pin mode to output

    while (1) {
        digitalWrite(LED_PIN, HIGH); // Turn the LED on
        delay(1000); // Wait for a second
        digitalWrite(LED_PIN, LOW); // Turn the LED off
        delay(1000); // Wait for a second
    }

    return 0;
}
