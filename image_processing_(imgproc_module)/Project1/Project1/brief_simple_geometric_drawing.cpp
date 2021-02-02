#include <opencv2/opencv.hpp>
#include "brief_simple_geometric_drawing.h"

#define SIZEIMAGE 400
//input function 
void MyLine(cv::Mat Img, cv::Point start, cv::Point end)
{
	int line_thickness = 2;
	int line_type = cv::LINE_8;

	line(Img,
		start,
		end,
		cv::Scalar(0, 0, 0),
		line_thickness,
		line_type);
}

void MyPolygon(cv::Mat Img)
{
	int line_type = cv::LINE_8;

	/** Create 20 points */
	cv::Point rook_points[1][20];
	rook_points[0][0] = cv::Point(SIZEIMAGE / 4, 7 * SIZEIMAGE / 8);
	rook_points[0][1] = cv::Point(3 * SIZEIMAGE / 4, 7 * SIZEIMAGE / 8);
	rook_points[0][2] = cv::Point(3 * SIZEIMAGE / 4, 13 * SIZEIMAGE / 16);
	rook_points[0][3] = cv::Point(11 * SIZEIMAGE / 16, 13 * SIZEIMAGE / 16);
	rook_points[0][4] = cv::Point(19 * SIZEIMAGE / 32, 3 * SIZEIMAGE / 8);
	rook_points[0][5] = cv::Point(3 * SIZEIMAGE / 4, 3 * SIZEIMAGE / 8);
	rook_points[0][6] = cv::Point(3 * SIZEIMAGE / 4, SIZEIMAGE / 8);
	rook_points[0][7] = cv::Point(26 * SIZEIMAGE / 40, SIZEIMAGE / 8);
	rook_points[0][8] = cv::Point(26 * SIZEIMAGE / 40, SIZEIMAGE / 4);
	rook_points[0][9] = cv::Point(22 * SIZEIMAGE / 40, SIZEIMAGE / 4);
	rook_points[0][10] = cv::Point(22 * SIZEIMAGE / 40, SIZEIMAGE / 8);
	rook_points[0][11] = cv::Point(18 * SIZEIMAGE / 40, SIZEIMAGE / 8);
	rook_points[0][12] = cv::Point(18 * SIZEIMAGE / 40, SIZEIMAGE / 4);
	rook_points[0][13] = cv::Point(14 * SIZEIMAGE / 40, SIZEIMAGE / 4);
	rook_points[0][14] = cv::Point(14 * SIZEIMAGE / 40, SIZEIMAGE / 8);
	rook_points[0][15] = cv::Point(SIZEIMAGE / 4, SIZEIMAGE / 8);
	rook_points[0][16] = cv::Point(SIZEIMAGE / 4, 3 * SIZEIMAGE / 8);
	rook_points[0][17] = cv::Point(13 * SIZEIMAGE / 32, 3 * SIZEIMAGE / 8);
	rook_points[0][18] = cv::Point(5 * SIZEIMAGE / 16, 13 * SIZEIMAGE / 16);
	rook_points[0][19] = cv::Point(SIZEIMAGE / 4, 13 * SIZEIMAGE / 16);

	const cv::Point* ppt[1] = { rook_points[0] };
	int npt[] = { 20 };

	fillPoly(Img,
		ppt,
		npt,
		1,
		cv::Scalar(255, 255, 255),
		line_type);
}

void MyFilledCircle(cv::Mat Img, cv::Point center)
{
	circle(Img,
		center,
		SIZEIMAGE / 32,
		cv::Scalar(0, 0, 255),
		cv::FILLED,
		cv::LINE_8);
}

void MyEllipse(cv::Mat Img, double angle) {
	int thick_ness = 2;
	int line_type = 8;

	ellipse(Img,
		cv::Point(SIZEIMAGE / 2, SIZEIMAGE / 2),
		cv::Size(SIZEIMAGE / 4, SIZEIMAGE / 16),
		angle,
		0,
		360,
		cv::Scalar(255, 0, 0),
		thick_ness,
		line_type);
}

int BriefSimpleGeometricDrawing(void) {

	//![create_images]
	/// Windows names
	char atom_window[] = "Drawing 1: Atom";
	char rook_window[] = "Drawing 2: Rook";

	/// Create black empty images
	cv::Mat AtomImage = cv::Mat::zeros(SIZEIMAGE, SIZEIMAGE, CV_8UC3);
	cv::Mat RookImage = cv::Mat::zeros(SIZEIMAGE, SIZEIMAGE, CV_8UC3);
	//![create_images]

	/// 1. Draw a simple atom:
	/// -----------------------

	//![draw_atom]
	/// 1.a. Creating ellipses
	MyEllipse(AtomImage, 90);
	MyEllipse(AtomImage, 0);
	MyEllipse(AtomImage, 45);
	MyEllipse(AtomImage, -45);

	/// 1.b. Creating circles
	MyFilledCircle(AtomImage, cv::Point(SIZEIMAGE / 2, SIZEIMAGE / 2));
	//![draw_atom]

	/// 2. Draw a rook
	/// ------------------

	//![draw_rook]
	/// 2.a. Create a convex polygon
	MyPolygon(RookImage);

	//![rectangle]
	/// 2.b. Creating rectangles
	rectangle(RookImage,
		cv::Point(0, 7 * SIZEIMAGE / 8),
		cv::Point(SIZEIMAGE, SIZEIMAGE),
		cv::Scalar(0, 255, 255),
		cv::FILLED,
		cv::LINE_8);
	//![rectangle]

	/// 2.c. Create a few lines
	MyLine(RookImage, cv::Point(0, 15 * SIZEIMAGE / 16), cv::Point(SIZEIMAGE, 15 * SIZEIMAGE / 16));
	MyLine(RookImage, cv::Point(SIZEIMAGE / 4, 7 * SIZEIMAGE / 8), cv::Point(SIZEIMAGE / 4, SIZEIMAGE));
	MyLine(RookImage, cv::Point(SIZEIMAGE / 2, 7 * SIZEIMAGE / 8), cv::Point(SIZEIMAGE / 2, SIZEIMAGE));
	MyLine(RookImage, cv::Point(3 * SIZEIMAGE / 4, 7 * SIZEIMAGE / 8), cv::Point(3 * SIZEIMAGE / 4, SIZEIMAGE));
	//![draw_rook]

	/// 3. Display your stuff!
	imshow(atom_window, AtomImage);
	cv::moveWindow(atom_window, 0, 200);
	imshow(rook_window, RookImage);
	cv::moveWindow(rook_window, SIZEIMAGE, 200);

	cv::waitKey(0);
	return(0);
}



