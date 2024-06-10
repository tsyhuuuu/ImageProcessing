#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

using namespace std;
using namespace cv;


int main(int argc, char const *argv[])
{
    // Blank Image (height, width, type, color_BGR)
    // CV_8S:   type of image(8bits per pixel)
    // CV_8UC3: type of image(8bits per pixel with 3 channels)
    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255)); 

    // circle(img, center, radius, color(, widthOfEdge, FILLED))
    circle(img, Point(256, 256), 155, Scalar(0, 69, 255), FILLED);
    // Rectangle(img, point1, point2, color(, widthOfEdge, FILLED))
    rectangle(img, Point(382, 286), Point(130, 226), Scalar(255, 255, 255), 3, FILLED);
    // line(img, point1, point2, color, widthOfEdgge)
    line(img, Point(130, 296), Point(382, 296), Scalar(255, 255, 255), 2);
    // putText(img, name, startPoint, fontStyle, fontSize, color)
    putText(img, "tsy's Workshop", Point(137, 262), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255));


    imshow("Customized Image", img);
    waitKey(0);
    return 0;
}

