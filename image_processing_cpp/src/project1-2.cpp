#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include <math.h>

using namespace cv;
using namespace std;

// Object Detection using VideoCapture
// [Step.1]  Color Detection
// [Step.2]  Find Contours
// [Step.3]  Draw Triangular/Circle around Objects
// *[Step.4] Create Virtual Painter


vector<vector<int>> myColors { {20,70,100,50,180,200} };  // green

vector<vector<int>> newPoints;

Mat img, mask;

VideoCapture cap(0);

// Step.2・3
Point GetContours(Mat src, Mat dst){
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    Point myPoint(0, 0);

    for (int i = 0; i < contours.size(); i++){

        int area = contourArea(contours[i]);

        if (area > 1000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.01*peri, true);

            boundRect[i] = boundingRect(conPoly[i]);
            myPoint.x = boundRect[i].x + boundRect[i].width/2;
            myPoint.y = boundRect[i].y + boundRect[i].height/2;
            int myRadius = sqrt(boundRect[i].width*boundRect[i].width + boundRect[i].height*boundRect[i].height) / 2;
            // drawContours(dst, conPoly, i, Scalar(0, 0, 255), 2);
            // rectangle(dst, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 3);
            circle(dst, (Point(myPoint.x, myPoint.y)), myRadius, Scalar(0, 255, 0), 3);
        }
    }

    return myPoint;
}

// Step.4
vector<vector<int>> findColor(Mat img) {
    Mat imgHSV;
    cvtColor(img, imgHSV, COLOR_BGR2HSV);

    for (int i = 0; i < myColors.size(); i++){
        Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
        Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
        inRange(imgHSV, lower, upper, mask);

        // imshow(to_string(i), mask);

        Point myPoint = GetContours(mask, img);
        if(myPoint.x != 0 && myPoint.y != 0) { 
            newPoints.push_back({ myPoint.x, myPoint.y, i});
        }
    }

    return newPoints;
}


// Step.3
void drawOnCanvas(vector<vector<int>> newPoints){
    for (int i = 0; i < newPoints.size(); i++) {
        circle(img, Point(newPoints[i][0], newPoints[i][1]), 3, Scalar(255, 100, 100), FILLED);
    }
}


int main(int argc, char const *argv[])
{
    while (true) {
        cap.read(img);
        newPoints = findColor(img);
        // drawOnCanvas(newPoints);
        imshow("Camera", img);
        waitKey(10);
    }

    return 0;
}
