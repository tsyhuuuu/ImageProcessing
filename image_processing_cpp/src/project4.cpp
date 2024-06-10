#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

#include <iostream>

class ImageQuantization {
public:
    ImageQuantization() {}

    cv::Mat linear_quantization(cv::Mat img, int N) {
        return linear_quantization(img, N);
    }
    
    // cv::Mat blockwise_quantization(cv::Mat img, int N) {
    //     return blockwise_quantization(img, N);
    // }

    // cv::Mat error_diffusion_quantization(cv::Mat img, int N, cv::Mat h = cv::Mat(), std::string method = "jjn") {
    //     if (method == "visual model") {
    //         return halftone_visual_model(img, N);
    //     } else {
    //         return error_diffusion_quantization(img, h, method, N);
    //     }
    // }

private:
    cv::Mat linear_quantization(cv::Mat img, int N) {
        int level = pow(2, N);
        double d = 255.0 / (level - 1);
        cv::Mat quantized_img = std::round(img / d) * d;
        
        return quantized_img;
    }
    
    // cv::Mat blockwise_quantization(cv::Mat img, int N) {
    //     int height = img.rows;
    //     int width = img.cols;
    //     cv::Mat quantized_img = img.clone();

    //     for (int i = 0; i < height; i += N) {
    //         for (int j = 0; j < width; j += N) {
    //             int i_end = std::min(i + N, height);
    //             int j_end = std::min(j + N, width);

    //             cv::Mat block = img(cv::Range(i, i_end), cv::Range(j, j_end));
    //             double max_value, min_value;
    //             cv::minMaxLoc(block, &min_value, &max_value);
    //             double thresh = (max_value + min_value) / 2;

    //             for (int x = 0; x < N; x++) {
    //                 for (int y = 0; y < N; y++) {
    //                     if (block.at<uchar>(x, y) >= thresh) {
    //                         quantized_img.at<uchar>(i + x, j + y) = thresh;
    //                     } else {
    //                         quantized_img.at<uchar>(i + x, j + y) = min_value;
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     return quantized_img;
    // }

    // cv::Mat error_diffusion_quantization(cv::Mat img, cv::Mat h, std::string method, int N) {
    //     int FSTEPJ = 0, BSTEPJ = 0, FSTEPI = 0;

    //     if (method == "jjn") {
    //         h = (cv::Mat_<double>(3, 5) << 0, 0, 0, 7, 5,
    //                                        3, 5, 7, 5, 3,
    //                                        1, 3, 5, 3, 1) / 48;
    //         FSTEPJ = 2;
    //         BSTEPJ = -2;
    //         FSTEPI = 2;
    //     } else if (method == "fs") {
    //         h = (cv::Mat_<double>(2, 3) << 0, 0, 7,
    //                                        3, 5, 1) / 16;
    //         FSTEPJ = 1;
    //         BSTEPJ = -1;
    //         FSTEPI = 1;
    //     } else if (method == "custom") {
    //         if (h.rows * h.cols == 6) {
    //             FSTEPJ = 1;
    //             BSTEPJ = -1;
    //             FSTEPI = 1;
    //         } else if (h.rows * h.cols == 15) {
    //             FSTEPJ = 2;
    //             BSTEPJ = -2;
    //             FSTEPI = 2;
    //         }
    //     }

    //     int level = pow(2, N);
    //     double d = 255.0 / (level - 1);

    //     cv::Mat tmp1, tmp2, tmp;
    //     cv::copyMakeBorder(img, tmp1, 0, 0, -BSTEPJ, FSTEPJ, cv::BORDER_CONSTANT, 0);
    //     cv::copyMakeBorder(cv::Mat::ones(FSTEPI, img.cols, CV_64F), tmp2, FSTEPI, 0, -BSTEPJ, FSTEPJ, cv::BORDER_CONSTANT, 0);
    //     cv::vconcat(tmp1, tmp2, tmp);

    //     cv::Mat newImage = cv::Mat::zeros(img.rows + FSTEPI, img.cols + FSTEPJ - BSTEPJ, CV_64F);

    //     for (int i = 0; i < img.rows; i++) {
    //         for (int j = 0; j < img.cols + FSTEPJ; j++) {
    //             if (i >= img.rows || j >= img.cols - BSTEPJ || j <= -BSTEPJ) {
    //                 newImage.at<double>(i, j) = cv::round(newImage.at<double>(i, j) / d) * d;
    //             } else {
    //                 double tmp_ceil = cv::ceil(tmp.at<double>(i, j) / d) * d;
    //                 double tmp_floor = cv::floor(tmp.at<double>(i, j) / d) * d;

    //                 double err1 = tmp.at<double>(i, j) - tmp_floor;
    //                 double err2 = tmp.at<double>(i, j) - tmp_ceil;

    //                 double err3, newValue;
    //                 if (err1 * err1 < err2 * err2) {
    //                     newValue = tmp_floor;
    //                     err3 = err1;
    //                 } else {
    //                     newValue = tmp_ceil;
    //                     err3 = err2;
    //                 }

    //                 for (int k = 1; k < FSTEPI + 2; k++) {
    //                     for (int l = BSTEPJ; l <= FSTEPJ; l++) {
    //                         tmp.at<double>(i + k - 1, j + l) += err3 * h.at<double>(k - 1, -1 * BSTEPJ + l);
    //                     }
    //                 }
    //                 newImage.at<double>(i, j) = newValue;
    //             }
    //         }
    //     }

    //     return newImage(cv::Rect(FSTEPJ, 0, img.cols, img.rows));
    // }
};

int main() {
    // Initialize ImageQuantization object
    ImageQuantization image_quantization;

    // Load an image using OpenCV
    cv::Mat img = cv::imread("./resources/quantization/original/lab8bit.png");

    // Example usage of linear quantization
    int N = 1;
    cv::Mat quantized_img = image_quantization.linear_quantization(img, N);

    // Display the original and quantized images
    cv::imshow("Original Image", img);
    cv::imshow("Quantized Image", quantized_img);
    cv::waitKey(0);

    return 0;
}
