#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

#include <math.h>

using namespace cv;
using namespace std;

// Object Scanning using Image
// [Step.1]  Preprocessing 
// //   1-1  Get biggest contours
// //   1-2  Wrap using contours
// [Step.2]  Get imgWrap 
// //   2-1  Tranform into triangular contour
// //   2-2  Crop for a little bit

Mat imgOriginal, imgGray, imgCanny, imgBlur, imgDil, imgThre, imgWrap, imgCrop;
vector<Point> initialPoints, docPoints;

float w = 420, h = 596;


Mat PreProcessing(Mat img) {
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(5, 5), 5, 0);
    Canny(imgBlur, imgCanny, 25, 75);

    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
    dilate(imgCanny, imgDil, kernel); 

    return imgDil;
}

vector<Point> GetBiggestContour(Mat src){
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;

    findContours(src, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());

    vector<Point> biggestContour;
    int maxArea;

    for (int i = 0; i < contours.size(); i++){

        int area = contourArea(contours[i]);

        if (area > 1000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.01*peri, true);
            if (area > maxArea && conPoly[i].size() == 4) {
                biggestContour = {conPoly[i][0], conPoly[i][1], conPoly[i][2], conPoly[i][3]};
                maxArea = area;
            }
        }
    }

    return biggestContour;
}

void drawPoints(Mat dst, vector<Point> points, Scalar color){
    // Reorder the number of 4 points
    for (int i = 0; i < points.size(); i++){
        circle(dst, points[i], 7, color, FILLED);
        putText(dst, to_string(i), points[i], FONT_HERSHEY_PLAIN, 3, color, 3);
    }
}

vector<Point> reorder(vector<Point> points) {
    vector<Point> newPoints;
    vector<int> sumPoints, subPoints;

    for (int i = 0; i < 4; i++){
        // push_back(): pre-defined function used to insert data or elements at the end of the vector
        sumPoints.push_back(points[i].x + points[i].y);
        subPoints.push_back(points[i].x - points[i].y);
    }
    
    // maximum element: max_element(subPoints.begin(), subPoints.end())
    // maximum index:   maxElement - subPoints.begin()
    newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index.0 (tl)
    newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // index.1 (tr)
    newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // index.2 (bl)
    newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index.3 (br)

    return newPoints;
}

Mat getWrap(Mat img, vector<Point> points, float w, float h) {
    Point2f src[4] = { points[0], points[1], points[2], points[3] };
    Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h}};

    // compute transform matrix T
    Mat matrix = getPerspectiveTransform(src, dst);
    // convert src into dst using T
    warpPerspective(img, imgWrap, matrix, Point(w,h));

    return imgWrap;
}

int main(int argc, char const *argv[])
{
    string path = "./resources/paper.jpg";
    Mat imgOriginal = imread(path);
    // resize(imgOriginal, imgOriginal, Size(), 0.5, 0.5);

    // Preprocessing
    imgThre = PreProcessing(imgOriginal);
    // Get Biggest Contour && Reorder the indices of 4 points
    initialPoints = GetBiggestContour(imgThre);
    docPoints = reorder(initialPoints);
    // drawPoints(imgOriginal, docPoints, Scalar(0, 255, 0));

    // Wrap
    imgWrap = getWrap(imgOriginal, docPoints, w, h);

    // Crop
    int cropVal = 6;
    Rect roi(cropVal, cropVal, w-(2*cropVal), h-(2*cropVal));
    imgCrop = imgWrap(roi);

    imshow("image", imgOriginal);
    // imshow("image Dilation", imgThre);
    imshow("Image Wrap", imgWrap);
    imshow("Image Crop", imgCrop);
    waitKey(0);
    return 0;
}
