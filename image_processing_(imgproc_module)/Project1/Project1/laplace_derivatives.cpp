#include <opencv2/opencv.hpp>
#include "laplace_derivatives.h"

int LaplaceDerivatives(int argc, char** argv)
{
	// Declare the variables we are going to use
	cv::Mat Source, SrcGray, Destination;
	int kernel_size = 3;
	int scale = 1;
	int delta = 0;
	int ddepth = CV_16S;
	const char* kWindowName = "Laplace Demo";
	const char* KImageName = argc >= 2 ? argv[1] : "lena.jpg";
	Source = cv::imread(cv::samples::findFile(KImageName), cv::IMREAD_COLOR); // Load an image
	// Check if image is loaded fine
	if (Source.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default lena.jpg] \n");
		return -1;
	}
	// Reduce noise by blurring with a Gaussian filter ( kernel size = 3 )
	GaussianBlur(Source, Source, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
	cvtColor(Source, SrcGray, cv::COLOR_BGR2GRAY); // Convert the image to grayscale
	cv::Mat AbsDst;
	Laplacian(SrcGray, Destination, ddepth, kernel_size, scale, delta, cv::BORDER_DEFAULT);
	// converting back to CV_8U
	convertScaleAbs(Destination, AbsDst);
	cv::imshow(kWindowName, AbsDst);
	cv::waitKey(0);
	return 0;
}