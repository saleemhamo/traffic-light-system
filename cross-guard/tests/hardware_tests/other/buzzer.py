import RPi.GPIO as GPIO
import time

# Pin Definitions
buzzerPin = 33  # GPIO 13 is physical pin 33

# Setup
GPIO.setmode(GPIO.BOARD)  # Use Physical pin numbering
GPIO.setup(buzzerPin, GPIO.OUT)  # Buzzer pin set as output

# Create PWM instance with frequency
buzzer = GPIO.PWM(buzzerPin, 500)  # Set frequency to 1000 Hz

try:
    buzzer.start(20)  # Start PWM with 50% duty cycle
    while True:
        time.sleep(1)  # Wait for 1 second
except KeyboardInterrupt:
    buzzer.stop()  # Stop the PWM
    GPIO.cleanup()  # Clean up GPIO settings on CTRL+C exit

GPIO.cleanup()  # Clean up GPIO settings on normal exit
