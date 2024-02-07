#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture capture(1); // Open default camera

    if (!capture.isOpened()) {
        cout << "Error opening video stream" << endl;
        return -1;
    }

    // Create a BackgroundSubtractorMOG2 object
    Ptr<BackgroundSubtractorMOG2> mog2 = createBackgroundSubtractorMOG2();

    Mat frame, foregroundMask;

    // Capture the initial frame
    if (!capture.read(frame)) {
        cout << "Error reading the initial frame" << endl;
        return -1;
    }

    while (true) {
        // Capture the current frame
        if (!capture.read(frame)) {
            cout << "Error reading a frame" << endl;
            break;
        }

        // Apply the BackgroundSubtractorMOG2 to the current frame
        mog2->apply(frame, foregroundMask);

        // Threshold the foreground mask to create a binary mask
        threshold(foregroundMask, foregroundMask, 128, 255, THRESH_BINARY);

        // Find contours in the binary mask
        vector<vector<Point> > contours;
        findContours(foregroundMask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (int i = 0; i < contours.size(); i++) {
            if (contourArea(contours[i]) > 1000) {
                putText(frame, "Motion Detected", Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 2);
                break;
            }
        }

        // Show the camera feed and motion detection overlay
        imshow("Camera Feed with Motion Detection", frame);

        char c = (char) waitKey(25);
        if (c == 27)
            break;
    }

    capture.release();
    destroyAllWindows();
    return 0;
}
