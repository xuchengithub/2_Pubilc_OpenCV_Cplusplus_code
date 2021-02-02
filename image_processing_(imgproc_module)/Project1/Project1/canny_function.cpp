#include <opencv2/opencv.hpp>
#include "canny_function.h"

cv::Mat Src3, SrcGray;
cv::Mat Dst3, DetectedEdges;

int canny_function_low_threshold = 0;
extern const int kMaxLowThreshold = 100;
extern const int kRatio = 3;
extern const int kKernelSize = 3;
extern const char* kCannyFuntionWindowName = "Edge Map";


static void CannyThreshold(int, void*)
{//smooth:::::::::Blurs an image using the normalized box filter.
	blur(SrcGray, DetectedEdges, cv::Size(3, 3));//borderType – border mode used to extrapolate pixels outside of the image.
	Canny(DetectedEdges, DetectedEdges, canny_function_low_threshold, canny_function_low_threshold*kRatio, kKernelSize);//
	//We fill a dst image with zeros(meaning the image is completely black)
	//dst9 = Scalar::all(0);
	//src9.copyTo(dst9, detected_edges);
	imshow(kCannyFuntionWindowName, DetectedEdges);
}
int CannyDerivatives(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv, "{@input | fruits.jpg | input image}");
	Src3 = cv::imread(cv::samples::findFile(Parser.get<cv::String>("@input")), cv::IMREAD_COLOR); // Load an image
	if (Src3.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	Dst3.create(Src3.size(), Src3.type());
	cvtColor(Src3, SrcGray, cv::COLOR_BGR2GRAY);
	cv::namedWindow(kCannyFuntionWindowName, cv::WINDOW_AUTOSIZE);
	cv::createTrackbar("Min Threshold:", kCannyFuntionWindowName, &canny_function_low_threshold, kMaxLowThreshold, CannyThreshold);
	CannyThreshold(0, 0);
	cv::waitKey(0);
	return 0;
}