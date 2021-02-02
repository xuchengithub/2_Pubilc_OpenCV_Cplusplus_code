#include<opencv2/opencv.hpp>
#include "convex_hull.h"

cv::Mat SrcGrayImage;
int low_canny_thresh = 100;
cv::RNG RandomConvexColors(12345);

int ConvexHull(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv, "{@input | stuff.jpg | input image}");
	cv::Mat Source = cv::imread(argv[1]);
	if (Source.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	cv::cvtColor(Source, SrcGrayImage, cv::COLOR_BGR2GRAY);
	blur(SrcGrayImage, SrcGrayImage, cv::Size(3, 3));
	const char* kSourceWindow = "Source";
	cv::namedWindow(kSourceWindow);
	cv::imshow(kSourceWindow, Source);
	const int kMaxThresh = 255;
	cv::createTrackbar("Canny thresh:", kSourceWindow, &low_canny_thresh, kMaxThresh, NewThreshCallback);
	NewThreshCallback(0, 0);
	cv::waitKey();
	return 0;
}
void NewThreshCallback(int, void*)
{
	cv::Mat CannyOutput;
	Canny(SrcGrayImage, CannyOutput, low_canny_thresh, low_canny_thresh * 2);
	std::vector<std::vector<cv::Point> > Contours;
	findContours(CannyOutput, Contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<cv::Point> >hull(Contours.size());
	for (size_t i = 0; i < Contours.size(); i++)
	{
		convexHull(Contours[i], hull[i]);
	}
	cv::Mat Drawing = cv::Mat::zeros(CannyOutput.size(), CV_8UC3);
	for (size_t i = 0; i < Contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(RandomConvexColors.uniform(0, 256), RandomConvexColors.uniform(0, 256), RandomConvexColors.uniform(0, 256));
		drawContours(Drawing, Contours, (int)i, color);
		drawContours(Drawing, hull, (int)i, color);
	}
	cv::imshow("Hull demo", Drawing);
}

