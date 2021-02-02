#include <opencv2/opencv.hpp>
#include "histogram_calculation.h"

int HistogramCalculation(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv, "{@input | lena.jpg | input image}");
	cv::Mat Source = cv::imread(cv::samples::findFile(Parser.get<cv::String>("@input")), cv::IMREAD_COLOR);
	if (Source.empty())
	{
		return EXIT_FAILURE;
	}
	std::vector<cv::Mat> BgrPlanes;
	split(Source, BgrPlanes);
	int hist_size = 256;
	float range[] = { 0, 256 }; //the upper boundary is exclusive
	const float* kHistRange = { range };
	bool uniform = true, accumulate = false;
	cv::Mat BHist, GHist, RHist;
	cv::calcHist(&BgrPlanes[0], 1, 0, cv::Mat(), BHist, 1, &hist_size, &kHistRange, uniform, accumulate);
	cv::calcHist(&BgrPlanes[1], 1, 0, cv::Mat(), GHist, 1, &hist_size, &kHistRange, uniform, accumulate);
	cv::calcHist(&BgrPlanes[2], 1, 0, cv::Mat(), RHist, 1, &hist_size, &kHistRange, uniform, accumulate);
	int hist_w = 512, hist_h = 400;
	int bin_w = cvRound((double)hist_w / hist_size);
	cv::Mat HistImage(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));
	normalize(BHist, BHist, 0, HistImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(GHist, GHist, 0, HistImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	normalize(RHist, RHist, 0, HistImage.rows, cv::NORM_MINMAX, -1, cv::Mat());
	for (int i = 1; i < hist_size; i++)
	{
		line(HistImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(BHist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(BHist.at<float>(i))),
			cv::Scalar(255, 0, 0), 2, 8, 0);
		line(HistImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(GHist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(GHist.at<float>(i))),
			cv::Scalar(0, 255, 0), 2, 8, 0);
		line(HistImage, cv::Point(bin_w*(i - 1), hist_h - cvRound(RHist.at<float>(i - 1))),
			cv::Point(bin_w*(i), hist_h - cvRound(RHist.at<float>(i))),
			cv::Scalar(0, 0, 255), 2, 8, 0);
	}
	cv::imshow("Source image", Source);
	cv::imshow("calcHist Demo", HistImage);
	cv::waitKey();
	return EXIT_SUCCESS;
}