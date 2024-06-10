#include <iostream>

#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {

    cv::Mat imgBlur, imgGray;
    cv::Mat img = cv::imread("/Users/tsy/Documents/vscode/cppFolder/opencvFolder/resources/test/mylab.jpg");
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(9,9), 5, 0);
    // cv::namedWindow("test", cv::WINDOW_AUTOSIZE);
    cv::imwrite("/Users/tsy/Documents/vscode/cppFolder/opencvFolder/resources/test/mylab_blur.jpg", imgBlur);
    // cv::waitKey(0);
    return 0;
}
