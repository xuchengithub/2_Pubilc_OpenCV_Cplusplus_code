#include <opencv2/opencv.hpp>
#include "hough_line_transform.h"

int HoughLineTransform(int argc, char** argv)
{
	// Declare the output variables
	cv::Mat Destination, Cdst, CdstP;
	const char* kDefaultFile = "sudoku.png";
	const char* kFilename = argc >= 2 ? argv[1] : kDefaultFile;
	// Loads an image
	cv::Mat Source = cv::imread(cv::samples::findFile(kFilename), cv::IMREAD_GRAYSCALE);//グレースケール図
	// Check if image is loaded fine
	if (Source.empty()) {
		printf(" Error opening image\n");
		printf(" Program Arguments: [image_name -- default %s] \n", kDefaultFile);
		return -1;
	}
	// Edge detection
	Canny(Source, Destination, 50, 200, 3);
	// Copy edges to the images that will display the results in BGR
	cvtColor(Destination, Cdst, cv::COLOR_GRAY2BGR);
	CdstP = Cdst.clone();
	// Standard Hough Line Transform

	std::vector<cv::Vec2f> lines; // will hold the results of the detection
	HoughLines(Destination, lines, 1, CV_PI / 180, 150, 0, 0); // runs the actual detection

	//dst: Output of the edge detector.It should be a grayscale image(although in fact it is a binary one)//エッジ画像
	//lines : A vector that will store the parameters(r, θ) of the detected lines//(r, θ)を保存するため、vectorを作成
	//rho : The resolution of the parameter r in pixels.We use 1 pixel.　　　　　　　　　　//線の長さの範囲
	//theta : The resolution of the parameter θ in radians.We use 1 degree(CV_PI / 180)　　//線の向きの範囲
	//threshold : The minimum number of intersections to "*detect*" a line　　　　　　　　　//交点の数
	//srn and stn : Default parameters to zero.Check OpenCV reference for more info.　　　　//

	// Draw the lines
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(Cdst, pt1, pt2, cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
	}
	// Probabilistic Line Transform
	std::vector<cv::Vec4i> linesP; // will hold the results of the detection
	HoughLinesP(Destination, linesP, 1, CV_PI / 180, 50, 50, 10); // runs the actual detection
	// Draw the lines
	for (size_t i = 0; i < linesP.size(); i++)
	{
		cv::Vec4i l = linesP[i];
		line(CdstP, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, cv::LINE_AA);
	}
	// Show results
	imshow("Source", Source);
	imshow("Detected Lines (in red) - Standard Hough Line Transform", Cdst);
	imshow("Detected Lines (in red) - Probabilistic Line Transform", CdstP);
	// Wait and Exit
	cv::waitKey();
	return 0;
}