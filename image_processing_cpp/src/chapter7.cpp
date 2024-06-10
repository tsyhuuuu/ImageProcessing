// orb

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

Mat show_img_with_orb(string path) {
   
    Mat img = imread(path);

    std::vector<KeyPoint> keypoints;
    Mat descriptors;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    detector->detect(img, keypoints);

    // Mat outimg;
    const float r = 4.5f;
    const int n = keypoints.size();
    for (int i=0; i<n; i++){
        if (i % 5 > 2) {
            cv::Point2f pt1,pt2;
            pt1.x=keypoints[i].pt.x-r;
            pt1.y=keypoints[i].pt.y-r;
            pt2.x=keypoints[i].pt.x+r;
            pt2.y=keypoints[i].pt.y+r;

            rectangle(img, pt1, pt2, cv::Scalar(0,255,0));
            circle(img, keypoints[i].pt, 2, cv::Scalar(0,255,0), -1);
        }
    }
    // drawKeypoints(img, keypoints, outimg, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
    // imshow("ORB keypoints", outimg);
    imshow("ORB keypoints", img);
    waitKey(0);

    // // return outimg;
    return img;
}

Mat show_orb_matching(string path1, string path2) {

    // 1. read the images
    Mat img1 = imread(path1);
    Mat img2 = imread(path2);

     // 2. initialize
    std::vector<KeyPoint> keypoints1, keypoints2;
    Mat descriptors1, descriptors2;
    Ptr<FeatureDetector> detector = ORB::create();
    Ptr<DescriptorExtractor> descriptor = ORB::create();
    Ptr<DescriptorMatcher> matcher = DescriptorMatcher::create("BruteForce-Hamming");

    // 3. detect Oriented FAST
    detector->detect(img1, keypoints1);
    detector->detect(img2, keypoints2);

    // 4. compute BRIEF
    descriptor->compute(img1, keypoints1, descriptors1);
    descriptor->compute(img2, keypoints2, descriptors2);

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

    return img_goodmatch;
}



int main(int argc, char const *argv[]) {
    // if (argc != 3){
    //     cout << "usage: feature extraction img1 img2" << endl;
    //     return 1;
    // }

    string RAW_PATHS[4] = {
        {"./resources/orb_imgs/halftone/8bit.png"},
        {"./resources/orb_imgs/halftone/linear.png"},
        {"./resources/orb_imgs/halftone/blockwise.png"},
        {"./resources/orb_imgs/halftone/errdiff_fs.png"}
    };


    string GOAL_PATHS[4] = {
        {"./resources/orb_imgs/halftone_orb/8bit.png"},
        {"./resources/orb_imgs/halftone_orb/linear.png"},
        {"./resources/orb_imgs/halftone_orb/blockwise.png"},
        {"./resources/orb_imgs/halftone_orb/errdiff_fs.png"}
    };

    for (int i = 0; i < 4; i++) {
        Mat img = show_img_with_orb(RAW_PATHS[i]);
        imwrite(GOAL_PATHS[i], img);
    }

    // Mat img = show_orb_matching(RAW_PATHS[0][1], RAW_PATHS[0][1]);
    // imwrite("./resources/orb_imgs/simple_quantization_orb/mono1bit1_8bit1.png", img);
}
