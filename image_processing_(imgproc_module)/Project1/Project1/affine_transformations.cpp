#include <opencv2/opencv.hpp>
#include "affine_transformations.h"

int AffineTransformations(int argc, char** argv)
{
	cv::CommandLineParser Parser(argc, argv, "{@input | lena.jpg | input image}");
	cv::Mat Source = cv::imread(cv::samples::findFile(Parser.get<cv::String>("@input")));
	if (Source.empty())
	{
		std::cout << "Could not open or find the image!\n" << std::endl;
		std::cout << "Usage: " << argv[0] << " <Input image>" << std::endl;
		return -1;
	}
	cv::Point2f SrcTri[3];
	SrcTri[0] = cv::Point2f(0.f, 0.f);
	SrcTri[1] = cv::Point2f(Source.cols - 1.f, 0.f);
	SrcTri[2] = cv::Point2f(0.f, Source.rows - 1.f);
	cv::Point2f DstTri[3];
	DstTri[0] = cv::Point2f(0.f, Source.rows*0.33f);
	DstTri[1] = cv::Point2f(Source.cols*0.85f, Source.rows*0.25f);
	DstTri[2] = cv::Point2f(Source.cols*0.15f, Source.rows*0.7f);
	cv::Mat WarpMat = getAffineTransform(SrcTri, DstTri);
	cv::Mat WarpDst = cv::Mat::zeros(Source.rows, Source.cols, Source.type());
	warpAffine(Source, WarpDst, WarpMat, WarpDst.size());
	cv::Point center = cv::Point(WarpDst.cols / 2, WarpDst.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	cv::Mat RotMat = getRotationMatrix2D(center, angle, scale);
	cv::Mat WarpRotateDst;
	warpAffine(WarpDst, WarpRotateDst, RotMat, WarpDst.size());
	cv::imshow("Source image", Source);
	cv::imshow("Warp", WarpDst);
	cv::imshow("Warp + Rotate", WarpRotateDst);
	cv::waitKey();
	return 0;
}