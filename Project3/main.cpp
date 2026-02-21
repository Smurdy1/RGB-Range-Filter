#include <opencv2/opencv.hpp>
#include <iostream>

int r_min = 0, r_max = 255;
int g_min = 0, g_max = 255;
int b_min = 0, b_max = 255;

cv::Mat image, mask;

void updateMask(int, void*)
{
    mask = cv::Mat::zeros(image.size(), image.type());
    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            cv::Vec3b pixel = image.at<cv::Vec3b>(y, x);
            int b = pixel[0], g = pixel[1], r = pixel[2];
            if (r < r_min || r > r_max ||
                g < g_min || g > g_max ||
                b < b_min || b > b_max)
            {
                mask.at<cv::Vec3b>(y, x) = cv::Vec3b(255, 255, 255);
            }
            else
            {
                mask.at<cv::Vec3b>(y, x) = pixel;
			}
        }
    }
    cv::imshow("Display Window", mask);
}


int main() {

    image = cv::imread("C:\\Users\\blais\\Downloads\\box.png");
    if (image.empty())
    {
        std::cerr << "Error: Could not load image." << std::endl;
        return -1;
    }

    mask = image.clone();

    cv::namedWindow("Display Window", cv::WINDOW_AUTOSIZE);

    cv::createTrackbar("R_MIN", "Display Window", &r_min, 255, updateMask);
    cv::createTrackbar("R_MAX", "Display Window", &r_max, 255, updateMask);
    cv::createTrackbar("G_MIN", "Display Window", &g_min, 255, updateMask);
    cv::createTrackbar("G_MAX", "Display Window", &g_max, 255, updateMask);
    cv::createTrackbar("B_MIN", "Display Window", &b_min, 255, updateMask);
    cv::createTrackbar("B_MAX", "Display Window", &b_max, 255, updateMask);

    updateMask(0, 0);

    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}