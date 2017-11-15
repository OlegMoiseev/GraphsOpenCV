#include <opencv2/opencv.hpp>
#include <iostream>

#pragma comment (lib, "opencv_world331d.lib")

int main()
{
	cv::Mat m1 = cv::Mat(3, 1, CV_8UC1);
	cv::Mat m2 = cv::Mat(1, 3, CV_8UC1);

	for (int i = 0; i < 3; ++i)
	{
		m1.at<uchar>(i, 0) = 255;
		m2.at<uchar>(0, i) = 1;
	}
	std::cout << m1 << std::endl << m2 << std::endl;

	cv::Mat tmp = cv::Mat(3, 3, CV_8UC1);
	tmp = m1 * m2;
	std::cout << tmp << std::endl;


	system("pause");
	return 0;
}
