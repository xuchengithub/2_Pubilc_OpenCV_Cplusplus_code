#include <opencv2/opencv.hpp>
#include "sobel_derivatives.h"

int SobelDerivatives(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv,
		"{@input   |lena.jpg|input image}"
		"{ksize   k|1|ksize (hit 'K' to increase its value at run time)}"
		"{scale   s|1|scale (hit 'S' to increase its value at run time)}"
		"{delta   d|0|delta (hit 'D' to increase its value at run time)}");
	std::cout << "The sample uses Sobel or Scharr OpenCV functions for edge detection\n\n";
	Parser.printMessage();
	std::cout << "\nPress 'ESC' to exit program.\nPress 'R' to reset values ( ksize will be -1 equal to Scharr function )";
	// First we declare the variables we are going to use
	cv::Mat Image, Source, Src_gray;
	cv::Mat Grad;
	const cv::String kWindowName = "Sobel Demo - Simple Edge Detector";
	int ksize = Parser.get<int>("ksize");
	int scale = Parser.get<int>("scale");
	int delta = Parser.get<int>("delta");
	int ddepth = CV_16S;
	cv::String kImageName = Parser.get<cv::String>("@input");
	// As usual we load our source image (src)
	Image = cv::imread(cv::samples::findFile(kImageName), cv::IMREAD_COLOR); // Load an image
	// Check if image is loaded fine
	if (Image.empty())
	{
		printf("Error opening image: %s\n", kImageName.c_str());
		return EXIT_FAILURE;
	}
	for (;;)
	{
		// Remove noise by blurring with a Gaussian filter ( kernel size = 3 )
		GaussianBlur(Image, Source, cv::Size(3, 3), 0, 0, cv::BORDER_DEFAULT);
		// Convert the image to grayscale
		cvtColor(Source, Src_gray, cv::COLOR_BGR2GRAY);
		cv::Mat GradX, GradY;
		cv::Mat AbsGradX, AbsGradY;
		Sobel(Src_gray, GradX, ddepth, 1, 0, ksize, scale, delta, cv::BORDER_DEFAULT);//ksize,scale,delta
		Sobel(Src_gray, GradY, ddepth, 0, 1, ksize, scale, delta, cv::BORDER_DEFAULT);
		//ksize – size of the extended Sobel kernel; it must be 1, 3, 5, or 7.
		//scale – optional scale factor for the computed derivative values; by default, no scaling is applied(see getDerivKernels() for details).
		//delta – optional delta value that is added to the results prior to storing them in dst.
		//borderType – pixel extrapolation method(see borderInterpolate() for details).
		// converting back to CV_8U
		convertScaleAbs(GradX, AbsGradX);
		convertScaleAbs(GradY, AbsGradY);
		addWeighted(AbsGradX, 0.5, AbsGradY, 0.5, 0, Grad);//dst(I)=saturate(src1(I)∗alpha+src2(I)∗beta+gamma)
		imshow(kWindowName, Grad);
		char key = (char)cv::waitKey(0);
		if (key == 27)
		{
			return EXIT_SUCCESS;
		}
		if (key == 'k' || key == 'K')
		{
			ksize = ksize < 30 ? ksize + 2 : -1;
		}
		if (key == 's' || key == 'S')
		{
			scale++;
		}
		if (key == 'd' || key == 'D')
		{
			delta++;
		}
		if (key == 'r' || key == 'R')
		{
			scale = 1;
			ksize = -1;
			delta = 0;
		}
	}
	return EXIT_SUCCESS;
}