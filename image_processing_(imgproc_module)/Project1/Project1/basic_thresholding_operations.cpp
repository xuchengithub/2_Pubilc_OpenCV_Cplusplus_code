#include <opencv2\opencv.hpp>
#include "basic_thresholding_operations.h"

cv::Mat Src1, dst1, src_gray1;
int threshold_value = 0;
int threshold_type = 3;
int const kMaxValue = 255;
int const kMaxType = 4;
int const kMaxBinaryValue = 255;
const char* kWindowName = "Threshold Demo";
const char* kTrackbarType = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
const char* kTrackbarValue = "Value";


static void ThresholdDemo(int, void*)
{
	/* 0: Binary
	 1: Binary Inverted
	 2: Threshold Truncated
	 3: Threshold to Zero
	 4: Threshold to Zero Inverted
	*/
	cv::threshold(src_gray1, dst1, threshold_value, kMaxBinaryValue, threshold_type);
	cv::imshow(kWindowName, dst1);
}
int BasicThresholdingOperations(int argc, char** argv)
{
	cv::String imageName("stuff.jpg"); // by default
	if (argc > 1)
	{
		imageName = argv[1];
	}
	Src1 = cv::imread(cv::samples::findFile(imageName), cv::IMREAD_COLOR); // Load an image
	if (Src1.empty())
	{
		std::cout << "Cannot read the image: " << imageName << std::endl;
		return -1;
	}
	cvtColor(Src1, src_gray1, cv::COLOR_BGR2GRAY); // Convert the image to Gray
	cv::namedWindow(kWindowName, cv::WINDOW_AUTOSIZE); // Create a window to display results
	cv::createTrackbar(kTrackbarType,
		kWindowName, &threshold_type,
		kMaxType, ThresholdDemo); // Create a Trackbar to choose type of Threshold
	cv::createTrackbar(kTrackbarValue,
		kWindowName, &threshold_value,
		kMaxValue, ThresholdDemo); // Create a Trackbar to choose Threshold value
	ThresholdDemo(0, 0); // Call the function to initialize
	cv::waitKey();
	return 0;
}