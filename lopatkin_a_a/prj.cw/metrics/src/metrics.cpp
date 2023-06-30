#include <metrics/metrics.hpp>

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include <cmath>

double NUBN(const cv::Mat1b& img, int m = 8) {
    int nubn = 0;
    for (int i = m; i < img.rows; i += m) {
        for (int j = m; j < img.cols; j += m) {
            cv::Mat1b block = img(cv::Range(i - m, i), cv::Range(j - m, j));
            int n_black_pixels = cv::countNonZero(block);
            if (0 < n_black_pixels && n_black_pixels < m * m) {
                nubn += 1;
            }
        }
    }
    return nubn;
}


cv::Mat1d normalizedWeightMatrix(int m = 5) {
    cv::Mat1d weight_matrix = cv::Mat1d::zeros(m, m);
    int i_c = m / 2;
    int j_c = m / 2;
    double weights_sum = 0;
    for (int i = 0; i < m; i += 1) {
        for (int j = 0; j < m; j += 1) {
            if (i != i_c && j != j_c) {
                double weight = 1 / sqrt((i - i_c) * (i - i_c) + (j - j_c) * (j - j_c));
                weights_sum += weight;
                weight_matrix.at<double>(i, j) = weight;
            }
        }
    }
    weight_matrix = weight_matrix / weights_sum;
    return weight_matrix;
}


double DRD(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin, int m, int n) {
    double DRD = 0;
    int h = img_GT.rows;
    int w = img_GT.cols;
    cv::Mat1d weight_matrix = normalizedWeightMatrix(m);
    for (int i = 0; i < h; i += 1) {
        for (int j = 0; j < w; j += 1) {
            if (img_bin.at<uchar>(i, j) != img_GT.at<uchar>(i, j)) {
                double drd_k = 0;
                for (int y = -m / 2; y < m / 2 + 1; y += 1) {
                    for (int x = -m / 2; x < m / 2 + 1; x += 1) {
                        int d = 0;
                        if (i + y >= 0 && i + y < h && j + x >= 0 && j + x < w) 
                            d = std::abs(img_GT.at<uchar>(i + y, j + x) - img_bin.at<uchar>(i, j)) / 255;
                        drd_k += d * weight_matrix.at<double>(y + m / 2, x + m / 2);
                    }
                }
                DRD += drd_k;
            }
        }
    }
    DRD /= NUBN(img_GT, n);
    return DRD;
}


double MPM(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin) {
    double mpm = 0;

    cv::Mat1b tmp;
    cv::threshold(img_GT, tmp, 128, 255, cv::THRESH_BINARY_INV);

    std::vector<std::vector<cv::Point> > contours;
    cv::findContours(tmp, contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);

    cv::Mat1b contour_img = cv::Mat1b::ones(img_GT.size());
    for (size_t idx = 0; idx < contours.size(); idx++) {
        cv::drawContours(contour_img, contours, idx, 0);
    }

    cv::Mat dist;
    distanceTransform(contour_img, dist, cv::DIST_C, CV_32F);
    double D = cv::sum(dist)[0];
    double MP_FN = 0;
    double MP_FP = 0;
    for (int i = 0; i < dist.rows; i += 1) {
        for (int j = 0; j < dist.cols; j += 1) {
            if (img_GT.at<uchar>(i, j) == 0 && img_bin.at<uchar>(i, j) != 0) {
                MP_FN += dist.at<float>(i, j);
            }
            if (img_GT.at<uchar>(i, j) != 0 && img_bin.at<uchar>(i, j) == 0) {
                MP_FP += dist.at<float>(i, j);
            }
        }
    }
    mpm = (MP_FN + MP_FP) / (2 * D);
    return mpm;
}


double FMeasure(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin) {
    cv::Mat1b errors_matrix;
    cv::absdiff(img_bin, img_GT, errors_matrix);
    double n_errors = cv::countNonZero(errors_matrix);
    double n_hits = img_bin.total() - n_errors;

    cv::Mat1b TN_matrix = img_bin.mul(img_GT);
    double TN = cv::countNonZero(TN_matrix);
    double TP = n_hits - TN;

    cv::Mat1b FP_matrix;
    cv::absdiff(TN_matrix, img_GT, FP_matrix);
    double FP = cv::countNonZero(FP_matrix);
    double FN = n_errors - FP;

    double precision = 100 * TP / (TP + FP);
    double recall = 100 * TP / (TP + FN);
    double f_measure = 2 * precision * recall / (precision + recall);

    return f_measure;
}


double PSNR(const cv::Mat1b& img_GT, const cv::Mat1b& img_bin) {
    cv::Mat1b errors_matrix;
    cv::absdiff(img_bin, img_GT, errors_matrix);
    double n_errors = cv::countNonZero(errors_matrix);
    double mse = n_errors / img_bin.total();
    double psnr = 10.0 * log10(1.0 / mse);
    return psnr;
}
