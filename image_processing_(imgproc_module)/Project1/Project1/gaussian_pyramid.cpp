#include <opencv2/opencv.hpp>
#include "gaussian_pyramid.h"

int GaussianPyramid(int argc, char** argv)
{
	std::cout << argv[1] << std::endl;
	std::cout << "\n Zoom In-Out demo \n "
		"------------------  \n"
		" * [i] -> Zoom in   \n"
		" * [o] -> Zoom out  \n"
		" * [ESC] -> Close program \n" << std::endl;
	//const char* filename = argc >= 2 ? filename : "chicky_512.png";
	// Loads an image
	cv::Mat GaussianPyramidSource = cv::imread(argv[1]);
	// Check if image is loaded fine
	if (GaussianPyramidSource.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default chicky_512.png] \n");
		return EXIT_FAILURE;
	}
	for (;;)
	{
		imshow("window_name", GaussianPyramidSource);
		char c = (char)cv::waitKey(0);
		if (c == 27)
		{
			break;
		}
		else if (c == 'i')
		{
			pyrUp(GaussianPyramidSource, GaussianPyramidSource, cv::Size(GaussianPyramidSource.cols * 2, GaussianPyramidSource.rows * 2));
			printf("** Zoom In: Image x 2 \n");
		}
		else if (c == 'o')
		{
			pyrDown(GaussianPyramidSource, GaussianPyramidSource, cv::Size(GaussianPyramidSource.cols / 2, GaussianPyramidSource.rows / 2));
			printf("** Zoom Out: Image / 2 \n");
		}
	}
	return EXIT_SUCCESS;
}