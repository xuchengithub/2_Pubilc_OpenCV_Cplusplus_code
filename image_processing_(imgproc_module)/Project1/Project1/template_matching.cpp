#include <opencv2/opencv.hpp>
#include"template_matching.h"

cv::Mat Img; cv::Mat Templ; cv::Mat Mask; cv::Mat Result;
bool use_mask;
int match_method;
int max_Trackbar = 5;
extern const char* kTemplate_Matching_ImageWindow = "Source Image";
extern const char* kTemplate_Matching_kResultWindow = "Result window";


int TemplateMatching(int argc, char** argv)
{
	if (argc < 3)
	{
		std::cout << "Not enough parameters" << std::endl;
		std::cout << "Usage:\n" << argv[0] << " <image_name> <template_name> [<mask_name>]" << std::endl;
		return -1;
	}
	Img = cv::imread(argv[1], cv::IMREAD_COLOR);
	Templ = cv::imread(argv[2], cv::IMREAD_COLOR);
	if (argc > 3) {
		use_mask = true;
		Mask = cv::imread(argv[3], cv::IMREAD_COLOR);
	}
	if (Img.empty() || Templ.empty() || (use_mask && Mask.empty()))
	{
		std::cout << "Can't read one of the images" << std::endl;
		return EXIT_FAILURE;
	}
	cv::namedWindow(kTemplate_Matching_ImageWindow, cv::WINDOW_AUTOSIZE);
	cv::namedWindow(kTemplate_Matching_kResultWindow, cv::WINDOW_AUTOSIZE);
	const char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
	cv::createTrackbar(trackbar_label, kTemplate_Matching_ImageWindow, &match_method, max_Trackbar, MatchingMethod);
	MatchingMethod(0, 0);
	cv::waitKey(0);
	return EXIT_SUCCESS;
}
void MatchingMethod(int, void*)
{
	cv::Mat img_display;
	Img.copyTo(img_display);
	int result_cols = Img.cols - Templ.cols + 1;
	int result_rows = Img.rows - Templ.rows + 1;
	Result.create(result_rows, result_cols, CV_32FC1);
	bool method_accepts_mask = (cv::TM_SQDIFF == match_method || match_method == cv::TM_CCORR_NORMED);
	if (use_mask && method_accepts_mask)
	{
		cv::matchTemplate(Img, Templ, Result, match_method, Mask);
	}
	else
	{
		cv::matchTemplate(Img, Templ, Result, match_method);
	}
	normalize(Result, Result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat());
	double min_val; double max_val; cv::Point min_loc; cv::Point max_loc;
	cv::Point MatchLoc;
	minMaxLoc(Result, &min_val, &max_val, &min_loc, &max_loc, cv::Mat());
	if (match_method == cv::TM_SQDIFF || match_method == cv::TM_SQDIFF_NORMED)
	{
		MatchLoc = min_loc;
	}
	else
	{
		MatchLoc = max_loc;
	}
	rectangle(img_display, MatchLoc, cv::Point(MatchLoc.x + Templ.cols, MatchLoc.y + Templ.rows), cv::Scalar::all(0), 2, 8, 0);
	rectangle(Result, MatchLoc, cv::Point(MatchLoc.x + Templ.cols, MatchLoc.y + Templ.rows), cv::Scalar::all(0), 2, 8, 0);
	imshow(kTemplate_Matching_ImageWindow, img_display);
	imshow(kTemplate_Matching_kResultWindow, Result);
	return;
}