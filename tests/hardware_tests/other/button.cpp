#include <pigpio.h>
#include <iostream>
#include <unistd.h>

#define btn 6

void btnHandler(int pin, int level, uint32_t tick)
{
    std::cout << "Button Pressed " << pin << " " << level << " " << tick << std::endl;
}

int main()
{
    if (gpioInitialise() < 0)
    {
        std::cerr << "Unable to connect PIGPIO, exiting" << std::endl;
        return 1;
    }

    gpioSetMode(btn, PI_INPUT);
    gpioSetPullUpDown(btn, PI_PUD_UP);
    gpioSetAlertFunc(btn, btnHandler);

    sleep(30);

    gpioTerminate();
    return 0;
}
