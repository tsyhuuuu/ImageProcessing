#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//　Wrap image

float w = 250, h = 350; // ratio
Mat matrix, imgWrap;

void ImgWrap(string path){
    Mat img = imread(path);

    // Point2f: image with 2 float numbers
    // Define source and destination image size
    Point2f src[4] = { {529,142}, {771,190}, {405,395}, {674,457} }; // pixel value for cards.jpg
    Point2f dst[4] = { {0.0f,0.0f}, {w,0.0f}, {0.0f,h}, {w,h}};

    // compute transform matrix T
    matrix = getPerspectiveTransform(src, dst);
    // convert src into dst using T
    warpPerspective(img, imgWrap, matrix, Point(w,h));

    // add red cricle to check the coordinates
    for (int i = 0; i < 4; i++){
        circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
    }

    imshow("CARDS", img);
    imshow("CARDWRAP", imgWrap);

    waitKey(0);
}

int main(){

    string path = "./resources/test/cards.jpg";
    
    ImgWrap(path);

    return 0;
}