#ifndef CAMERASENSOR_H
#define CAMERASENSOR_H

#include <opencv2/opencv.hpp>
#include <thread>
#include <atomic>
#include <functional>
#include <chrono>

/**
 * @class CameraSensor
 * @brief Handles camera operations and motion detection using OpenCV.
 *
 * This class provides functionalities to capture video frames from a camera,
 * detect motion between frames, and execute a callback when motion is detected.
 */
class CameraSensor {
public:
    /**
     * @brief Constructor for CameraSensor.
     */
    CameraSensor();

    /**
     * @brief Destructor for CameraSensor.
     */
    ~CameraSensor();

    /**
     * @brief Callback type for motion detection.
     */
    using CallbackType = std::function<void()>;

    /**
     * @brief Initializes the camera for capturing video.
     *
     * @return True if the camera was successfully opened, false otherwise.
     */
    bool initialize();

    /**
     * @brief Starts the video capture and motion detection in a separate thread.
     */
    void run();

    /**
     * @brief Stops the video capture and motion detection thread.
     */
    void stop();

    /**
     * @brief Sets the callback function to be called when motion is detected.
     *
     * @param callback The function to call when motion is detected.
     */
    void setMotionDetectedCallback(CallbackType callback);

private:
    cv::VideoCapture cap; ///< OpenCV video capture object.
    std::atomic<bool> running; ///< Flag to control the running of the capture loop.
    std::thread captureThread; ///< Thread for running the capture loop.
    CallbackType motionDetectedCallback; ///< Callback function for motion detection.
    std::chrono::steady_clock::time_point lastDetectionTime; ///< Last time motion was detected.
    std::chrono::milliseconds debounceDuration{500}; ///< Debounce duration in milliseconds.

    /**
     * @brief The loop that captures video frames and checks for motion.
     */
    void captureLoop();

    /**
     * @brief Detects motion between two frames.
     *
     * @param frame The current video frame.
     * @param prevFrame The previous video frame.
     * @param sensitivity Sensitivity threshold for motion detection.
     * @return True if motion is detected, false otherwise.
     */
    bool detectMotion(cv::Mat& frame, cv::Mat& prevFrame, double sensitivity = 50.0);
};

#endif // CAMERASENSOR_H
