#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio.hpp>

int main() {
    // Open the camera (use camera ID 0 for default camera)
    cv::VideoCapture cap(0, cv::CAP_FFMPEG);  // Use FFMPEG backend
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open the camera." << std::endl;
        return -1;
    }

    // Set FFmpeg to use VA-API for hardware acceleration
    cap.set(cv::CAP_PROP_FFMPEG_HW_ACCELERATION, cv::VideoCaptureAPIs::CAP_FFMPEG_HW_ACCELERATION_VAAPI);
    
    // Frame capture and processing loop
    cv::Mat frame;
    while (true) {
        // Capture frame
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Empty frame." << std::endl;
            break;
        }

        // Process frame (convert to grayscale as an example)
        cv::Mat gray_frame;
        cv::cvtColor(frame, gray_frame, cv::COLOR_BGR2GRAY);

        // Show the frame
        cv::imshow("Processed Frame", gray_frame);

        // Exit if the user presses the "q" key
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Release the camera and close all windows
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
