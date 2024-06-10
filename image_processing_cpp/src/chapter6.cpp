#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
// ------------ new ------------
#include <opencv2/objdetect.hpp>
// ------------ new ------------
#include <iostream>

using namespace cv;
using namespace std;

// 

int main(int argc, char const *argv[])
{
    string path = "./resources/face.jpg";
    Mat img = imread(path);

    CascadeClassifier faceCascade;
    //　load config file related to target object 
    faceCascade.load("./resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }

    vector<Rect> faces;

    faceCascade.detectMultiScale(img, faces, 1.1, 10);

    // Display faces saved in previous variable(faces)
    // faces[i].tl(): top-left of face i; faces[i].br(): bottom-right of face i; 
    for (int i = 0; i < faces.size(); i++) {
        rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
    }

    imshow("Image", img);
    waitKey(0);
    return 0;
}
