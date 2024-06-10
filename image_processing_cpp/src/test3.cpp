// orb

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char const *argv[])
{
    // if (argc != 3){
    //     cout << "usage: feature extraction img1 img2" << endl;
    //     return 1;
    // }


    // 1. read the images
    Mat img1 = imread("./resources/orb_imgs/mono1bit1.png");
    Mat img2 = imread("./resources/orb_imgs/mono2bit1.png");
    Mat img3 = imread("./resources/orb_imgs/mono3bit1.png");
    Mat img4 = imread("./resources/orb_imgs/mono4bit1.png");
    Mat img5 = imread("./resources/orb_imgs/mono5bit1.png");
    Mat img6 = imread("./resources/orb_imgs/mono6bit1.png");
    Mat img7 = imread("./resources/orb_imgs/mono7bit1.png");
    Mat img8 = imread("./resources/orb_imgs/mono8bit1.png");

    // 2. initialize
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    // Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming"); 
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    // 3. detect Oriented FAST
    detector->detect(img1, keypoints1);
    detector->detect(img2, keypoints2);
    detector->detect(img3, keypoints1);
    detector->detect(img4, keypoints2);
    detector->detect(img5, keypoints1);
    detector->detect(img6, keypoints2);
    detector->detect(img7, keypoints1);
    detector->detect(img8, keypoints2);

    // 4. compute BRIEF
    descriptor->compute(img1, keypoints1, descriptors1);
    descriptor->compute(img2, keypoints2, descriptors2);

    Mat outimg1;
    drawKeypoints(img1, keypoints1, outimg1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    imshow("ORB keypoints", outimg1);
    waitKey(0);

    // 5. matching keypoints
    vector<DMatch> matches;
    matcher->match(descriptors1, descriptors2, matches); // NORMAL_HAMMING

    // 6. filtering matching keypoints 
    double min_dist = 10000, max_dist = 0;

    for (int i = 0; i < descriptors1.rows; i++){
        double dist = matches[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    std::vector<DMatch> good_matches;
    for (int i = 0; i < descriptors1.rows; i++) {

        if (matches[i].distance <= max(2*min_dist, 30.0)){
            good_matches.push_back(matches[i]);   // equal to list.append(ele) in python
        }
    }

    // 7. show the result
    Mat img_match, img_goodmatch;
    drawMatches(img1, keypoints1, img2, keypoints2, matches, img_match);
    drawMatches(img1, keypoints1, img2, keypoints2, good_matches, img_goodmatch);

    imshow("img_match", img_match);
    imshow("img goodmatch", img_goodmatch);
    waitKey(0);

    return 0;
}
