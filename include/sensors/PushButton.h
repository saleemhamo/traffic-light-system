#ifndef CROSSGUARD_PUSHBUTTON_H
#define CROSSGUARD_PUSHBUTTON_H

#include <cstdint>

#if defined(__linux__) && defined(__arm__)
#include <pigpio.h>
#else

#include "pigpio_stub.h"

#endif

#include <functional>


class PushButton {
public:
    using ButtonCallback = std::function<void()>;

    PushButton(int pin);

    ~PushButton();

    void initialize();

    void registerButtonPressCallback(ButtonCallback callback);

    // Disabling copy constructor and assignment operator
    PushButton(const PushButton &) = delete;

    PushButton &operator=(const PushButton &) = delete;


private:
    int gpioPin;
    ButtonCallback buttonPressCallback;

    static void buttonPressHandler(int gpio, int level, uint32_t tick, void *user); // Static ISR handler

};


#endif //CROSSGUARD_PUSHBUTTON_H
