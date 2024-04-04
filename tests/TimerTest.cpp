#define BOOST_TEST_MODULE TimerTest
#include <boost/test/included/unit_test.hpp>
#include "utils/Timer.h"

BOOST_AUTO_TEST_SUITE(TimerSuite)

    BOOST_AUTO_TEST_CASE(testTimerExecution) {
        Timer timer;
        bool executed = false;

        // Schedule a function to set 'executed' to true after 100 milliseconds
        timer.setTimeout([&executed]() {
            executed = true;
        }, 100);

        // Wait a bit longer than 100 milliseconds to give the timer time to execute
        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        // Check if the function was executed
        BOOST_CHECK(executed == true);
    }

    BOOST_AUTO_TEST_CASE(testStopTimer) {
        Timer timer;
        bool executed = false;

        // Schedule a function to set 'executed' to true after 300 milliseconds
        timer.setTimeout([&executed]() {
            executed = true;
        }, 300);

        // Stop the timer after 100 milliseconds, before the scheduled function can execute
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        timer.stopTimer();

        // Wait a bit longer than the original timer to ensure it would have executed
        std::this_thread::sleep_for(std::chrono::milliseconds(400));

        // Check if the function was prevented from executing
        BOOST_CHECK(executed == false);
    }

BOOST_AUTO_TEST_SUITE_END()
