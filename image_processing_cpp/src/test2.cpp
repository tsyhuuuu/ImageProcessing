#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap(0); // 1 will raise the error due to the mac error
    Mat img;

    while(true){
        cap.read(img);
        imshow("Image", img);
        waitKey(1);
    }

    return 0;
}