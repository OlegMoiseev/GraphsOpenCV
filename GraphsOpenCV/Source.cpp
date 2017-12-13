#include <opencv2/opencv.hpp>
#include "ImuModule.h"
#include <chrono>
#include <thread>
#include <mutex>


int main()
{
	PololuImuV5 imu;
	Quaternion a;
	double tmpRoll = 0, tmpPitch = 0;

	cv::Mat m1 = cv::Mat::zeros(2, 2, cv::DataType<double>::type);
	cv::Mat tmp = cv::Mat(1, 2, cv::DataType<double>::type);

	tmp.at<double>(0, 0) = 100;
	tmp.at<double>(0, 1) = 1;

	const cv::Point center(75, 75);
	double yaw = 0.;
	std::mutex mutex;
	std::thread imuThread(PololuImuV5::readOutImu, &imu, std::ref(a));
	imuThread.detach();

	while (true)
	{
		std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
		cv::Mat background = cv::Mat::zeros(150, 150, cv::DataType<double>::type);
		cv::circle(background, center, 50, 128);
		mutex.lock();
		quaternionToEulerianAngle(a, tmpRoll, tmpPitch, yaw);
		mutex.unlock();
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count() << std::endl;

		start = std::chrono::system_clock::now();
		m1.at<double>(0, 0) = cos(yaw);
		m1.at<double>(0, 1) = -sin(yaw);
		m1.at<double>(1, 0) = sin(yaw);
		m1.at<double>(1, 1) = cos(yaw);
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count() << std::endl;

		start = std::chrono::system_clock::now();
		cv::Mat t = tmp * m1;
		cv::arrowedLine(background, center - cv::Point(t.at<double>(0, 0) / 2, t.at<double>(0, 1) / 2),
		                center + cv::Point(t.at<double>(0, 0) / 2, t.at<double>(0, 1) / 2), 255);
		cv::imshow("", background);
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - start).count() << std::endl << "_____" << std::endl;

		cv::waitKey(10);
	}
	cv::waitKey();
	return 0;
}
