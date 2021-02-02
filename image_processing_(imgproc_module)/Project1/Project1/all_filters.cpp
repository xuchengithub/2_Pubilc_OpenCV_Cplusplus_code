#include <opencv2/opencv.hpp>
#include "all_filters.h"

cv::Mat Source;cv::Mat Destination;
int delay_caption = 1500;
int delay_blur = 100;
int max_kernel_length = 31;
char window_name[] = "Smoothing Demo";

int DisplayDst(int delay)
{
	imshow(window_name, Destination);
	int c = cv::waitKey(delay);
	if (c >= 0) { return -1; }
	return 0;
}
int DisplayCaption(const char* caption)
{
	Destination = cv::Mat::zeros(Source.size(), Source.type());
	putText(Destination, caption,
		cv::Point(Source.cols / 4, Source.rows / 2),
		cv::FONT_HERSHEY_COMPLEX, 1, cv::Scalar(255, 255, 255));

	return DisplayDst(delay_caption);
}
int AllFilters(int argc, char ** argv)
{
	cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);

	/// Load the source image
	const char* kFileName = argc >= 2 ? argv[2] : "lena.jpg";

	Source = cv::imread(cv::samples::findFile(kFileName), cv::IMREAD_COLOR);

	if (Source.empty())
	{
		printf(" Error opening image\n");
		printf(" Usage:\n %s [image_name-- default lena.jpg] \n", argv[0]);
		return EXIT_FAILURE;
	}

	if (DisplayCaption("Original Image") != 0)
	{
		return 0;
	}

	Destination = Source.clone();
	if (DisplayDst(delay_caption) != 0)
	{
		return 0;
	}

	/// Applying Homogeneous blur
	if (DisplayCaption("Homogeneous Blur") != 0)
	{
		return 0;
	}

	//![blur]
	for (int i = 1; i < max_kernel_length; i = i + 2)
	{
		blur(Source, Destination, cv::Size(i, i), cv::Point(-1, -1));
		if (DisplayDst(delay_blur) != 0)
		{
			return 0;
		}
	}
	//![blur]

	/// Applying Gaussian blur
	if (DisplayCaption("Gaussian Blur") != 0)
	{
		return 0;
	}

	//![gaussianblur]
	for (int i = 1; i < max_kernel_length; i = i + 2)
	{
		GaussianBlur(Source, Destination, cv::Size(i, i), 0, 0);
		if (DisplayDst(delay_blur) != 0)
		{
			return 0;
		}
	}
	//![gaussianblur]

	/// Applying Median blur
	if (DisplayCaption("Median Blur") != 0)
	{
		return 0;
	}

	//![medianblur]
	for (int i = 1; i < max_kernel_length; i = i + 2)
	{
		cv::medianBlur(Source, Destination, i);
		if (DisplayDst(delay_blur) != 0)
		{
			return 0;
		}
	}
	//![medianblur]

	/// Applying Bilateral Filter
	if (DisplayCaption("Bilateral Blur") != 0)
	{
		return 0;
	}

	//![bilateralfilter]
	for (int i = 1; i < max_kernel_length; i = i + 2)
	{
		bilateralFilter(Source, Destination, i, i * 2, i / 2);
		if (DisplayDst(delay_blur) != 0)
		{
			return 0;
		}
	}
	//![bilateralfilter]

	/// Done
	DisplayCaption("Done!");

	return 0;
}



