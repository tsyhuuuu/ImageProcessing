#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// color detection(extract target color from your image)
// draw contours for the image

Mat imgHSV, mask;
Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

int hmin = 0, smin = 0, vmin = 30;
// int hmax = 179, smax = 0, vmax = 255;
int hmax = 150, smax = 50, vmax = 255;

void ColorDetection(string path){
    Mat img = imread(path);

    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    // create trackbars for variables in "Trackbars" window
    // createTrackbar(trackBarName, WindowName, variableName, maximum);
    namedWindow("Trackbars", (640, 200));  
    createTrackbar("Hue Min", "Trackbars", &hmin, 179);
    createTrackbar("Hue Max", "Trackbars", &hmax, 179);
    createTrackbar("Sat Min", "Trackbars", &smin, 255);
    createTrackbar("Sat Max", "Trackbars", &smax, 255);
    createTrackbar("Val Min", "Trackbars", &vmin, 255);
    createTrackbar("Val Max", "Trackbars", &vmax, 255);


    while (true){
        Scalar lower(hmin, smin, vmin);
        Scalar upper(hmax, smax, vmax);
        // inRange(src, lowerBoundary, upperBoundary, dst)
        // lower~upper: white, ~lower&&higher~: black
        inRange(imgHSV, lower, upper, mask);

        // imshow("image", img);
        imshow("img HSV", imgHSV);
        imshow("mask", mask);

        waitKey(1);
    }
}

void GetContours(Mat src, Mat dst){
    vector<vector<Point>> contours; // {{Point(20, 30), Point(50, 60)}, {...}, {...}}
    vector<Vec4i> hierarchy;
    // findContours(src, contours, hierachy, 抽出モード, 近似手法)
    // // RETR_EXTERNALは、輪郭のうち、最も外側の輪郭のみを抽出するモードです
    // // hierachy: contour1がcontour2囲む場合、両者は上下関係があり、この関係のことである
    findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    // // drawContours(dst, contours, whichContour[-1: all], color, thickness);
    // drawContours(dst, contours, -1, Scalar(255, 0, 255), 2);

    // Only draw the target contours
    for (int i = 0; i < contours.size(); i++){
        vector<vector<Point>> conPoly(contours.size());

        int area = contourArea(contours[i]);
        // cout << area << endl;  // area == number of points per contour
        if (area > 1000) {
            // arcLength(contour, whetherContourIsClosed) -> 周囲長の計算
            float peri = arcLength(contours[i], true);
            // approxPolyDP(contourSrc, contourDst, epsilon[], closed);
            // - epsilon: approximate the curve with an accuracy of 1% of its perimeter
            //            smaller epsilon -> higher accuracy
            approxPolyDP(contours[i], conPoly[i], 0.1*peri, true);
            drawContours(dst, conPoly, i, Scalar(255, 0, 255), 2);
        }
    }
}

int main() {

    // string path = "./resources/shapes.png";
    string path = "./resources/test/wanihakase.png";
    Mat img = imread(path);
    
    // Preprocessing
    GaussianBlur(img, imgBlur, Size(7, 7), 5, 0);
    Canny(imgBlur, imgCanny, 80, 80);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
    dilate(imgCanny, imgDil, kernel);   

    GetContours(imgDil, img);


    // imshow("image", img);
    // imshow("imageGray", imgGray);
    // imshow("imageBlur", imgBlur);
    // imshow("imageCanny", imgCanny);
    imshow("imageDil", imgDil);

    waitKey(0);
    return 0;
}