#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// <summary> Basics
//  1. convert images
//  2. resize images

void CvtImage(string path){
    Mat img = imread(path);
    Mat imgGray, imgBlur, imgCanny, imgDil, imgErode;

    cvtColor(img, imgGray, COLOR_BGR2GRAY); // [Python version] imgGray = cvtColor(img, COLOR_BGR2GRAY)
    GaussianBlur(imgGray, imgBlur, Size(7, 7), 5, 0);
    Canny(imgBlur, imgCanny, 80, 80);       // Canny edge detection (Canny is person's name) 
                                            // 隣接の画素値の差が閾値(threshold1, threshold2)を超えたら edge とみなす

    Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
    dilate(imgCanny, imgDil, kernel);       // increase the width of edges
    erode(imgDil, imgErode, kernel);        // decrease the erosion area (achieve the effect of filling the blank area)

    // imshow("image", img);
    // imshow("imageGray", imgGray);
    // imshow("imageBlur", imgBlur);
    imshow("imageCanny", imgCanny);
    imshow("imageDilation", imgDil);
    imshow("imageErode", imgErode);

    waitKey(0);
}

void ResizeImg(string path){
    Mat img = imread(path);
    Mat imgResize, imgCrop;

    cout << img.size() << endl;
    // resize(img, imgResize, Size(640, 480));   // exact pixels
    resize(img, imgResize, Size(), 0.25, 0.25);  // relative size (0.5x0.5 means the same size of your using image)
    
    Rect roi(250, 50, 1160, 1200);    // cropping area
    imgCrop = img(roi);

    imshow("image", img);
    imshow("image Resize", imgResize); 
    imshow("image Crop", imgCrop); 
    waitKey(0);
}


int main() {
    string path = "./resources/limo.jpg";
    ResizeImg(path);

    return 0;
}