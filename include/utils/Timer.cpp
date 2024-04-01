#include <future>
#include <chrono>
#include <functional>

class Timer { // TODO: Improve this class
public:
    template<typename Function>
    void setTimeout(Function function, int delay) {
        // Cancel the previous timer if it's running
        if (future.valid())
            stopTimer();

        // Launch a new asynchronous task that will wait and then execute the callback
        future = std::async(std::launch::async, [function, delay]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            function();
        });
    }

    void stopTimer() {
        // Check if the future is valid and then wait for the timer thread to finish
        if (future.valid()) {
            auto status = future.wait_for(std::chrono::milliseconds(0));
            if (status == std::future_status::timeout) {
                // The task is still running
                std::terminate(); // Forcefully terminates the thread, use with caution
            }
        }
    }

private:
    std::future<void> future;
};
