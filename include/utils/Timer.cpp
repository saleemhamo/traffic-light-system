#include <future>
#include <chrono>
#include <atomic>

class Timer {
public:
    Timer() : shouldExecute(false) {}

    template<typename Function>
    void setTimeout(Function function, int delay) {
        // Ensure any existing timer is stopped before starting a new one
        stopTimer();

        // Set execution flag to true
        shouldExecute.store(true);

        // Launch a new asynchronous task that will wait and then execute the callback
        future = std::async(std::launch::async, [this, function, delay]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            if (shouldExecute.load()) // Check the flag before executing the function
                function();
        });
    }

    void stopTimer() {
        // Set the execution flag to false to prevent the function from being called
        shouldExecute.store(false);

        if (future.valid()) {
            // Wait for the thread to finish execution
            future.wait();
        }
    }

private:
    std::future<void> future;
    std::atomic<bool> shouldExecute; // Flag to control the execution
};
