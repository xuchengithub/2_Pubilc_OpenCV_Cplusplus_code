#ifndef BRIEF_SIMPLE_GEOMETRIC_DRAWING_H
#define BRIEF_SIMPLE_GEOMETRIC_DRAWING_H

#include <opencv2/opencv.hpp>

#define SIZEIMAGE 400

int BriefSimpleGeometricDrawing(void);
void MyEllipse(cv::Mat Img, double angle);
void MyFilledCircle(cv::Mat Img, cv::Point center);
void MyPolygon(cv::Mat Img);
void MyLine(cv::Mat Img, cv::Point start, cv::Point end);

#endif

