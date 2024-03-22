#ifndef CARSTIMER_H
#define CARSTIMER_H


#include "utils/CppTimer.h"
#include <atomic>
#include <thread>

class CarsTimer : public CppTimer
{

    void timerEvent()
    {
        // your timer event code here
    }
};

#endif // CARSTIMER_H