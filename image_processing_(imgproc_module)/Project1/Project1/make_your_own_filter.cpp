#include <opencv2/opencv.hpp>
#include "make_your_own_filter.h"

int MakeYourOwnFilter(int argc, char** argv)
{
	// Declare variables
	cv::Mat Source, Destination;
	cv::Mat Kernel;
	cv::Point Anchor;
	double delta;
	int ddepth;
	int kernel_size;
	const char* kWindowName = "filter2D Demo";
	const std::string kImageName = argv[1];
	// Loads an image
	Source = cv::imread(cv::samples::findFile(kImageName), cv::IMREAD_COLOR); // Load an image
	if (Source.empty())
	{
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default lena.jpg] \n");
		return EXIT_FAILURE;
	}
	// Initialize arguments for the filter
	Anchor = cv::Point(-1, -1);//anchor of the kernel that indicates the relative position of a filtered point within the kernel; the anchor should lie within the kernel; default value (-1,-1) means that the anchor is at the kernel center.
	delta = 0;
	ddepth = -1;//when ddepth=-1, the output image will have the same depth as the source.
	// Loop - Will filter the image with different kernel sizes each 0.5 seconds
	int ind = 0;
	for (;;)
	{
		// Update kernel size for a normalized box filter
		kernel_size = 3 + 2 * (ind % 5);
		Kernel = cv::Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
		// Apply filter
		filter2D(Source, Destination, ddepth, Kernel, Anchor, delta, cv::BORDER_DEFAULT);
		imshow(kWindowName, Destination);
		char c = (char)cv::waitKey(500);
		// Press 'ESC' to exit the program
		if (c == 27)
		{
			break;
		}
		ind++;
	}
	return EXIT_SUCCESS;
}