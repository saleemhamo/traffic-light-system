#include <wiringPi.h>
#include <iostream>
#include <sys/time.h>

// Define GPIO pins for Trigger and Echo according to your setup
#define TRIG 27 // GPIO 27 - Pin 13
#define ECHO 18 // GPIO 18 - Pin 12

void setup() {
    wiringPiSetupGpio(); // Use Broadcom GPIO pin numbering
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Ensure the trigger pin is set low initially
    digitalWrite(TRIG, LOW);
    delay(30); // Wait for sensor to settle
}

long getEchoDuration() {
    // Trigger the sensor by sending a high pulse of 10 microseconds
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    // Wait for echo start
    while (digitalRead(ECHO) == LOW);

    // Record start time
    long startTime = micros();

    // Wait for echo end
    while (digitalRead(ECHO) == HIGH);

    // Record end time
    long endTime = micros();

    // Return the pulse duration in microseconds
    return endTime - startTime;
}

double calculateDistance(long duration) {
    // Speed of sound in air (in cm/us)
    double speedOfSound = 0.0343;
    double distance = (duration / 2.0) * speedOfSound;
    return distance;
}

int main() {
    setup();
    std::cout << "Measuring distance with HC-SR04 Ultrasonic Sensor..." << std::endl;

    while (true) {
        long duration = getEchoDuration();
        double distance = calculateDistance(duration);
        std::cout << "Distance: " << distance << " cm" << std::endl;
        delay(1000); // Delay before the next measurement
    }

    return 0;
}
