#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>

using namespace cv;
using namespace std;

// face detection using webcam

int main(int argc, char const *argv[])
{
    
    VideoCapture cap(0);
    Mat img;

    CascadeClassifier faceCascade;
    // plateCascade.load("./resources/haarcascade_russian_plate_number.xml");
    faceCascade.load("./resources/haarcascade_frontalface_default.xml");

    if (faceCascade.empty()) { cout << "XML file not loaded" << endl; }

    vector<Rect> faces;

    while (true){
        cap.read(img);
        faceCascade.detectMultiScale(img, faces, 1.1, 10);

        for (int i = 0; i < faces.size(); i++) {
            Mat imgCrop = img(faces[i]);
            imshow(to_string(i), imgCrop);
            // imwrite("./resources/Plates/" + to_string(i) + ".png", imgCrop);
            rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 0, 255), 3);
        }

        imshow("Image", img);
        waitKey(10);
    }
    
    return 0;
}
