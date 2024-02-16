#include <wiringPi.h>
#include <stdio.h>
#include <sys/time.h>

#define TRIG 26 // WiringPi pin 26 corresponds to GPIO 12 (pin 32)
#define ECHO 22 // WiringPi pin 22 corresponds to GPIO 6 (pin 31)

void setup() {
    wiringPiSetup();
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Ensure the trigger pin is low
    digitalWrite(TRIG, LOW);
    delay(30);
}

int get_pulse_width() {
    int pulse_width = 0;
    struct timeval start_time, end_time;

    // Send pulse
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10); // 10 microseconds pulse
    digitalWrite(TRIG, LOW);

    // Wait for echo start
    while(digitalRead(ECHO) == LOW);

    // Echo start detected, now wait for echo end
    gettimeofday(&start_time, NULL);
    while(digitalRead(ECHO) == HIGH);
    gettimeofday(&end_time, NULL);

    // Calculate pulse width
    pulse_width = (int)(end_time.tv_usec - start_time.tv_usec);

    return pulse_width;
}

float calculate_distance(int pulse_width) {
    float distance_cm;
    distance_cm = pulse_width / 58.0; // Pulse width to distance conversion
    return distance_cm;
}

int main(void) {
    setup();

    printf("Measuring distance with HC-SR04\n");

    while(1) {
        int pulse_width = get_pulse_width();
        float distance = calculate_distance(pulse_width);

        printf("Distance: %.2f cm\n", distance);
        delay(1000); // Delay 1 second
    }

    return 0;
}
