#include <wiringPi.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h> // For sleep()

class UltrasonicSensor {
    int trigPin, echoPin;

public:
    UltrasonicSensor(int trig, int echo) : trigPin(trig), echoPin(echo) {
        pinMode(trigPin, OUTPUT);
        pinMode(echoPin, INPUT);
        digitalWrite(trigPin, LOW); // Ensure trigger is low
    }

    float measureDistance() {
        long startTime, endTime;
        float distance;

        // Trigger the pulse
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);

        // Wait for echo start
        while(digitalRead(echoPin) == LOW);

        startTime = micros();

        // Wait for echo end
        while(digitalRead(echoPin) == HIGH);

        endTime = micros();

        // Calculate distance in cm
        distance = ((endTime - startTime) * 0.0343) / 2;

        return distance;
    }
};

class LEDControl {
    int pin;
public:
    LEDControl(int gpioPin) : pin(gpioPin) {
        pinMode(pin, OUTPUT);
    }
    void on() { digitalWrite(pin, HIGH); }
    void off() { digitalWrite(pin, LOW); }
};

class Buzzer {
    int pin;
public:
    Buzzer(int gpioPin) : pin(gpioPin) {
        pinMode(pin, OUTPUT);
    }
    void alarm() {
        // Simple sound generation through toggling
        for (int i = 0; i < 100; ++i) { // Generate a simple tone
            digitalWrite(pin, HIGH);
            delay(1); // Adjust timing for tone generation
            digitalWrite(pin, LOW);
            delay(1);
        }
    }
};

class Controller {
    UltrasonicSensor sensor1, sensor2;
    LEDControl pedestrianRedLED, pedestrianGreenLED;
    Buzzer alarmBuzzer;

public:
    Controller() : sensor1(27, 22), sensor2(5, 6), 
                   pedestrianRedLED(4), pedestrianGreenLED(17), alarmBuzzer(13) {}

    void run() {
        while(true) {
            float distance1 = sensor1.measureDistance();
            float distance2 = sensor2.measureDistance();

            // Control pedestrian LEDs based on sensor1
            if (distance1 < 15) {
                pedestrianGreenLED.on();
                pedestrianRedLED.off();
            } else {
                pedestrianGreenLED.off();
                pedestrianRedLED.on();
            }

            // Sound the buzzer if sensor2 detects an object too close
            if (distance2 < 15) {
                alarmBuzzer.alarm();
            }

            delay(1000); // Check every second
        }
    }
};

int main() {
    if (wiringPiSetupGpio() == -1) {
        std::cout << "Could not set up wiringPi" << std::endl;
        return -1;
    }

    Controller controlSystem;
    controlSystem.run();

    return 0;
}
