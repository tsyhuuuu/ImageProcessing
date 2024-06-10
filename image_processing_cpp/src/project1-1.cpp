#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// Object Detection using VideoCapture
// [Step.1] Color Detection
// [Step.2] Find Contours
// [Step.3] Get (x,y) position
// [Step.4] Draw Circle around Objects

vector<vector<int>> myColors;

Mat img, imgHSV, mask;

// 4 110 30 130 135 190 house
// 20,70,100,50,180,200 lab
int hmin = 4, smin = 30, vmin = 135;
int hmax = 110, smax = 135, vmax = 290;

VideoCapture cap(0);

void findColor(Mat img) {
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    namedWindow("Trackbars", (640, 200));  
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);
    
    Scalar lower(hmin, smin, vmin);
    Scalar upper(hmax, smax, vmax);
    inRange(imgHSV, lower, upper, mask);

    cout << hmin << "," << smin << "," << vmin << "," << hmax << "," << smax << "," << vmax << endl;
}

int main(int argc, char const *argv[])
{
    while (true) {
        cap.read(img);
        findColor(img);
        imshow("Camera", img);
        imshow("Mask", mask);
        waitKey(100);
    }

    return 0;
}
