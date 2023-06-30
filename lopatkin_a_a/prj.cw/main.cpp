#include <metrics/metrics.hpp>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

#include <iostream>
#include <string>


bool isBinary(const cv::Mat1b& img) {
    for (int i = 0; i < img.rows; i += 1) {
        for (int j = 0; j < img.cols; j += 1) {
            if (0 < img.at<uchar>(i, j) && img.at<uchar>(i, j) < 255) {
                return false;
            }
        }
    }
    return true;
}


int main(int argc, char* argv[]) {
    int m = 5;
    int n = 8;
    if (argc == 5) {
        try {
            m = std::stoi(argv[3]);
            n = std::stoi(argv[4]);
        } catch (std::invalid_argument const& e) {
            std::cout << "Bad input of integer arguments\n";
            return -1;
        }
    } else {
        std::cout << "Usage: " << argv[0] << " <Ground truth image> " << "<Binarized image> " << "<m(Recommended: 5)> " << "<n(Recommended: 8)>\n";
        return -1;
    }
    cv::Mat1b img_GT;
    cv::Mat1b img_bin;
    img_GT = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
    img_bin = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
    
    if (img_GT.empty()) {
        std::cout << "Can't open Ground truth image\n";
        return -1;
    }
    if (img_bin.empty()) {
        std::cout << "Can't open binarized image\n";
        return -1;
    }
    if (img_bin.channels() != 1 && img_GT.channels() != 1) {
        std::cout << "Images must be 1 channel\n";
        return -1;
    }
    if (!isBinary(img_bin) || !isBinary(img_GT)) {
        std::cout << "Image must be binary\n";
        return -1;
    }
    if (img_bin.size() != img_GT.size()) {
        std::cout << "Different image sizes\n";
        return -1;
    }

    std::cout << "F-Measure: " << FMeasure(img_GT, img_bin) \
        << "\nPSNR: " << PSNR(img_GT, img_bin) \
        << "\nDRD: " << DRD(img_GT, img_bin, m, n) \
        << "\nMPM(x10^(-3)): " << MPM(img_GT, img_bin) * 1000;
}