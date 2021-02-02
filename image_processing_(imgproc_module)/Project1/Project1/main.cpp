
//copyright:著作権
//	IMPORTANT : READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//	By downloading, copying, installing or using the software you agree to this license.
//	If you do not agree to this license, do not download, install,
//	copy or use the software.
//
//	License Agreement
//	For Open Source Computer Vision Library
//
//	Copyright(C) 2000 - 2008, Intel Corporation, all rights reserved.
//	Copyright(C) 2008 - 2009, Willow Garage Inc., all rights reserved.
//	Third party copyrights are property of their respective owners.
//
//	Redistribution and use in source and binary forms, with or without modification,
//	are permitted provided that the following conditions are met :
//
//		  *Redistribution's of source code must retain the above copyright notice,
//			  this list of conditions and the following disclaimer.
//
//			  * Redistribution's in binary form must reproduce the above copyright notice,
//			  this list of conditions and the following disclaimer in the documentation
//			  and/or other materials provided with the distribution.
//
//			  * The name of the copyright holders may not be used to endorse or promote products
//			  derived from this software without specific prior written permission.
//
//			  This software is provided by the copyright holders and contributors "as is" and
//			  any express or implied warranties, including, but not limited to, the implied
//			  warranties of merchantability and fitness for a particular purpose are disclaimed.
//			  In no event shall the Intel Corporation or contributors be liable for any direct,
//			  indirect, incidental, special, exemplary, or consequential damages
//			  (including, but not limited to, procurement of substitute goods or services;
//		  loss of use, data, or profits; or business interruption) however caused
//			  and on any theory of liability, whether in contract, strict liability,
//			  or tort(including negligence or otherwise) arising in any way out of
//			  the use of this software, even if advised of the possibility of such damage.
//
//			  license:ライセンス
//			  no license
//
//			  Author : XuChen
//
//			  This is a code cleanup of the OpenCV website tutorial
//			  これはOpenCVのウェブサイトのチュートリアルのコードの整理



//C++のファイル
//C++Files 



//Dos. h in C: Dos. h header file of C language contains functions for handling interrupts, producing sound,
//date and time functions etc. It is Borland specific and works in Turbo C compiler.
//CのDos.h：C言語のDos.hヘッダーファイルには、割り込みの処理、サウンドの生成、
//日付および時刻関数など。Borland固有であり、Turbo Cコンパイラで動作します。


#include <dos.h>


//input・output_function
//入出力機能

#include <iostream>

//In the C++ programming language, <sstream> is a part of the C++ Standard Library. It is a header file that 
//provides templates and types that enable interoperation between stream buffers and string objects.
//C ++プログラミング言語では、<sstream>はC ++標準ライブラリの一部です。 それはヘッダーファイルです
//ストリームバッファと文字列オブジェクト間の相互運用を可能にするテンプレートとタイプを提供します。

#include <sstream>

//The C++ function std::algorithm::includes() test whether first set is subset of another or not. This member
//function expects elements in sorted order. It use operator< for comparison.
//C ++関数std :: algorithm :: includes（）は、最初のセットが別のセットのサブセットかどうかをテストします。 このメンバー関数は、
//ソートされた順序で要素を予期します。 比較にはoperator <を使用します。

#include<algorithm>

//#include OpenCV
//
//
//その他のファイル
//Files created by this work
//No file

#include<opencv2/opencv.hpp>

//Data structure, matrix calculation, data type conversion, memory management, etc.
//データの構造、行列計算、データのタイプ変換、メモリー管理等
//
//この作業で作成したファイル
//Files created by this work

#include "all_filters.h"
#include "brief_simple_geometric_drawing.h"
#include "drawing_random_lines.h"
#include "dilation_erosion.h"
#include "more_morphology_transformations.h"
#include "hit_or_miss.h"
#include "extract_horizontal_and_vertical_lines_by_using_morphological_operations.h"
#include "gaussian_pyramid.h"
#include "basic_thresholding_operations.h"
#include "color_thresholding.h"
#include "adding_borders_to_your_images.h"
#include "make_your_own_filter.h"
#include "sobel_derivatives.h"
#include "laplace_derivatives.h"
#include "canny_function.h"
#include "hough_line_transform.h"
#include "affine_transformations.h"
#include "histogram_calculation.h"
#include "histogram_comparsion.h"
#include "backprojection.h"
#include "template_matching.h"
#include "finding_contours_in_your_image.h"
#include "convex_hull.h"
#include "creating_bounding_boxes_and_circles_for_contours.h"

