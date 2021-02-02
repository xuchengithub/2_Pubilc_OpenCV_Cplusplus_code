#include <opencv2/opencv.hpp>
#include "extract_horizontal_and_vertical_lines_by_using_morphological_operations.h"

int ExtractHorizontalAndVerticalLinesByUsingMorphologicalOperations(int argc, char** argv)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////! [load_image]
	//CommandLineParser parser(argc, argv, "{@input | notes.png | input image}");
	cv::Mat ExtractHorizontalSource = cv::imread(argv[1],cv::IMREAD_COLOR);
	if (ExtractHorizontalSource.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		//cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}

	// Show source image
	imshow("extract_horizontal_source", ExtractHorizontalSource);
	//! [load_image]

	//////////////////////////////////////////////////////////////////////////////! [gray]
	// Transform source image to gray if it is not already
	cv::Mat GrayImage;

	if (ExtractHorizontalSource.channels() == 3)
	{
		cvtColor(ExtractHorizontalSource, GrayImage, cv::COLOR_BGR2GRAY);
	}
	else
	{
		GrayImage = ExtractHorizontalSource;
	}

	// Show gray image
	ShowWaitDestroy("gray", GrayImage);
	//! [gray]

	//! [bin]
	// Apply adaptiveThreshold at the bitwise_not of gray, notice the ~ symbol
	cv::Mat BinaryImage;
	adaptiveThreshold(~GrayImage, BinaryImage, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 15, -2);//size=15,•½‹Ï’l‚ð-2

	// Show binary image
	ShowWaitDestroy("binary", BinaryImage);
	//! [bin]

	//! [init]
	// Create the images that will use to extract the horizontal and vertical lines
	cv::Mat Horizontal = BinaryImage.clone();
	cv::Mat Vertical = BinaryImage.clone();
	//! [init]

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//! [horiz]
	// Specify size on horizontal axis
	int horizontal_size = Horizontal.cols / 30;

	// Create structure element for extracting horizontal lines through morphology operations
	cv::Mat HorizontalStructure = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(horizontal_size, 1));//Œ`‚ðì¬

	// Apply morphology operations
	erode(Horizontal, Horizontal, HorizontalStructure, cv::Point(-1, -1));
	dilate(Horizontal, Horizontal, HorizontalStructure, cv::Point(-1, -1));

	// Show extracted horizontal lines
	ShowWaitDestroy("horizontal", Horizontal);
	//! [horiz]

	//! [vert]
	// Specify size on vertical axis
	int vertical_size = Vertical.rows / 30;

	// Create structure element for extracting vertical lines through morphology operations
	cv::Mat VerticalStructure = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(1, vertical_size));

	// Apply morphology operations
	erode(Vertical, Vertical, VerticalStructure, cv::Point(-1, -1));
	dilate(Vertical, Vertical, VerticalStructure, cv::Point(-1, -1));

	// Show extracted vertical lines
	ShowWaitDestroy("vertical", Vertical);
	//! [vert]

	//! [smooth]
	// Inverse vertical image//”½“]
	bitwise_not(Vertical, Vertical);
	ShowWaitDestroy("vertical_bit", Vertical);

	// Extract edges and smooth image according to the logic
	// 1. extract edges
	// 2. dilate(edges)
	// 3. src.copyTo(smooth)
	// 4. blur smooth img
	// 5. smooth.copyTo(src, edges)

	// Step 1
	cv::Mat Edges;
	adaptiveThreshold(Vertical, Edges, 255, cv::ADAPTIVE_THRESH_MEAN_C, cv::THRESH_BINARY, 3, -2);
	ShowWaitDestroy("edges", Edges);

	// Step 2
	cv::Mat Kernel = cv::Mat::ones(2, 2, CV_8UC1);
	dilate(Edges, Edges, Kernel);
	ShowWaitDestroy("dilate", Edges);

	// Step 3
	cv::Mat Smooth;
	Vertical.copyTo(Smooth);

	// Step 4
	cv::blur(Smooth, Smooth, cv::Size(2, 2));

	// Step 5
	Smooth.copyTo(Vertical, Edges);

	// Show final result
	ShowWaitDestroy("smooth - final", Vertical);
	//! [smooth]

	return 0;
}
void ShowWaitDestroy(const char* winname, cv::Mat Img) {
	imshow(winname, Img);
	cv::moveWindow(winname, 500, 0);
	cv::waitKey(0);
	cv::destroyWindow(winname);
}