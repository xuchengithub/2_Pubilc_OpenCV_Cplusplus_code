#ifndef DRAWING_RANDOM_LINES_H
#define DRAWING_RANDOM_LINES_H

#include <opencv2/opencv.hpp>

int DrawingRandom(void);
int DrawingRandomLines(cv::Mat image, const char* window_name, cv::RNG rng);
static cv::Scalar RandomColor(cv::RNG& rng);
int DisplayingRandomText(cv::Mat image, const char* window_name, cv::RNG rng);
int DisplayingBigEnd(cv::Mat image, const char* window_name, cv::RNG rng);

#endif



