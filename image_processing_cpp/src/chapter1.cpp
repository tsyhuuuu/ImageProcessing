#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

// <summary>
//  1. read & show image
//  2. read & show video

void ReadImage(string path){
    Mat img = imread(path);
    imshow("image", img);
    waitKey(0);
}

void ReadVideo1(string path){
    VideoCapture cap(path);

    Mat img;
    Mat imgResize;
    Mat imgCrop;

    int idx = 0;
    int count = 0;
    int freq = 3;

    while (true) {
        cap.read(img);
        resize(img, imgResize, cv::Size(), 0.5, 0.5);
        imgCrop = imgResize(Range(280, 640), Range(0, 360));

        imshow("image", imgCrop);
        // cout << imgCrop.size << endl;
        if (count % freq == 0) {
            idx = count / freq;
            imwrite("./resources/KL_imgs/my_desk" + to_string(idx) + ".png", imgCrop);
            if (idx == 10) break; 
        }

        count++;
        waitKey(1);  // 1: delay 1ms; 0: infinity
    }
}

void ReadVideo2(string path){
    // from your computer
    // VideoCapture cap(path);
    // from your webcam: 0~one_camera; 1~multicamera
    VideoCapture cap(path);

    Mat img;
    Mat imgResize;
    Mat imgCrop;

    int idx = 0;
    int count = 0;
    int freq = 1;

    while (true) {
        cap.read(img);
        resize(img, imgResize, cv::Size(), 0.8, 0.8);
        imgCrop = imgResize(Range(200, 712), Range(0, 512));
        imshow("image", imgCrop);
        // cout << imgCrop.size << endl;
        if (count % freq == 0) {
            idx = count / freq;
            imwrite("./resources/video/lab" + to_string(idx) + ".png", imgCrop);
        }

        count++;
        if (count == 798){
            break;
        }

        waitKey(1);  // 1: delay 1ms; 0: infinity
    }
}

int main() {

    string path = "./resources/KL_imgs/my_desk.mp4";  // ../ じゃなくて ./   
    ReadVideo1(path);
    return 0;
}