#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

int main() {
    cv::Mat img(400, 600, CV_8UC3);
    img = cv::Vec3b{ 125, 200, 255 };
    cv::imshow("BGR-image", img);
    cv::imwrite("create-n-show.png", img);
    cv::waitKey(0);
}