#include <opencv2/opencv.hpp>
#include "more_morphology_transformations.h"

cv::Mat MorphologySource, MorphologyDestination, DestinationOtsu;
int morph_element = 0; //フィルターの型　1: Cross ＋型- 2 : Ellipse"楕円形
int morph_size = 0;//フィルターのサイズ　０は１、１は３．．．．．．．
int morph_operator = 0;//各値に対応するmode　0: Opening - 1 : Closing  \n 2: Gradient - 3 : Top Hat \n 4: Black Hat
int const kMaxOperator = 4; //morph_operatorに対して、最大に選択できるmode
int const kMaxMorphElem = 2;//morph_elemに対して、最大に選択できるmode
int const kMaxMorphKernelSize = 21;//morph_sizeに対して、最大に選択できるサイズ
const char* kMorphologyTransformationsWindowName = "Morphology Transformations Demo";

void MorphologyOperations(int, void*)
{
	// Since MORPH_X : 2,3,4,5 and 6
	int operation = morph_operator + 2;
	cv::Mat Element = cv::getStructuringElement(morph_element, cv::Size(2 * morph_size + 1, 2 * morph_size + 1), cv::Point(morph_size, morph_size));

	//Performs advanced morphological transformations.
	morphologyEx(MorphologySource, MorphologyDestination, operation, Element);
	cv::Mat GrayImage;
	cvtColor(MorphologyDestination, GrayImage, cv::COLOR_BGR2GRAY);
	threshold(GrayImage, DestinationOtsu, 0, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);
	cv::imshow(kMorphologyTransformationsWindowName, DestinationOtsu);
}
int MoreMorphologyTransformations(int argc, char** argv)
{
	//CommandLineParser parser(argc, argv, "{@input | baboon.jpg | input image}");
	MorphologySource = cv::imread(cv::samples::findFile(argv[1]), cv::IMREAD_COLOR);//色空間で読み取る
	if (MorphologySource.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		//std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return EXIT_FAILURE;
	}
	cv::namedWindow(kMorphologyTransformationsWindowName, cv::WINDOW_AUTOSIZE); // Create window
	/*C++: int createTrackbar(const string& trackbarname, const string& winname, int* value, int count, TrackbarCallback onChange=0, void* userdata=0)
	Parameters:
	trackbarname – Name of the created trackbar.
		winname – Name of the window that will be used as a parent of the created trackbar.
		value – Optional pointer to an integer variable whose value reflects the position of the slider.Upon creation, the slider position is defined by this variable.
		count – Maximal position of the slider.The minimal position is always 0.
		onChange – Pointer to the function to be called every time the slider changes position.This function should be prototyped as void Foo(int, void*);, where the first parameter is the trackbar position and the second parameter is the user data(see the next parameter).If the callback is the NULL pointer, no callbacks are called, but only value is updated.
		userdata – User data that is passed as is to the callback.It can be used to handle trackbar events without using global variables.
	*/
	cv::createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", kMorphologyTransformationsWindowName, &morph_operator, kMaxOperator, MorphologyOperations);
	cv::createTrackbar("Element:\n 0: Rect - 1: Cross - 2: Ellipse", kMorphologyTransformationsWindowName,
		&morph_element, kMaxMorphElem,
		MorphologyOperations);
	cv::createTrackbar("Kernel size:\n 2n +1", kMorphologyTransformationsWindowName,
		&morph_size, kMaxMorphKernelSize,
		MorphologyOperations);
	MorphologyOperations(0, 0);//
	cv::waitKey(0);
	return 0;
}