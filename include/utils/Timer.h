/**
 * @file Timer.h
 * @brief Declaration and implementation of the Timer class for asynchronous execution.
 *
 * Provides a mechanism to execute a function after a delay in a non-blocking manner.
 * Utilizes std::async and std::future to manage asynchronous execution.
 */

#ifndef CROSSGUARD_TIMER
#define CROSSGUARD_TIMER

#include <chrono>
#include <atomic>
#include <future>

/**
 * @class Timer
 * @brief Timer class for asynchronous execution after a specified delay.
 *
 * The Timer class allows scheduling a function to be executed after a specified
 * delay. It provides functionality to stop the timer, preventing the execution
 * of the function if needed.
 */
class Timer {
public:
    /**
     * @brief Default constructor. Initializes the timer in a stopped state.
     */
    Timer() : shouldExecute(false), isRunning(false) {}

    /**
     * @brief Starts a timer to execute a function after a specified delay.
     *
     * If there is an ongoing timer, it is stopped before starting the new one.
     *
     * @tparam Function Type of the function to be executed.
     * @param function Function to be executed after the delay.
     * @param delayMs Delay in milliseconds before the function is executed.
     */
    template<typename Function>
    void setTimeout(Function function, int delayMs) {
        stopTimer(); // Ensure any existing timer is stopped

        shouldExecute.store(true);
        isRunning.store(true);

        future = std::async(std::launch::async, [this, function, delayMs]() {
            auto start = std::chrono::high_resolution_clock::now();
            auto end = start + std::chrono::milliseconds(delayMs);

            while (std::chrono::high_resolution_clock::now() < end) {
                if (!shouldExecute.load()) break; // Exit early if stopped
            }

            if (shouldExecute.load() && isRunning.load()) {
                function(); // Execute the function
            }

            isRunning.store(false);
        });
    }

    /**
     * @brief Stops any ongoing timer and prevents the scheduled function from executing.
     *
     * If the timer is already stopped or the function has already executed, this method does nothing.
     */
    void stopTimer() {
        shouldExecute.store(false); // Prevent execution

        if (future.valid()) {
            future.wait(); // Ensure any ongoing asynchronous operation completes
        }
    }

private:
    std::future<void> future; ///< Future associated with the async operation of the timer.
    std::atomic<bool> shouldExecute; ///< Flag indicating if the scheduled function should execute.
    std::atomic<bool> isRunning; ///< Flag indicating if the timer is currently running.
};

#endif // CROSSGUARD_TIMER
