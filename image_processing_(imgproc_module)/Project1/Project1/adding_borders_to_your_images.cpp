#include <opencv2/opencv.hpp>
#include "adding_borders_to_your_images.h"

cv::Mat Src2, dst2;
int top, bottom, left, right;
int kBorderType = cv::BORDER_CONSTANT;
extern const char* kAddingBordersToYourImagesWindowName = "copyMakeBorder Demo";
cv::RNG rng(12345);

int AddingBordersToYourImages(int argc, char** argv)
{
	const std::string kImageName = argv[1];
	// Loads an image
	Src2 = cv::imread(cv::samples::findFile(kImageName), cv::IMREAD_COLOR); // Load an image
	// Check if image is loaded fine
	if (Src2.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default lena.jpg] \n");
		return -1;
	}
	// Brief how-to for this program
	printf("\n \t copyMakeBorder Demo: \n");
	printf("\t -------------------- \n");
	printf(" ** Press 'c' to set the border to a random constant value \n");
	printf(" ** Press 'r' to set the border to be replicated \n");
	printf(" ** Press 'ESC' to exit the program \n");
	cv::namedWindow(kAddingBordersToYourImagesWindowName, cv::WINDOW_AUTOSIZE);
	// Initialize arguments for the filter
	top = (int)(0.05*Src2.rows); bottom = top;
	left = (int)(0.05*Src2.cols); right = left;
	for (;;)
	{
		cv::Scalar Value(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		copyMakeBorder(Src2, dst2, top, bottom, left, right, kBorderType, Value);
		imshow(kAddingBordersToYourImagesWindowName, dst2);
		char c = (char)cv::waitKey(500);
		if (c == 27)
		{
			break;
		}
		else if (c == 'c')
		{
			kBorderType = cv::BORDER_CONSTANT;
		}
		else if (c == 'r')
		{
			kBorderType = cv::BORDER_REPLICATE;
		}
	}
	return 0;
}