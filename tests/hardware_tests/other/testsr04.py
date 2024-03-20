import RPi.GPIO as GPIO
import time

# GPIO Pins setup
GPIO_TRIGGER = 32  # Physical pin 32
GPIO_ECHO = 31     # Physical pin 31

def setup():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setwarnings(False)  # Disable warnings
    GPIO.setup(GPIO_TRIGGER, GPIO.OUT)
    GPIO.setup(GPIO_ECHO, GPIO.IN)

def measure_distance():
    # Set trigger to False (Low)
    GPIO.output(GPIO_TRIGGER, False)
    time.sleep(0.5)

    # Send 10us pulse to trigger
    GPIO.output(GPIO_TRIGGER, True)
    time.sleep(0.00001)
    GPIO.output(GPIO_TRIGGER, False)
    start_time = time.time()

    # Record the last low time for timeout purposes
    while GPIO.input(GPIO_ECHO) == 0:
        start_time = time.time()

    # Record time of echo
    while GPIO.input(GPIO_ECHO) == 1:
        stop_time = time.time()

    # Calculate pulse length
    elapsed_time = stop_time - start_time
    distance = elapsed_time * 34300 / 2  # Speed of sound 34300 cm/s, divided by 2 for round trip

    return distance

if __name__ == '__main__':
    setup()
    try:
        while True:
            distance = measure_distance()
            print("Measured Distance = %.1f cm" % distance)
            time.sleep(1)
    except KeyboardInterrupt:
        print("Measurement stopped by User")
    finally:
        GPIO.cleanup()  # Ensure GPIOs are reset even if interrupted
