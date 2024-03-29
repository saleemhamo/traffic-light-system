import RPi.GPIO as GPIO
import time

# Pin Definitions
ledPin = 7  # GPIO 4 is physical pin 7

# Setup
GPIO.setmode(GPIO.BOARD)  # Use Physical pin numbering
GPIO.setup(ledPin, GPIO.OUT)  # LED pin set as output

try:
    while True:
        GPIO.output(ledPin, GPIO.HIGH)  # Turn on LED
        time.sleep(1)  # Wait for 1 second
        GPIO.output(ledPin, GPIO.LOW)  # Turn off LED
        time.sleep(1)  # Wait for 1 second
except KeyboardInterrupt:
    GPIO.cleanup()  # Clean up GPIO settings on CTRL+C exit

GPIO.cleanup()  # Clean up GPIO settings on normal exit
