#ifndef LIBCAM2OPENCV_H
#define LIBCAM2OPENCV_H

#include <opencv2/core.hpp>
#include <functional>

// Forward declaration from libcamera for required types
namespace libcamera {
    class Camera;
    class CameraManager;
    class FrameBufferAllocator;
    // Add more as required by your implementation
}

class Libcam2OpenCV {
public:
    Libcam2OpenCV();
    ~Libcam2OpenCV();

    // Start the camera and begin capturing
    bool start();

    // Stop the camera and cleanup resources
    void stop();

    // Set a callback function that will be called for each frame
    // The callback function must take an cv::Mat as its parameter
    void setFrameCallback(std::function<void(const cv::Mat&)> callback);

    // Method to be called for capturing a frame (implementation depends on libcamera setup)
    // This might be used internally in a loop within start(), or called by an external loop
    bool capture(cv::Mat& frame);

private:
    // Libcamera objects
    std::unique_ptr<libcamera::CameraManager> cameraManager;
    libcamera::Camera* camera;
    libcamera::FrameBufferAllocator* allocator;

    // Frame processing callback
    std::function<void(const cv::Mat&)> frameCallback;

    // Method to initialize libcamera components
    bool initializeCamera();

    // Convert libcamera frame buffer to OpenCV Mat
    cv::Mat convertFrameBufferToMat(const libcamera::FrameBuffer& buffer);

    // Add more helper methods and member variables as needed for your implementation
};

#endif // LIBCAM2OPENCV_H
