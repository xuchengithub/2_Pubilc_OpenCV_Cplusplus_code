#ifndef BACKPROJECTION_H
#define BACKPROJECTION_H

extern cv::Mat hue;
extern int bins;

void HistAndBackproj(int, void*);
int BackProjection(int argc, char* argv[]);

#endif