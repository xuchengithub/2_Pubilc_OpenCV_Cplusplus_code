#include <opencv2/opencv.hpp>
#include "dilation_erosion.h"

cv::Mat DilationSource, ErosionDestination, DilationDestination;
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const kMaxElem = 2;
int const kMaxKernelSize = 21;

void Erosion(int, void*)
{
	int erosion_type = 0;
	if (erosion_elem == 0) { erosion_type = cv::MORPH_RECT; }
	else if (erosion_elem == 1) { erosion_type = cv::MORPH_CROSS; }
	else if (erosion_elem == 2) { erosion_type = cv::MORPH_ELLIPSE; }

	//![kernel]
	cv::Mat Element = cv::getStructuringElement(erosion_type,
		cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
		cv::Point(erosion_size, erosion_size));
	//![kernel]

	/// Apply the erosion operation
	erode(DilationSource, ErosionDestination, Element);
	cv::imshow("Erosion Demo", ErosionDestination);
}
void Dilation(int, void*)
{
	int dilation_type = 0;
	if (dilation_elem == 0) { dilation_type = cv::MORPH_RECT; }
	else if (dilation_elem == 1) { dilation_type = cv::MORPH_CROSS; }
	else if (dilation_elem == 2) { dilation_type = cv::MORPH_ELLIPSE; }

	cv::Mat Element = cv::getStructuringElement(dilation_type,
		cv::Size(2 * dilation_size + 1, 2 * dilation_size + 1),
		cv::Point(dilation_size, dilation_size));

	/// Apply the dilation operation
	dilate(DilationSource, DilationDestination, Element);
	cv::imshow("Dilation Demo", DilationDestination);
}
int DilationErosion(int argc, char** argv)
{
	/// Load an image
	//CommandLineParser parser(argc, filename, "{@input | LinuxLogo.jpg | input image}");//
	DilationSource = cv::imread(argv[1]);
	if (DilationSource.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		//cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}

	/// Create windows
	cv::namedWindow("Erosion Demo", cv::WINDOW_AUTOSIZE);
	cv::namedWindow("Dilation Demo", cv::WINDOW_AUTOSIZE);
	cv::moveWindow("Dilation Demo", DilationSource.cols, 0);//window‚ÌêŠ‚ð•Ï‚¦‚éB

	/// Create Erosion Trackbar
	cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
		&erosion_elem, kMaxElem,
		Erosion);

	cv::createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
		&erosion_size, kMaxKernelSize,
		Erosion);

	/// Create Dilation Trackbar
	cv::createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
		&dilation_elem, kMaxElem,
		Dilation);

	cv::createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
		&dilation_size, kMaxKernelSize,
		Dilation);

	/// Default start
	Erosion(0, 0);
	Dilation(0, 0);

	cv::waitKey(0);
	return 0;
}