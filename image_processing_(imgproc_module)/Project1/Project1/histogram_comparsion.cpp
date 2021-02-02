#include <opencv2/opencv.hpp>
#include "histogram_comparsion.h"

extern const char* kKeys =
"{ help  h| | Print help message. }"
"{ @input1 | | Path to input image 1. }"
"{ @input2 | | Path to input image 2. }"
"{ @input3 | | Path to input image 3. }";

int HistogramComparison(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv, kKeys);
	cv::Mat SrcBase = cv::imread(argv[1]);
	cv::Mat SrcTest1 = cv::imread(argv[2]);
	cv::Mat SrcTest2 = cv::imread(argv[3]);
	if (SrcBase.empty() || SrcTest1.empty() || SrcTest2.empty())
	{
		std::cout << "Could not open or find the images!\n" << std::endl;
		Parser.printMessage();
		return -1;
	}
	cv::Mat HsvBase, HsvTest1, HsvTest2;
	cvtColor(SrcBase, HsvBase, cv::COLOR_BGR2HSV);
	cvtColor(SrcTest1, HsvTest1, cv::COLOR_BGR2HSV);
	cvtColor(SrcTest2, HsvTest2, cv::COLOR_BGR2HSV);
	cv::Mat HsvHalfDown = HsvBase(cv::Range(HsvBase.rows / 2, HsvBase.rows), cv::Range(0, HsvBase.cols));
	int h_bins = 50, s_bins = 60;
	int histSize[] = { h_bins, s_bins };
	// hue varies from 0 to 179, saturation from 0 to 255
	float h_ranges[] = { 0, 180 };
	float s_ranges[] = { 0, 256 };
	const float* kRanges[] = { h_ranges, s_ranges };
	// Use the 0-th and 1-st channels
	int channels[] = { 0, 1 };
	cv::Mat HistBase, HistHalfDown, HistTest1, HistTest2;
	calcHist(&HsvBase, 1, channels, cv::Mat(), HistBase, 2, histSize, kRanges, true, false);
	normalize(HistBase, HistBase, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	calcHist(&HsvHalfDown, 1, channels, cv::Mat(), HistHalfDown, 2, histSize, kRanges, true, false);
	normalize(HistHalfDown, HistHalfDown, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	calcHist(&HsvTest1, 1, channels, cv::Mat(), HistTest1, 2, histSize, kRanges, true, false);
	normalize(HistTest1, HistTest1, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	calcHist(&HsvTest2, 1, channels, cv::Mat(), HistTest2, 2, histSize, kRanges, true, false);
	normalize(HistTest2, HistTest2, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	for (int compare_method = 0; compare_method < 4; compare_method++)
	{
		double base_base = compareHist(HistBase, HistBase, compare_method);
		double base_half = compareHist(HistBase, HistHalfDown, compare_method);
		double base_test1 = compareHist(HistBase, HistTest1, compare_method);
		double base_test2 = compareHist(HistBase, HistTest2, compare_method);
		std::cout << "Method " << compare_method << " Perfect, Base-Half, Base-Test(1), Base-Test(2) : "
			<< base_base << " / " << base_half << " / " << base_test1 << " / " << base_test2 << std::endl;
	}
	std::cout << "Done \n";
	return 0;
}