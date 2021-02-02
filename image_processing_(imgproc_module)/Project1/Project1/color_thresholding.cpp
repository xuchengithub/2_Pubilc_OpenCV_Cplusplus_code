#include <opencv2/opencv.hpp>
#include "color_thresholding.h"

const cv::String kWindowCaptureName = "Video Capture";
const cv::String kWindowDetectionName = "Object Detection";
int const kMaxValue = 255;
const int kMaxValueh = 360 / 2;
int low_h = 0, low_s = 0, low_v = 0;
int high_h = kMaxValueh, high_s = kMaxValue, high_v = kMaxValue;


static void OnLowhThreshTrackbar(int, void *)
{
	low_h = cv::min(high_h - 1, low_h);
	cv::setTrackbarPos("Low h", kWindowDetectionName, low_h);
}
static void OnHighhThreshTrackbar(int, void *)
{
	high_h = cv::max(high_h, low_h + 1);
	cv::setTrackbarPos("High h", kWindowDetectionName, high_h);
}
static void OnLowsThreshTrackbar(int, void *)
{
	low_s = cv::min(high_s - 1, low_s);
	cv::setTrackbarPos("Low s", kWindowDetectionName, low_s);
}
static void OnHighsThreshTrackbar(int, void *)
{
	high_s = cv::max(high_s, low_s + 1);
	cv::setTrackbarPos("High s", kWindowDetectionName, high_s);
}
static void OnLowvThreshTrackbar(int, void *)
{
	low_v = cv::min(high_v - 1, low_v);
	cv::setTrackbarPos("Low V", kWindowDetectionName, low_v);
}
static void OnHighvThreshTrackbar(int, void *)
{
	high_v = cv::max(high_v, low_v + 1);
	cv::setTrackbarPos("High V", kWindowDetectionName, high_v);
}
int ColorThresholding(int argc, char** argv)
{
	/////////////////////////色(Hue)、彩度(Saturation・Chroma)、明度(Value・Brightness)/////////////////////////
	cv::VideoCapture cap(0);//カメラを取る。
	cv::namedWindow(kWindowCaptureName);
	cv::namedWindow(kWindowDetectionName);
	// Trackbars to set thresholds for HSV values
	cv::createTrackbar("Low h", kWindowDetectionName, &low_h, kMaxValueh, OnLowhThreshTrackbar);
	cv::createTrackbar("High h", kWindowDetectionName, &high_h, kMaxValueh, OnHighhThreshTrackbar);
	cv::createTrackbar("Low s", kWindowDetectionName, &low_s, kMaxValue, OnLowsThreshTrackbar);
	cv::createTrackbar("High s", kWindowDetectionName, &high_s, kMaxValue, OnHighsThreshTrackbar);
	cv::createTrackbar("Low v", kWindowDetectionName, &low_v, kMaxValue, OnLowvThreshTrackbar);
	cv::createTrackbar("High v", kWindowDetectionName, &high_v, kMaxValue, OnHighvThreshTrackbar);
	cv::Mat Frame, FrameHsv, FrameThreshold;
	while (true) {
		cap >> Frame;
		if (Frame.empty())
		{
			break;
		}
		// Convert from BGR to HSV colorspace
		cvtColor(Frame, FrameHsv, cv::COLOR_BGR2HSV);//hsvに変更
		// Detect the object based on HSV Range Values
		inRange(FrameHsv, cv::Scalar(low_h, low_s, low_v), cv::Scalar(high_h,high_s, high_v), FrameThreshold);
		// Show the frames
		imshow(kWindowCaptureName, Frame);
		imshow(kWindowDetectionName, FrameThreshold);
		char key = (char)cv::waitKey(30);
		if (key == 'q' || key == 27)
		{
			break;
		}
	}
	return 0;
}