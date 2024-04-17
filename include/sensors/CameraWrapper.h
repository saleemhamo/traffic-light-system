#include "utils/libcam2opencv.h"
#include <iostream>

class CameraWrapper : public Libcam2OpenCV::Callback {
public:
    CameraWrapper() {
        libcam2opencv.registerCallback(this);
    }

    void start(const Libcam2OpenCVSettings& settings = Libcam2OpenCVSettings()) {
        libcam2opencv.start(settings);
    }

    void stop() {
        libcam2opencv.stop();
    }

    void setMotionDetectedCallback(std::function<void()> callback) {
        motionDetectedCallback = callback;
    }

private:
    void hasFrame(const cv::Mat& frame, const libcamera::ControlList& metadata) override {
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        if (!prevGray.empty()) {
            if (detectMotion(gray, prevGray)) {
                auto now = std::chrono::steady_clock::now();
                if (now - lastDetectionTime > debounceDuration) {
                    lastDetectionTime = now;
                    if (motionDetectedCallback) {
                        motionDetectedCallback();
                    }
                }
            }
        }

        prevGray = gray.clone();
    }

    bool detectMotion(cv::Mat& frame, cv::Mat& prevFrame, double sensitivity = 50.0) {
        cv::Mat diff;
        cv::absdiff(prevFrame, frame, diff);
        cv::threshold(diff, diff, sensitivity, 255, cv::THRESH_BINARY);
        int nonZeroCount = cv::countNonZero(diff);
        return nonZeroCount > 0;
    }

    Libcam2OpenCV libcam2opencv;
    cv::Mat prevGray;
    std::chrono::steady_clock::time_point lastDetectionTime = std::chrono::steady_clock::now();
    std::chrono::milliseconds debounceDuration{500};
    std::function<void()> motionDetectedCallback;
};