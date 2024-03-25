#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include "utils/CppTimer.h"
#include <atomic>
#include <thread>

class SystemTimer : public CppTimer
{
public:
    SystemTimer(MainSystem &mainSystem) : m_mainSystem(mainSystem) {}

    void startTimer(long millisecs, cppTimerType_t type = PERIODIC)
    {
        startms(millisecs, type);
    }

    void stopTimer()
    {
        stop();
    }

protected:
    virtual void timerEvent() override
    {
        // Implement the desired behavior when the timer fires
        // This could involve calling a method on the MainSystem instance
        m_mainSystem.handleTimerEvent();
    }

private:
    MainSystem &m_mainSystem;
};

#endif // SYSTEMTIMER_H