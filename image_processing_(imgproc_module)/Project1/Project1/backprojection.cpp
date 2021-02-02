#include <opencv2/opencv.hpp>
#include "backprojection.h"

cv::Mat hue;
int bins = 25;

void HistAndBackproj(int, void*)
{
	int histSize = MAX(bins, 2);
	float hue_range[] = { 0, 180 };
	const float* kRanges = { hue_range };
	cv::Mat Hist;
	calcHist(&hue, 1, 0, cv::Mat(), Hist, 1, &histSize, &kRanges, true, false);
	cv::normalize(Hist, Hist, 0, 255, cv::NORM_MINMAX, -1, cv::Mat());
	cv::Mat BackProj;
	calcBackProject(&hue, 1, 0, Hist, BackProj, &kRanges, 1, true);
	cv::imshow("BackProj", BackProj);
	int w = 400, h = 400;
	int bin_w = cvRound((double)w / histSize);
	cv::Mat HistImg = cv::Mat::zeros(h, w, CV_8UC3);
	for (int i = 0; i < bins; i++)
	{
		rectangle(HistImg, cv::Point(i*bin_w, h), cv::Point((i + 1)*bin_w, h - cvRound(Hist.at<float>(i)*h / 255.0)),
			cv::Scalar(0, 0, 255), cv::FILLED);
	}
	imshow("Histogram", HistImg);
}
int BackProjection(int argc, char* argv[])
{
	cv::CommandLineParser Parser(argc, argv, "{@input |  | input image}");
	cv::Mat Source = cv::imread(argv[1]);
	if (Source.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	cv::Mat Hsv;
	cvtColor(Source, Hsv, cv::COLOR_BGR2HSV);
	hue.create(Hsv.size(), Hsv.depth());
	int ch[] = { 0, 0 };
	mixChannels(&Hsv, 1, &hue, 1, ch, 1);
	const char* kWindowImage = "Source image";
	cv::namedWindow(kWindowImage);
	cv::createTrackbar("* Hue  bins: ", kWindowImage, &bins, 180, HistAndBackproj);
	HistAndBackproj(0, 0);
	cv::imshow(kWindowImage, Source);
	// Wait until user exits the program
	cv::waitKey();
	return 0;
}