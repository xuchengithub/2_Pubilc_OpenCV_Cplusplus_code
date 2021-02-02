#include <opencv2/opencv.hpp>
#include "finding_contours_in_your_image.h"

cv::Mat SrcGray23;
int thresh = 100;
cv::RNG RandomContoursColors(12345);
void ThreshCallback(int, void*);

int FindingContoursInYourImage(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv, "{@input | HappyFish.jpg | input image}");
	cv::Mat Source = cv::imread(argv[1]);
	if (Source.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	cvtColor(Source, SrcGray23, cv::COLOR_BGR2GRAY);
	blur(SrcGray23, SrcGray23, cv::Size(3, 3));
	const char* kSourceWindow = "Source";
	cv::namedWindow(kSourceWindow);
	imshow(kSourceWindow, Source);
	const int kMaxThresh = 255;
	cv::createTrackbar("Canny thresh:", kSourceWindow, &thresh, kMaxThresh, ThreshCallback);
	ThreshCallback(0, 0);
	cv::waitKey();
	return 0;
}
void ThreshCallback(int, void*)
{
	cv::Mat kCannyOutput;
	Canny(SrcGray23, kCannyOutput, thresh, thresh * 2);
	std::vector<std::vector<cv::Point> > Contours;
	std::vector<cv::Vec4i> Hierarchy;
	findContours(kCannyOutput, Contours, Hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	cv::Mat Drawing = cv::Mat::zeros(kCannyOutput.size(), CV_8UC3);
	for (size_t i = 0; i < Contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(RandomContoursColors.uniform(0, 256), RandomContoursColors.uniform(0, 256), RandomContoursColors.uniform(0, 256));
		drawContours(Drawing, Contours, (int)i, color, 2, cv::LINE_8, Hierarchy, 0);
	}
	cv::imshow("Contours", Drawing);
}