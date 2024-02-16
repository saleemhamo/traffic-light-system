#include <wiringPi.h>

#define BUZZER_PIN 1 // WiringPi pin 1 corresponds to GPIO 18 (PWM pin)

int main(void) {
    if (wiringPiSetup() == -1) {
        return -1; // Initialization failed
    }

    pinMode(BUZZER_PIN, PWM_OUTPUT); // Set the buzzer pin to PWM output mode

    // Generate a simple tone
    pwmSetMode(PWM_MODE_MS); // Set PWM mode to Mark-Space
    pwmSetRange(1024); // Set the PWM range
    pwmSetClock(32); // Set the PWM clock divider

    pwmWrite(BUZZER_PIN, 512); // Set PWM value for generating tone
    delay(1000); // Sound the buzzer for 1 second

    pwmWrite(BUZZER_PIN, 0); // Turn off the buzzer

    return 0;
}
