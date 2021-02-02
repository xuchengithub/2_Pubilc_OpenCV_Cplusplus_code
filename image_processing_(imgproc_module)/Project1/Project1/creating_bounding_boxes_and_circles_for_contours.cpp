#include <opencv2/opencv.hpp>
#include "creating_bounding_boxes_and_circles_for_contours.h"

cv::Mat SrcGray1;
int new_thresh = 100;
cv::RNG Rng2(12345);

int CreatingBoundingBoxesAndCirclesForContours(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv, "{@input | stuff.jpg | input image}");
	cv::Mat Source = cv::imread(argv[1]);
	if (Source.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	cvtColor(Source, SrcGray1, cv::COLOR_BGR2GRAY);
	blur(SrcGray1, SrcGray1, cv::Size(3, 3));
	const char* kSourceWindow = "Source";
	cv::namedWindow(kSourceWindow);
	imshow(kSourceWindow, Source);
	const int kMaxThresh = 255;
	cv::createTrackbar("Canny thresh:", kSourceWindow, &new_thresh, kMaxThresh, NewThreshCallback1);
	NewThreshCallback1(0, 0);
	cv::waitKey();
	return 0;
}
void NewThreshCallback1(int, void*)
{
	cv::Mat CannyOutput;
	Canny(SrcGray1, CannyOutput, new_thresh, new_thresh * 2);
	std::vector<std::vector<cv::Point> > Contours;
	findContours(CannyOutput, Contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<cv::Point> > ContoursPoly(Contours.size());
	std::vector<cv::Rect> BoundRect(Contours.size());
	std::vector<cv::Point2f>Centers(Contours.size());
	std::vector<float>Radius(Contours.size());
	for (size_t i = 0; i < Contours.size(); i++)
	{
		cv::approxPolyDP(Contours[i], ContoursPoly[i], 3, true);
		BoundRect[i] = cv::boundingRect(ContoursPoly[i]);
		cv::minEnclosingCircle(ContoursPoly[i], Centers[i], Radius[i]);
	}
	cv::Mat Drawing = cv::Mat::zeros(CannyOutput.size(), CV_8UC3);
	for (size_t i = 0; i < Contours.size(); i++)
	{
		cv::Scalar Color = cv::Scalar(Rng2.uniform(0, 256), Rng2.uniform(0, 256), Rng2.uniform(0, 256));
		cv::drawContours(Drawing, ContoursPoly, (int)i, Color);
		cv::rectangle(Drawing, BoundRect[i].tl(), BoundRect[i].br(), Color, 2);
		cv::circle(Drawing, Centers[i], (int)Radius[i], Color, 2);
	}
	cv::imshow("Contours", Drawing);
}
