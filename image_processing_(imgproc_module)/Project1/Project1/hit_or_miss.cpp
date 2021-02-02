#include <opencv2/opencv.hpp>
#include "hit_or_miss.h"

int HitOrMiss() {
	cv::Mat InputImage = (cv::Mat_<uchar>(8, 8) <<
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 0, 0, 255,
		0, 255, 255, 255, 0, 0, 0, 0,
		0, 255, 255, 255, 0, 255, 0, 0,
		0, 0, 255, 0, 0, 0, 0, 0,
		0, 0, 255, 0, 0, 255, 255, 0,
		0, 255, 0, 255, 0, 0, 255, 0,
		0, 255, 255, 255, 0, 0, 0, 0);
	cv::Mat Kernel = (cv::Mat_<int>(3, 3) <<
		0, 1, 0,
		1, -1, 1,
		0, 1, 0);
	cv::Mat OutputImage;
	morphologyEx(InputImage, OutputImage, cv::MORPH_HITMISS, Kernel);

	const int kEnlargementTime = 50;
	Kernel = (Kernel + 1) * 127;

	Kernel.convertTo(Kernel, CV_8U);//画像を作成ー１の時、黒い、０の時グレー、１の時、白い
	cv::resize(Kernel, Kernel, cv::Size(), kEnlargementTime, kEnlargementTime, cv::INTER_NEAREST); 
	//void resize(InputArray src, OutputArray dst, Size dsize, double fx = 0, double fy = 0, int interpolation = INTER_LINEAR)¶
	imshow("kernel", Kernel);
	cv::moveWindow("kernel", 0, 0);
	resize(InputImage, InputImage, cv::Size(), kEnlargementTime, kEnlargementTime, cv::INTER_NEAREST);
	imshow("Original", InputImage);
	cv::moveWindow("Original", 0, 200);
	resize(OutputImage, OutputImage, cv::Size(), kEnlargementTime, kEnlargementTime, cv::INTER_NEAREST);
	imshow("Hit or Miss", OutputImage);
	cv::moveWindow("Hit or Miss", 500, 200);
	cv::waitKey(0);
	return 0;
}