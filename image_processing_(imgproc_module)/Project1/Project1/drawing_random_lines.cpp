#include <opencv2/opencv.hpp>
#include "drawing_random_lines.h"

int DrawingRandom(void){
	cv::RNG MaxRng(0xFFFFFFFF);
	int window_height = 1080;
	int window_width = 1920;
	const char *kWindowName = "Random_Line";
	cv::Mat image = cv::Mat::zeros(window_height, window_width, CV_8UC3);
	cv::imshow(kWindowName, image);
	int c = DrawingRandomLines(image, kWindowName, MaxRng);
	if (c != 0) return 0;
	c = DisplayingRandomText(image, kWindowName, MaxRng);
	if (c != 0) return 0;
	c = DisplayingBigEnd(image, kWindowName, MaxRng);
	if (c != 0) return 0;
}
int DrawingRandomLines(cv::Mat image, const char* window_name, cv::RNG MaxRng)
{
	int line_number = 90;
	int line_type = 8;
	cv::Point ApexPoint1, ApexPoint2;

	int x_1 = 0;
	int x_2 = 1919;
	int y_1 = 0;
	int y_2 = 1079;

	for (int i = 0; i < line_number; i++)
	{
		ApexPoint1.x = MaxRng.uniform(x_1, x_2);//ランダムに、x1、X2の間の値を取って、Xの値にする。
		ApexPoint1.y = MaxRng.uniform(y_1, y_2);
		ApexPoint2.x = MaxRng.uniform(x_1, x_2);
		ApexPoint2.y = MaxRng.uniform(y_1, y_2);
		line(image, ApexPoint1, ApexPoint2, RandomColor(MaxRng), MaxRng.uniform(1, 10), 8);
		imshow(window_name, image);
		if (cv::waitKey(30) >= 0)
		{
			return -1;
		}
	}
	return 0;
}
static cv::Scalar RandomColor(cv::RNG& MaxRng)
{
	int icolor_ = (unsigned)MaxRng;
	return cv::Scalar(icolor_ & 255, (icolor_ >> 8) & 255, (icolor_ >> 16) & 255);
}
int DisplayingRandomText(cv::Mat image, const char* window_name, cv::RNG MaxRng)
{
	int line_type = 8;
	int text_number = 9;

	int x_1 = 0;
	int x_2 = 1079;
	int y_1 = 0;
	int y_2 = 1919;

	for (int i = 1; i < text_number; i++)
	{
		cv::Point Org;
		Org.x = MaxRng.uniform(x_1, x_2);
		Org.y = MaxRng.uniform(y_1, y_2);
		cv::putText(image, "Testing text rendering", Org, MaxRng.uniform(0, 8),
			MaxRng.uniform(0, 100)*0.05 + 0.1, RandomColor(MaxRng), MaxRng.uniform(1, 10), line_type);
		cv::imshow(window_name, image);
		if (cv::waitKey(32) >= 0)
		{
			return -1;
		}
	}
	return 0;
}
int DisplayingBigEnd(cv::Mat image, const char* window_name, cv::RNG MaxRng)
{
	int window_height = 1080;
	int window_width = 1920;

	cv::Size TextSize = cv::getTextSize("MAKER BY XUCHEN!", cv::FONT_HERSHEY_COMPLEX, 3, 5, 0);
	cv::Point Org((window_width - TextSize.width) / 2, (window_height - TextSize.height) / 2);
	int line_type = 8;
	cv::Mat DisplayImage;
	for (int i = 0; i < 255; i += 2)
	{
		DisplayImage = image - cv::Scalar::all(i);
		cv::putText(DisplayImage, "MAKER BY XUCHEN!", Org, cv::FONT_HERSHEY_COMPLEX, 3,
			cv::Scalar(i, i, 255), 5, line_type);
		cv::imshow(window_name, DisplayImage);
		if (cv::waitKey(32) >= 0)
		{
			return -1;
		}
	}
	return 0;
}