int main(int argc, char** argv)
{
	
	int The_maximum_mode_that_can_be_selected = 30;
	std::string user_input_mode_string;

	int user_input_mode_num;
	int using_default_data_if_n_0_if_y_1;
	std::string address_date_const_cast;

	int num_put_data = argc;
	char *address_data_set_char[4] ;
	address_data_set_char[0] = argv[0];
//////////////////////////////////////モード選択/////////////////////////////////////////////////////
	
	for (;;)
	{
		if (num_put_data == 1)
		{
			std::cerr << "実行ファイルのアドレス" << std::endl;;
			std::cerr << argv[0] << std::endl;
			std::cerr << "==================================" << std::endl;//プログラムエラーが発生しても、出力する。
			std::cerr << "使い方：まず以下の<mode>（数字を入力）を選択してください" << std::endl;
			std::cout << "============= <mode> =============" << std::endl;
			std::cout << "1: brief_Simple_geometric_drawing" << std::endl;//作成した関数を使って、OpenCVの関数にパラメーターを入力し、円等を作成する。
			std::cout << "2: drawing_random_lines" << std::endl;
			std::cout << "3: all_filters" << std::endl;
			std::cout << "4: morphology_transformations" << std::endl;
			std::cout << "5: more_morphology_transformations" << std::endl;
			std::cout << "6: hit_or_miss" << std::endl;
			std::cout << "7: extract_horizontal_and_vertical_lines_by_using_morphological_operations" << std::endl;
			std::cout << "8: gaussian_pyramid" << std::endl;
			std::cout << "9: basic_thresholding_operations" << std::endl;
			std::cout << "10: color_thresholding" << std::endl;
			std::cout << "11: make_your_own_filter" << std::endl;
			std::cout << "12: adding_borders_to_your_images" << std::endl;
			std::cout << "13: sobel_derivatives" << std::endl;
			std::cout << "14: laplace_derivatives" << std::endl;
			std::cout << "15: canny_derivatives" << std::endl;
			std::cout << "16: hough_line_transform" << std::endl;
			std::cout << "17: affine_transformations" << std::endl;
			std::cout << "18: histogram_calculation" << std::endl;
			std::cout << "19: histogram_comparison" << std::endl;
			std::cout << "20: back_projection" << std::endl;
			std::cout << "21: template_matching" << std::endl;
			std::cout << "22: finding_contours_in_your_image" << std::endl;
			std::cout << "23: convex_hull" << std::endl;
			std::cout << "24: creating_bounding_boxes_and_circles_for_contours" << std::endl;
			std::cout << "=================================" << std::endl;

			std::cin >> user_input_mode_string;
			try {
				user_input_mode_num = std::stoi(user_input_mode_string);
			}
			catch (...) {
				user_input_mode_num = 0;
			}
			if (user_input_mode_num > 0 && user_input_mode_num < The_maximum_mode_that_can_be_selected)
			{
				break;
			}
			else
			{
				std::cout << "入力モードが間違いました。再入力してください" << std::endl;
			}
		}
	}
	std::cout << "以上のモードを選択された。" << std::endl;
	std::cout << "==============モード選択完了===================" << std::endl;
	std::cout << "好みのデータを入力しますか（Y/N or y/nを入力）。" << std::endl;

	////////////////////////////////////アドレスを入力/////////////////////////////////////////////////////////////////////////////////////
	for (;;)
	{
		std::string Whether_to_input_the_data_you_like;
		std::cin >> Whether_to_input_the_data_you_like;

		std::string y_str = "Y";
		std::string n_str = "N";

		try {
			std::transform(Whether_to_input_the_data_you_like.begin(),Whether_to_input_the_data_you_like.end(), Whether_to_input_the_data_you_like.begin(), ::toupper);
		}
		catch (...) {
		}

		if (Whether_to_input_the_data_you_like == y_str)
		{
			
			std::cout << "好みのデータの保存場所を入力してください" << std::endl;
			std::cin >> address_date_const_cast;
			address_data_set_char[1] = const_cast<char*>(address_date_const_cast.data());
			num_put_data = 2;
			std::cout << "好みのデータの保存場所は" << address_data_set_char[1] << std::endl;
			using_default_data_if_n_0_if_y_1 = 0;
			std::system("PAUSE");
			break;
		}
		else if (Whether_to_input_the_data_you_like == n_str)
		{
			std::cout << "===============================================" << std::endl;
			std::cout << "デフォルトデータを使用" << std::endl;
			std::cout << "===============================================" << std::endl;
			using_default_data_if_n_0_if_y_1 = 1;
			std::system("PAUSE");
			break;
		}
		else
		{
			std::cout << "入力が間違いました。再入力してください" << std::endl;
		}
	}

	////////////////////////////////////実行コード/////////////////////////////////////////////////////////////////////////////////////
	switch (user_input_mode_num) {
	case 1:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは各型の物を書く。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・line()関数を使って、線型を引く。" << std::endl;
		std::cout << "・ellipse()関数を使って、楕円形を書く。" << std::endl;
		std::cout << "・rectangle()関数を使って、矩形を作成する。" << std::endl;
		std::cout << "・circle()関数を使って、円を引く。" << std::endl;
		std::cout << "・fillPoly()関数を使って、各型のものを塗りつぶす。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明：" << std::endl;
		std::cout << "・操作できない。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズの説明:" << std::endl;
		std::cout << "・Drawing 1:Atom、Drawing 2:Rookウィンドウズに関数で作成した図。" << std::endl;
		std::cout << "===============================================" << std::endl;

		std::system("PAUSE");
		BriefSimpleGeometricDrawing();
		std::system("PAUSE");
		break;

	case 2:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはランダムに各色の線を作成する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・cv::RNGを使って、乱数を作成する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明：" << std::endl;
		std::cout << "・操作できない。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズの説明:" << std::endl;
		std::cout << "・Random_lineウィンドウズにランダムに各色の線を作成する。字をOpenCVのウィンドウズに書く。" << std::endl;
		std::cout << "===============================================" << std::endl;

		std::system("PAUSE");
		DrawingRandom();
		std::system("PAUSE");
		break;

	case 3:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは線型フィルターで画像をスムーズにする。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・blur()関数を使って、平均フィルターで画像処理する。" << std::endl;
		std::cout << "・GaussianBlur()関数を使って、カウスフィルターで画像処理する。" << std::endl;
		std::cout << "・medianBlur()関数を使って、中央値フィルタで画像処理する。" << std::endl;
		std::cout << "・bilateralFilter()関数を使って、バイラテラルフィルタで画像処理する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明：" << std::endl;
		std::cout << "・操作できない。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズの説明:" << std::endl;
		std::cout << "・Smoothing_Demoウィンドウズに、各フィルターを使って、画像処理した結果を示す。" << std::endl;
		std::cout << "===============================================" << std::endl;

		AllFilters(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 4:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは膨張と収縮で画像処理する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・cv::erode関数を使って、収縮処理する。" << std::endl;
		std::cout << "・cv::dilate関数を使って、膨張処理する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明とウィンドウズの説明：" << std::endl;
		std::cout << "・Erosion Demoのウィンドウズに、Elemen...seのトラックバーを使って、構造化要素を選択：" << std::endl;
		std::cout << "・0は矩形　1は十字の形　2は楕円形" << std::endl;
		std::cout << "・Erosion Demoのウィンドウズに、Kernel...+1のトラックバーを使って、フィルターのサイズの変更" << std::endl;
		std::cout << "・1番左は１サイズ　1番右は21サイズ" << std::endl;
		std::cout << "・Dilation Demo（収縮）のウィンドウズに、Elemen...seのトラックバーを使って、構造化要素を選択：" << std::endl;
		std::cout << "・0は矩形　1は十字の形　2は楕円形" << std::endl;
		std::cout << "・Dilation Demo（膨張）のウィンドウズに、Kernel...+1のトラックバーを使って、フィルターのサイズの変更" << std::endl;
		std::cout << "・1番左は１サイズ　1番右は21サイズ" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズの説明:" << std::endl;
		std::cout << "・Dilation Demoウィンドウズに膨張処理結果。Erosion Demoウィンドウズに収縮処理結果。" << std::endl;
		std::cout << "===============================================" << std::endl;
		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg" );
		}
		DilationErosion(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 5:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはOpening処理、Closing処理、morphological gradient処理、Top Hat処理、Black Hat処理を紹介します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・cv::morphologyEx関数を使って、各処理を選択して、画像処理。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明とウィンドウズの説明：" << std::endl;
		std::cout << "・操作の説明" << std::endl;
		std::cout << "・Morphology Transformaのウィンドウズに、Elemen...seのトラックバーを使って、構造化要素を選択：" << std::endl;
		std::cout << "・0は矩形　1は十字の形　2は楕円形" << std::endl;
		std::cout << "・Morphology Transformaのウィンドウズに、Kernel...+1のトラックバーを使って、フィルターのサイズの変更" << std::endl;
		std::cout << "・1番左は１サイズ　1番右は21サイズ" << std::endl;
		std::cout << "・Morphology Transformaのウィンドウズに、Operat...atのトラックバーを使って、処理を選択：" << std::endl;
		std::cout << "・0はOpening処理　1はClosing処理　2はmorphological_gradient処理　3はTop Hat処理　4はBlack Hat処理 " << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズの説明:" << std::endl;
		std::cout << "・Morphology Transformation Demoウィンドウズに各モードの処理結果を示す。" << std::endl;
		std::cout << "===============================================" << std::endl;
		if (using_default_data_if_n_0_if_y_1 == 1)
		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		MoreMorphologyTransformations(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 6:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはhit_miss理論を使って、二値画像に、特定な型の物を探す。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・cv::morphologyEx関数を使って、hit_miss画像処理する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;;
		std::cout << "・操作できない。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明：" << std::endl;
		std::cout << "・Originalウィンドウズに処理前の画像。kernalウィンドウズに目標Hit or Missウィンドウズに検出結果。白い画素の場所は検出された目標がいる場所。" << std::endl;
		std::cout << "===============================================" << std::endl;
		HitOrMiss();
		std::system("PAUSE");
		break;

	case 7:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは水平軸と垂直軸上の直線を抽出するために、カスタムカーネルを作成して、2つの非常に一般的な形態演算子（膨張と収縮）を適用します。この目的のために、erode()、dilate()、getStructuringElement()関数を使用します。" << std::endl << "この例の目的は楽譜から音符を抽出することが目標となる" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・erode()関数を使って、収縮処理する。" << std::endl;
		std::cout << "・dilate()関数を使って、膨張処理する。" << std::endl;
		std::cout << "・getStructuringElement()関数を使って、カスタムカーネルを作成する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・操作できない。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Srcウィンドウズに原画像。" << std::endl;
		std::cout << "・grayウィンドウズにグレー画像。" << std::endl;
		std::cout << "・binaryはウィンドウズ二値画像。horizontalウィンドウズに検出された横方向線型。" << std::endl;
		std::cout << "・Verticalウィンドウズに二値画像の縦方向の線。" << std::endl;
		std::cout << "・vertical_bitウィンドウズにverticalの反転画像。" << std::endl;
		std::cout << "・edgesウィンドウズに反転画像のエッジ画像。" << std::endl;
		std::cout << "・dilateウィンドウズにエッジを膨張した画像。" << std::endl;
		std::cout << "・smooth ウィンドウズにdilate画像とvertical画像を使って、作成したエッジが滑らかな画像。" << std::endl;			
		std::cout << "・vertical_bitはverticalの反転画像である。edgesは反転画像のエッジ画像である。dilateはエッジを膨張した画像である。smoothはdilate画像とvertical画像を使って、作成したエッジが滑らかな画像である。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\src.png");
		}
		ExtractHorizontalAndVerticalLinesByUsingMorphologicalOperations(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 8:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは画像ピラミッド。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・pyrUp()関数を使って、画像をアップサンプリングしてからぼかします。" << std::endl;
		std::cout << "・pyrDown()関数を使って、画像をぼかすとダウンサンプリングします。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・iを押すと大きくなる。oを押すと小さくする。ESCを押すとプログラムを消す。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・window_nameウィンドウズは原画像。この画像を使って、ピラミッドした画像もwindow_nameウィンドウズに示す。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		GaussianPyramid(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 9:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは閾値操作。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・cv::threshold関数を使って、画像に対して、基本閾値操作します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・閾値操作のタイプは5つあります。０はThreshold Binary、１はThreshold Binary, Inverted、２はTruncate、３はThreshold to Zero、４はThreshold to Zero, Inverted" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Threshold Demoウィンドウズに各閾値処理後の結果。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		BasicThresholdingOperations(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 10:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは色カメラを使って、閾値処理。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・cv::threshold関数を使って、画像に対して、基本閾値操作します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・Low Hは色相(Hue)の最小の閾値である。High Hは色相(Hue)の最大の閾値である。" << std::endl;
		std::cout << "・Low Sは彩度(Saturation・Chroma)の最小の閾値である。High Sは彩度(Saturation・Chroma)の最大の閾値である。 " << std::endl;
		std::cout << "・Low Vは明度(Value・Brightness)の最小の閾値である。High Vは明度(Value・Brightness)の最大の閾値である。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Video Captureウィンドウズにカメラを取った映像。Object Detectionウィンドウズに閾値処理した画像。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("");
		}
		ColorThresholding(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 11:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは自分のフィルターを作成して、画像処理する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・filter2D()を使って、画像に対して、フィルター処理操作します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・なし" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・filter2D Demoウィンドウズにフィルター処理した画像。フィルターのサイズによって、処理した結果が変化。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		MakeYourOwnFilter(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 12:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは画像に枠線を追加します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・copyMakeBorder()関数を使って、画像に対して、フィルター処理します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・ｃを押すと画像の枠線をランダムにします。" << std::endl;
		std::cout << "・ｒを押すと画像の枠線を画像の周辺の画像値による決めます。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・copyMakeBorder Demo ウィンドウズに結果画像。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		AddingBordersToYourImages(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 13:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはkernal sobelを使って画像のエッジ検出。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・Sobel()関数を使って、画像に対して、画像から導関数を計算します。" << std::endl;
		std::cout << "・Sobel()関数を使って、画像に対して、サイズ3 * 3のカーネルのより正確な導関数を計算します" << std::endl; 
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・Dを押すと、フィルターのサイズの値が大きくなる。。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Sobel Demo ウィンドウズにエッジ画像。" << std::endl;
		std::cout << "===============================================" << std::endl;
		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		SobelDerivatives(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 14:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはkernal laplaceを使って画像のエッジ検出。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・Laplacian() 関数を使って、画像に対して、画像から導関数を計算します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・なし" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Laplace Demo ウィンドウズにエッジ画像。" << std::endl;
		std::cout << "===============================================" << std::endl;
		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		LaplaceDerivatives(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 15:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはkernal cannyを使って画像のエッジ検出。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・canny() 関数を使って、画像に対して、画像から導関数を計算します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・cannyの下限閾値を大きく調整すると、細かいエッジ検出が検出できなくなった。。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Edge Mapウィンドウズにエッジ画像。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		CannyDerivatives(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 16:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはhough transformを使って、直線検出。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・２種類のハフf変換HoughLines()、HoughLinesP()関数を使って、画像に対して、画像から導関数を計算。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・なし。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Sourceウィンドウズに原画像、Detected Line(in red)-Standard Hough Line Transformウィンドウズに普通のハフ変換で検出された直線、Detected Line(in red)-Probabilistic Line Transformウィンドウズに確率Hough線変換の結果。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
		}
		HoughLineTransform(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 17:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは画像の空間的な変換について、説明" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・OpenCV関数cv::warpAffineを使用して、簡単な再マッピングルーチンを実装。" << std::endl;
		std::cout << "・OpenCV関数cv::getRotationMatrix2Dを使用して、回転行列。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・なし。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Source imageウィンドウズに原画像、Warpウィンドウズに画像をワープした結果、Warp+Rotateに画像をワープ、回転した結果。" << std::endl;
		std::cout << "===============================================" << std::endl;

		AffineTransformations(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;


	case 18:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは画像のヒストグラムを作成について説明" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・OpenCV関数cv :: splitを使用して、画像を対応するプレーンに分割します。" << std::endl;
		std::cout << "・OpenCV関数cv :: calcuHistを使用して、画像のヒストグラムを作成。" << std::endl;
		std::cout << "・OpenCV関数cv :: normalizeを使用して、画像のデータを正規化。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・なし。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Source imageウィンドウズに原画像、calcHist DemoウィンドウズにRGBのヒストグラム" << std::endl;
		std::cout << "===============================================" << std::endl;

		HistogramCalculation(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 19:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルはさまざまなメトリックを使用してヒストグラムを比較。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・関数cv::compareHistを使用して、2つのヒストグラムがどの程度一致するかを表す数値パラメーターを取得します。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・なし。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・ユーザインタフェースに、画像のヒストグラムの4つの比較結果。1は画像自身の比較結果、2は画像と半分画像の比較結果、3は画像とその他の画像の比較結果、4は画像とその他の画像の比較結果" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");
			address_data_set_char[2] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h1.jpg");
			address_data_set_char[3] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h2.jpg");
			num_put_data = 4;
		}

		HistogramComparison(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 20:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・このチュートリアルは逆投影とは何で、なぜ有用なのか" << std::endl;
		std::cout << "・逆投影は、特定の画像のピクセルがヒストグラムモデルのピクセルの分布にどの程度適合するかを記録する方法です。より簡単にするには：逆投影の場合、フィーチャのヒストグラムモデルを計算し、それを使用して画像内でこのフィーチャを見つけます。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "・OpenCV関数cv::calcBackProjectを使用して逆投影を計算。" << std::endl;
		std::cout << "・OpenCV関数cv::mixChannelsを使用して、画像の異なるチャンネルを混合する。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・Binの数が増えると、画像をbinの数分に分ける。。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Source imageウィンドウズに原画像、Backprojウィンドウズにbackprojectionの結果画像、Histogramにヒストグラム。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\h0.jpg");

		}
		BackProjection(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 21:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・画像パッチと入力画像の間の一致を検索" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "OpenCV関数matchTemplate（）を使用して、画像パッチと入力画像の間の一致を検索します" << std::endl;
		std::cout << "OpenCV関数minMaxLoc（）を使用して、特定の配列内の最大値と最小値（およびその位置）を見つけます" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・0はTM_SQDIFF　1はSQDIFF NORMED 2はTM CCORR 3はTM CCORR NORMED 4はTM COEFF 5はTM COEFF NORMED。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Source imageウィンドウズに原画像と検出結果、Result windowウィンドウズに、類似度を計算して、黒いところは類似度が高いところ。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\T0.jpg");
			address_data_set_char[2] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\T1.jpg");
			num_put_data = 3;
		}
		TemplateMatching(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 22:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・画像のエッジを検出し、色付き" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "cv :: findContoursを使って、エッジ検出" << std::endl;
		std::cout << "cv :: drawContoursを使って、色付き" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・cannyの下限閾値を大きく調整すると、細かいエッジ検出が検出できなくなった。。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Sourceウィンドウズに原画像、Contoursウィンドウズに色付きエッジ画像。" << std::endl;
		std::cout << "===============================================" << std::endl;

		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\T0.jpg");
		}
		FindingContoursInYourImage(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;

	case 23:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "・画像の凸包を計算" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "cv::convexHullを使って、画像の凸包を計算" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・cannyの下限閾値を大きく調整すると、細かいエッジ検出が検出できなくなった。。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Sourceウィンドウズに原画像、Contoursウィンドウズに色付き画像の凸包画像。" << std::endl;
		std::cout << "===============================================" << std::endl;
		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\T0.jpg");
		}
		ConvexHull(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;
	case 24:
		std::cout << "===============================================" << std::endl;
		std::cout << "コード目的：" << std::endl;
		std::cout << "検出物を枠で表示" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "コードに学んだ関数：" << std::endl;
		std::cout << "cv::boundingRectは最小の直立境界四角形を計算して返す" << std::endl;
		std::cout << "cv::minEnclosingCircleは反復アルゴリズムを使用して、2Dポイントセットの最小包囲円を見つけます。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "操作の説明" << std::endl;
		std::cout << "・cannyの下限閾値を大きく調整すると、細かいエッジ検出が検出できなくなった。。" << std::endl;
		std::cout << "===============================================" << std::endl;
		std::cout << "ウィンドウズ説明" << std::endl;
		std::cout << "・Sourceウィンドウズに原画像、Contoursウィンドウズに色付きエッジ画像とエッジ画像の枠（矩形、円）。" << std::endl;
		std::cout << "===============================================" << std::endl;
		if (using_default_data_if_n_0_if_y_1 == 1)
		{
			address_data_set_char[1] = const_cast<char*>("\\\\uran\\各開発部\\第三開発部\\４研修\\１オフィス研修報告資料\\１９２６キョ_シン\\OpenCV\\OpenCV4_tutorial(作成中)\\image_processing_(imgproc_module)\\Project1\\Project1\\image\\T0.jpg");
		}
		CreatingBoundingBoxesAndCirclesForContours(num_put_data, address_data_set_char);
		std::system("PAUSE");
		break;
	}
	return 0;
};