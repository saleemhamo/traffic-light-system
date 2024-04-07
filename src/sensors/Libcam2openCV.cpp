#include "Libcam2OpenCV.h"
#include <libcamera/camera_manager.h>
#include <libcamera/stream.h>
#include <libcamera/frame_buffer_allocator.h>
#include <libcamera/controls.h>
#include <libcamera/framebuffer.h>
#include <opencv2/opencv.hpp>
#include <sys/mman.h>
#include <iostream>
#include <stdexcept>
#include <functional>

Libcam2OpenCV::Libcam2OpenCV() {
    cameraManager = std::make_unique<libcamera::CameraManager>();
    int ret = cameraManager->start();
    if (ret) {
        throw std::runtime_error("Failed to start camera manager");
    }
    // Initialize any other members or state as necessary.
}

Libcam2OpenCV::~Libcam2OpenCV() {
    stop(); // Ensure resources are released
}

bool Libcam2OpenCV::start() {
    auto cameras = cameraManager->cameras();
    if (cameras.empty()) {
        std::cerr << "No cameras found." << std::endl;
        return false;
    }

    camera = cameras.front();
    if (camera->acquire()) {
        std::cerr << "Failed to acquire the camera." << std::endl;
        return false;
    }

    // Omitted: Detailed configuration for brevity.

    camera->start();

    // Connect to the 'requestCompleted' signal to handle completed capture requests.
    camera->requestCompleted.connect(this, &Libcam2OpenCV::onRequestComplete);

    return true;
}

void Libcam2OpenCV::stop() {
    if (camera) {
        camera->stop();
        camera->release();
        camera.reset();
    }
    if (cameraManager) {
        cameraManager->stop();
    }
}

void Libcam2OpenCV::setFrameCallback(std::function<void(const cv::Mat&)> callback) {
    frameCallback = std::move(callback);
}

void Libcam2OpenCV::onRequestComplete(libcamera::Request *request) {
    if (request->status() != libcamera::Request::RequestComplete) {
        std::cerr << "Request not completed successfully" << std::endl;
        return;
    }

    for (auto &[stream, buffer] : request->buffers()) {
        auto mem = mmap(nullptr, buffer->planes()[0].length, PROT_READ, MAP_SHARED, buffer->planes()[0].fd.fd(), 0);
        if (mem == MAP_FAILED) {
            std::cerr << "Failed to map memory" << std::endl;
            continue;
        }

        // Here, you should adjust 'cvFormat' and 'width', 'height' based on your actual camera configuration.
        cv::Mat frame(cv::Size(width, height), cvFormat, mem, cv::Mat::AUTO_STEP);

        if (frameCallback) {
            frameCallback(frame.clone()); // Clone the frame if it's going to be used outside the callback.
        }

        munmap(mem, buffer->planes()[0].length);
    }

    // Re-queue the request for the next frame.
    camera->queueRequest(request);
}

// Additional methods to support frame handling as needed...
