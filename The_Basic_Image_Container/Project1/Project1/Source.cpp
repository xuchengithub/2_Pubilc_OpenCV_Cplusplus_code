#include <opencv2/opencv.hpp>//
#include <iostream>//入出力機能
#include <opencv2/core.hpp>//データの構造、行列計算、データのタイプ変換、メモリー管理等
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"//OpenCV图像输入和输出
#include <opencv2/highgui.hpp>//GUI
#include <sstream>
#include <opencv2/imgproc.hpp>//画像プリンター等

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace cv;
using namespace std;
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;
//////////////////////////////////////////////////////Changing_the_contrast_and_brightness_of_an_image///////////////////////////////////////////////////////////////////////////
/**
 * @function main
 * @brief Main function
 */
int Changing_the_contrast_and_brightness_of_an_image(int argc, char** argv)
{
	/// Read image given by user
	//! [basic-linear-transform-load]
	//画像を読み込み
	CommandLineParser parser(argc, argv, "{@input | lena.jpg | input image}");
	Mat image = imread(samples::findFile(parser.get<String>("@input")));
	//画像を読み込みの結果
	if (image.empty())
	{
		cout << "Could not open or find the image!\n" << endl;
		cout << "Usage: " << argv[0] << " <Input image>" << endl;
		return -1;
	}
	//! [basic-linear-transform-load]

	//! [basic-linear-transform-output]
	Mat new_image = Mat::zeros(image.size(), image.type());
	//! [basic-linear-transform-output]

	//! [basic-linear-transform-parameters]
	double alpha = 1.0; /*< Simple contrast control */
	int beta = 0;       /*< Simple brightness control */

	/// Initialize values
	cout << " Basic Linear Transforms " << endl;
	cout << "-------------------------" << endl;
	cout << "* Enter the alpha value [1.0-3.0]: "; cin >> alpha;
	cout << "* Enter the beta value [0-100]: ";    cin >> beta;
	//! [basic-linear-transform-parameters]

	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	/// Instead of these 'for' loops we could have used simply:
	/// image.convertTo(new_image, -1, alpha, beta);
	/// but we wanted to show you how to access the pixels :)
	//! [basic-linear-transform-operation]
	for (int y = 0; y < image.rows; y++) {
		for (int x = 0; x < image.cols; x++) {
			for (int c = 0; c < image.channels(); c++) {
				new_image.at<Vec3b>(y, x)[c] =//3つのUintデータ
					saturate_cast<uchar>(alpha*image.at<Vec3b>(y, x)[c] + beta);
			}
		}
	}
	//! [basic-linear-transform-operation]

	//! [basic-linear-transform-display]
	/// Show stuff
	imshow("Original Image", image);
	imshow("New Image", new_image);

	/// Wait until the user press a key
	waitKey();
	//! [basic-linear-transform-display]
	return 0;
}

/////////////////////////////////////////////////scan_image_objects_in_OpenCV////////////////////////////////////////////////////////////////////////////////
int Mat_The_Basic_Image_Container(const std::string& filename)
{
//Mat型の基本知識と操作
//hear（アドレス）が同じの関数
Mat A, C;                                // creates just the header parts
A = imread(filename, IMREAD_COLOR);  // here we'll know the method used (allocate matrix)
cv::Mat B(A);                                // Use the copy constructor
//一部のデータを取り出す
Mat D(A, Rect(10, 10, 20, 20));      // using a rectangle一部の画像
Mat E = A(Range::all(),Range(1, 3)); // using row and column boundaries
C = A;  
Mat F = A.clone();
Mat G;
A.copyTo(G);// Assignment operator

//Mat型のデータを作成
Mat M(2, 2, CV_8UC3, Scalar(0, 0, 255));
cout << "M = " << endl << " " << M << endl << endl;
//The example shows how to create a matrix with more than two dimensions. Specify its dimension, then pass a pointer containing the size for each dimension and the rest remains the same.
int sz[3] = { 2,2,2 };
Mat L(3, sz, CV_8UC(1), Scalar::all(0));

M.create(4, 4, CV_8UC(2));
cout << "M = " << endl << " " << M << endl << endl;
Mat E1 = Mat::eye(4, 4, CV_64F);
cout << "E = " << endl << " " << E1 << endl << endl;
Mat O = Mat::ones(2, 2, CV_32F);
cout << "O = " << endl << " " << O << endl << endl;
Mat Z = Mat::zeros(3, 3, CV_8UC1);
cout << "Z = " << endl << " " << Z << endl << endl;

Mat C1 = (Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
cout << "C1 = " << endl << " " << C1 << endl << endl;
C1 = (Mat_<double>({ 0, -1, 0, -1, 5, -1, 0, -1, 0 })).reshape(3);
cout << "C1 = " << endl << " " << C1 << endl << endl;
Mat RowClone = C1.row(1).clone();
cout << "RowClone = " << endl << " " << RowClone << endl << endl;

//OpenCVでそのほかのデータの出力
Point2f P(5, 1);
cout << "Point (2D) = " << P << endl << endl;
Point3f P3f(2, 6, 7);
cout << "Point (3D) = " << P3f << endl << endl;

return 0;
}

/////////////////////////////////////////////////Mat_The_Basic_Image_Container//////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//画像処理加速するため、スキャン処理方法
static void help()
{
	cout
		<< "\n--------------------------------------------------------------------------" << endl
		<< "This program shows how to scan image objects in OpenCV (cv::Mat). As use case"
		<< " we take an input image and divide the native color palette (255) with the " << endl
		<< "input. Shows C operator[] method, iterators and at function for on-the-fly item address calculation." << endl
		<< "Usage:" << endl
		<< "./how_to_scan_images <imageNameToUse> <divideWith> [G]" << endl
		<< "if you add a G parameter the image is processed in gray scale" << endl
		<< "--------------------------------------------------------------------------" << endl
		<< endl;
}

Mat& ScanImageAndReduceC(Mat& I, const uchar* table);
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* table);
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar * table);

int scan_image_objects_in_OpenCV(int argc, char**argv)
{
	help();
	if (argc < 3)
	{
		cout << "Not enough parameters" << endl;
		return -1;
	}

	Mat I, J;
	if (argc == 4 && !strcmp(argv[3], "G"))
		I = imread(argv[1], IMREAD_GRAYSCALE);
	else
		I = imread(argv[1], IMREAD_COLOR);

	if (I.empty())
	{
		cout << "The image" << argv[1] << " could not be loaded." << endl;
		return -1;
	}

	//! [dividewith]
	int divideWith = 0; // convert our input string to number - C++ style
	stringstream s;
	s << argv[2];
	s >> divideWith;
	if (!s || !divideWith)
	{
		cout << "Invalid number entered for dividing. " << endl;
		return -1;
	}

	uchar table[256];
	for (int i = 0; i < 256; ++i)
		table[i] = (uchar)(divideWith * (i / divideWith));
	//! [dividewith]

	const int times = 100;
	double t;

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone();
		J = ScanImageAndReduceC(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Time of reducing with the C operator [] (averaged for "
		<< times << " runs): " << t << " milliseconds." << endl;

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone();
		J = ScanImageAndReduceIterator(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Time of reducing with the iterator (averaged for "
		<< times << " runs): " << t << " milliseconds." << endl;

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
	{
		cv::Mat clone_i = I.clone();
		ScanImageAndReduceRandomAccess(clone_i, table);
	}

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Time of reducing with the on-the-fly address generation - at function (averaged for "
		<< times << " runs): " << t << " milliseconds." << endl;

	//! [table-init]
	Mat lookUpTable(1, 256, CV_8U);
	uchar* p = lookUpTable.ptr();
	for (int i = 0; i < 256; ++i)
		p[i] = table[i];
	//! [table-init]

	t = (double)getTickCount();

	for (int i = 0; i < times; ++i)
		//! [table-use]
		LUT(I, lookUpTable, J);
	//! [table-use]

	t = 1000 * ((double)getTickCount() - t) / getTickFrequency();
	t /= times;

	cout << "Time of reducing with the LUT function (averaged for "
		<< times << " runs): " << t << " milliseconds." << endl;
	return 0;
}

//! [scan-c]
Mat& ScanImageAndReduceC(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	int channels = I.channels();

	int nRows = I.rows;
	int nCols = I.cols * channels;

	if (I.isContinuous())
	{
		nCols *= nRows;
		nRows = 1;
	}

	int i, j;
	uchar* p;
	for (i = 0; i < nRows; ++i)
	{
		p = I.ptr<uchar>(i);
		for (j = 0; j < nCols; ++j)
		{
			p[j] = table[p[j]];
		}
	}
	return I;
}
//! [scan-c]

//! [scan-iterator]
Mat& ScanImageAndReduceIterator(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		MatIterator_<uchar> it, end;
		for (it = I.begin<uchar>(), end = I.end<uchar>(); it != end; ++it)
			*it = table[*it];
		break;
	}
	case 3:
	{
		MatIterator_<Vec3b> it, end;
		for (it = I.begin<Vec3b>(), end = I.end<Vec3b>(); it != end; ++it)
		{
			(*it)[0] = table[(*it)[0]];
			(*it)[1] = table[(*it)[1]];
			(*it)[2] = table[(*it)[2]];
		}
	}
	}

	return I;
}
//! [scan-iterator]

//! [scan-random]
Mat& ScanImageAndReduceRandomAccess(Mat& I, const uchar* const table)
{
	// accept only char type matrices
	CV_Assert(I.depth() == CV_8U);

	const int channels = I.channels();
	switch (channels)
	{
	case 1:
	{
		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
				I.at<uchar>(i, j) = table[I.at<uchar>(i, j)];
		break;
	}
	case 3:
	{
		Mat_<Vec3b> _I = I;

		for (int i = 0; i < I.rows; ++i)
			for (int j = 0; j < I.cols; ++j)
			{
				_I(i, j)[0] = table[_I(i, j)[0]];
				_I(i, j)[1] = table[_I(i, j)[1]];
				_I(i, j)[2] = table[_I(i, j)[2]];
			}
		I = _I;
		break;
	}
	}

	return I;
}
//! [scan-random]

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////mat_mask_operations////////////////////////////////////////////////////////////////////////////

static void help(char* progName)
{
	cout << endl
		<< "This program shows how to filter images with mask: the write it yourself and the"
		<< "filter2d way. " << endl
		<< "Usage:" << endl
		<< progName << " [image_path -- default lena.jpg] [G -- grayscale] " << endl << endl;
}

void Sharpen(const Mat& myImage, Mat& Result);

int mat_mask_operations(int argc, char* argv[])
{
	help(argv[0]);
	const char* filename = argc >= 2 ? argv[1] : "lena.jpg"; //if?前の式は真の場合は？後ろの最初の式をやる。ではない場合は？後ろの最後の式をやる

	Mat src, dst0, dst1;

	if (argc >= 3 && !strcmp("G", argv[2]))
		src = imread(samples::findFile(filename), IMREAD_GRAYSCALE);
	else
		src = imread(samples::findFile(filename), IMREAD_COLOR);

	if (src.empty())
	{
		cerr << "Can't open image [" << filename << "]" << endl;
		return EXIT_FAILURE;
	}

	namedWindow("Input", WINDOW_AUTOSIZE);
	namedWindow("Output", WINDOW_AUTOSIZE);

	imshow("Input", src);
	double t = (double)getTickCount();

	Sharpen(src, dst0);

	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Hand written function time passed in seconds: " << t << endl;

	imshow("Output", dst0);
	waitKey();

	//![kern]//
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	//![kern]

	t = (double)getTickCount();

	//![filter2D]
	filter2D(src, dst1, src.depth(), kernel);
	//![filter2D]
	t = ((double)getTickCount() - t) / getTickFrequency();
	cout << "Built-in filter2D time passed in seconds:     " << t << endl;

	imshow("Output", dst1);

	waitKey();
	return EXIT_SUCCESS;
}

//! [basic_method]
void Sharpen(const Mat& myImage, Mat& Result)
{
	//! [8_bit]
	CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images読み込みのデータはCV８Uですか
  //! [8_bit]

  //! [create_channels]
	const int nChannels = myImage.channels();
	Result.create(myImage.size(), myImage.type());
	//! [create_channels]

	//! [basic_method_loop]
	for (int j = 1; j < myImage.rows - 1; ++j)
	{
		const uchar* previous = myImage.ptr<uchar>(j - 1);//行
		const uchar* current = myImage.ptr<uchar>(j);
		const uchar* next = myImage.ptr<uchar>(j + 1);

		uchar* output = Result.ptr<uchar>(j);

		for (int i = nChannels; i < nChannels*(myImage.cols - 1); ++i)//列
		{
			*output++ = saturate_cast<uchar>(5 * current[i]
				- current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
		}
	}
	//! [basic_method_loop]

	//! [borders]
	Result.row(0).setTo(Scalar(0));
	Result.row(Result.rows - 1).setTo(Scalar(0));
	Result.col(0).setTo(Scalar(0));
	Result.col(Result.cols - 1).setTo(Scalar(0));
	//! [borders]
}
//////////////////////////////////////////////////////////imread_image_and_Check_edge///////////////////////////////////////////////////////////////////////

int imread_image_and_Check_edge(int argc, char* argv[]){
Mat img = imread(argv[1]);
Mat grey;
cvtColor(img, grey, COLOR_BGR2GRAY);
Mat sobelx;
Sobel(grey, sobelx, CV_32F, 1, 0);
double minVal, maxVal;
minMaxLoc(sobelx, &minVal, &maxVal); //find minimum and maximum intensities//勾配が一番大きいと一番小さいな値を探す
Mat draw;
sobelx.convertTo(draw, CV_8U, 255.0 / (maxVal - minVal), -minVal * 255.0 / (maxVal - minVal));//勾配を画像に変換する。
namedWindow("image", WINDOW_AUTOSIZE);
imshow("image", draw);
waitKey();
return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////Adding_two_images_using_OpenCV////////////////////////////////////////////////////////////////////////////////

/**
 * @file AddingImages.cpp
 * @brief Simple linear blender ( dst = alpha*src1 + beta*src2 )
 * @author OpenCV team
 */
// we're NOT "using namespace std;" here, to avoid collisions between the beta variable and std::beta in c++17
using std::cin;
using std::cout;
using std::endl;

/**
 * @function main
 * @brief Main function
 */
int Adding_two_images_using_OpenCV(int argc,char** argv)
{
	double alpha = 0.5; double beta; double input;

	Mat src1, src2, dst;

	/// Ask the user enter alpha
	cout << " Simple Linear Blender " << endl;
	cout << "-----------------------" << endl;
	cout << "* Enter alpha [0.0-1.0]: ";
	cin >> input;

	// We use the alpha provided by the user if it is between 0 and 1
	if (input >= 0 && input <= 1)
	{
		alpha = input;
	}

	//![load]
	//Read images ( both have to be of the same size and type )
	src1 = imread(samples::findFile("LinuxLogo.jpg"));
	src2 = imread(samples::findFile("WindowsLogo.jpg"));
	//![load]

	if (src1.empty()) { cout << "Error loading src1" << endl; return EXIT_FAILURE; }
	if (src2.empty()) { cout << "Error loading src2" << endl; return EXIT_FAILURE; }

	//![blend_images]
	beta = (1.0 - alpha);
	addWeighted(src1, alpha, src2, beta, 0.0, dst);
	//![blend_images]

	//![display]
	imshow("Linear Blend", dst);
	waitKey(0);
	//![display]

	return 0;
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////discrete Fourier transform////////////////////////////////////////
using namespace cv;
using namespace std;

static void help(char ** argv)
{
	cout << endl
		<< "This program demonstrated the use of the discrete Fourier transform (DFT). " << endl
		<< "The dft of an image is taken and it's power spectrum is displayed." << endl << endl
		<< "Usage:" << endl
		<< argv[0] << " [image_name -- default lena.jpg]" << endl << endl;
}

int discrete_Fourier_transform(int argc, char ** argv)
{
	help(argv);

	const char* filename = argc >= 2 ? argv[1] : "lena.jpg";

	Mat I = imread(samples::findFile(filename), IMREAD_GRAYSCALE);
	if (I.empty()) {
		cout << "Error opening image" << endl;
		return EXIT_FAILURE;
	}
	////////////////////////////////////////////////////画像のサイズを調整する////////////////////////////////////////////////////////////
	//! [expand]
	Mat padded;                            //expand input image to optimal size
	int m = getOptimalDFTSize(I.rows);//フーリエ変換に対して、一番いい、サイズに変換
	int n = getOptimalDFTSize(I.cols); // on the border add zero values
	//C++: void copyMakeBorder(InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const Scalar& value=Scalar() 
	copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));//００００すると、増やせない。ｎ周の価を増やす。外ｎ周の価を０にする
	//! [expand]
	//! [complex_and_real]
	////////////////////////////////////////////////////同じサイズの画像で周波数の画像を保存////////////////////////////////////////////////////////////
	Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };//１層
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros//１層に２層を加えて
//! [complex_and_real]
	//フーリエ変換
//! [dft]
	dft(complexI, complexI);            // this way the result may fit in the source matrix          //dft(input　image ,output image)
//! [dft]

	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
//! [magnitude]
	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude　　　//input = planes[0],output =plances[1]、結果はplane[0]に保存、ベクトルを計算
	Mat magI = planes[0];
	//! [magnitude]

	//価の範囲が大きすぎるため、logで範囲を小さくする。
	//! [log]
	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);
	//! [log]
	//最初に増えるデータを削除し
	//! [crop_rearrange]
		// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
	//データを整える。
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols / 2;
	int cy = magI.rows / 2;

	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);

	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
	//! [crop_rearrange]
	//正規化
	//! [normalize]
	normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a　　　　　
											// viewable image form (float between values 0 and 1).
//! [normalize]

	imshow("Input Image", I);    // Show the result
	imshow("spectrum magnitude", magI);
	waitKey();

	return EXIT_SUCCESS;
}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class MyData//自分でデータ型を定義する
{
public:
	MyData() : A(0), X(0), id()
	{}
	explicit MyData(int) : A(97), X(CV_PI), id("mydata1234") //コストラクタ関数 explicit to avoid implicit conversion　　　CV_PIは角度１度の価　explicit隠れるコストラクタ関数を防ぐため
	{}
	//! [inside]
	void write(FileStorage& fs) const                        //Write serialization for this class
	{
		fs << "{" << "A" << A << "X" << X << "id" << id << "}";
	}
	void read(const FileNode& node)                          //Read serialization for this class
	{
		A = (int)node["A"];
		X = (double)node["X"];
		id = (string)node["id"];
	}
	//! [inside]
public:   // Data Members
	int A;
	double X;
	string id;
};

//These write and read functions must be defined for the serialization in FileStorage to work
//! [outside]
///////////////////////////////////////////////////////////////////////ｍはあたらいでーた型であるため、Mを入力し、overloadで自動検出し、この関数を使う。
static void write(FileStorage& fs, const std::string&, const MyData& x)
{
	x.write(fs);
}
static void read(const FileNode& node, MyData& x, const MyData& default_value = MyData()) {
	if (node.empty())
		x = default_value;
	else
		x.read(node);
}
//! [outside]

// This function will print our custom class to the console
static ostream& operator<<(ostream& out, const MyData& m)
{
	out << "{ id = " << m.id << ", ";
	out << "X = " << m.X << ", ";
	out << "A = " << m.A << "}";
	return out;
}

int  OpenCV_serialization_functionality(int ac, char** av)
{
	if (ac != 2)
	{
		//help(av);
		return 1;
	}

	string filename = av[1];
	{ //write
		//! [iomati]
		Mat R = Mat_<uchar>::eye(3, 3),
			T = Mat_<double>::zeros(3, 1);
		//! [iomati]
		//! [customIOi]
		MyData m(1);//explicit MyData(int) : A(97), X(CV_PI), id("mydata1234")
		//! [customIOi]

		//! [open]
		FileStorage fs(filename, FileStorage::WRITE);
		// or:
		// FileStorage fs;
		// fs.open(filename, FileStorage::WRITE);
		//! [open]

		//! [writeNum]
		fs << "iterationNr" << 100;
		//! [writeNum]
		//! [writeStr]
		fs << "strings" << "[";                              // text - string sequence
		fs << "image1.jpg" << "Awesomeness" << "../data/baboon.jpg";
		fs << "]";                                           // close sequence
		//! [writeStr]

		//! [writeMap]
		fs << "Mapping";                              // text - mapping
		fs << "{" << "One" << 1;
		fs << "Two" << 2 << "}";
		//! [writeMap]

		//! [iomatw]
		fs << "R" << R;                                      // cv::Mat
		fs << "T" << T;
		//! [iomatw]

		//! [customIOw]
		fs << "MyData" << m;                                // your own data structures
		//! [customIOw]

		//! [close]
		fs.release();                                       // explicit close
		//! [close]
		cout << "Write Done." << endl;
	}

	{//read
		cout << endl << "Reading: " << endl;
		FileStorage fs;
		fs.open(filename, FileStorage::READ);

		//! [readNum]
		int itNr;
		//fs["iterationNr"] >> itNr;
		itNr = (int)fs["iterationNr"];
		//! [readNum]
		cout << itNr;
		if (!fs.isOpened())
		{
			cerr << "Failed to open " << filename << endl;
		//help(av);
			return 1;
		}

		//! [readStr]
		FileNode n = fs["strings"];                         // Read string sequence - Get node
		if (n.type() != FileNode::SEQ)
		{
			cerr << "strings is not a sequence! FAIL" << endl;
			return 1;
		}

		FileNodeIterator it = n.begin(), it_end = n.end(); // Go through the node
		for (; it != it_end; ++it)
			cout << (string)*it << endl;
		//! [readStr]


		//! [readMap]
		n = fs["Mapping"];                                // Read mappings from a sequence
		cout << "Two  " << (int)(n["Two"]) << "; ";
		cout << "One  " << (int)(n["One"]) << endl << endl;
		//! [readMap]


		MyData m;
		Mat R, T;

		//! [iomat]
		fs["R"] >> R;                                      // Read cv::Mat
		fs["T"] >> T;
		//! [iomat]
		//! [customIO]
		fs["MyData"] >> m;                                 // Read your own structure_
		//! [customIO]

		cout << endl
			<< "R = " << R << endl;
		cout << "T = " << T << endl << endl;
		cout << "MyData = " << endl << m << endl << endl;

		//Show default behavior for non existing nodes
		//! [nonexist]
		cout << "Attempt to read NonExisting (should initialize the data structure with its default).";
		fs["NonExisting"] >> m;
		cout << endl << "NonExisting = " << endl << m << endl;
		//! [nonexist]
	}

	cout << endl
		<< "Tip: Open up " << filename << " with a text editor to see the serialized data." << endl;

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//! [mandelbrot-escape-time-algorithm]
int mandelbrot(const complex<float> &z0, const int max) //式による、否か判定、500回循環で式を４により多くなるのか。なるとｔを返す。
{
	complex<float> z = z0; //複素数
	for (int t = 0; t < max; t++)
	{
		if (z.real()*z.real() + z.imag()*z.imag() > 4.0f) return t;
		z = z * z + z0;
	}

	return max;
}
//! [mandelbrot-escape-time-algorithm]
//! [mandelbrot-grayscale-value]//escape-timeを使って、イメージ図を作成
int mandelbrotFormula(const complex<float> &z0, const int maxIter = 500) {
	//最大重複回数を500にする。
	int value = mandelbrot(z0, maxIter);
	if (maxIter - value == 0)//500回で４より多くない場合は０にする。mandeセットと判明する。
	{
		return 0;
	}

	return cvRound(sqrt(value / (float)maxIter) * 255);
	//mandeセットしゃないと判明する回数、画素値とする。
}
//! [mandelbrot-grayscale-value]

//! [mandelbrot-parallel]//parallel実験
class ParallelMandelbrot : public ParallelLoopBody
{
public:
	ParallelMandelbrot(Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
		: m_img(img), m_x1(x1), m_y1(y1), m_scaleX(scaleX), m_scaleY(scaleY)
	{
	}

	virtual void operator ()(const Range& range) const CV_OVERRIDE
	{
		for (int r = range.start; r < range.end; r++)
		{
			int i = r / m_img.cols;
			int j = r % m_img.cols;

			float x0 = j / m_scaleX + m_x1;
			float y0 = i / m_scaleY + m_y1;

			complex<float> z0(x0, y0);
			uchar value = (uchar)mandelbrotFormula(z0);
			m_img.ptr<uchar>(i)[j] = value;
		}
	}

	ParallelMandelbrot& operator=(const ParallelMandelbrot &) {
		return *this;
	};

private:
	Mat &m_img;
	float m_x1;
	float m_y1;
	float m_scaleX;
	float m_scaleY;
};
//! [mandelbrot-parallel]

//! [mandelbrot-sequential]
void sequentialMandelbrot(Mat &img, const float x1, const float y1, const float scaleX, const float scaleY)
{
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			float x0 = j / scaleX + x1;//縮小
			float y0 = i / scaleY + y1;

			complex<float> z0(x0, y0);//複素数
			uchar value = (uchar)mandelbrotFormula(z0);
			img.ptr<uchar>(i)[j] = value;//輝度値
		}
	}
}
//! [mandelbrot-sequential]

int OpenCV_parallel_for_to_parallelize_your_code()
{
	//! [mandelbrot-transformation]
	Mat mandelbrotImg(4800, 5400, CV_8U);
	float x1 = -2.1f, x2 = 0.6f;	
	float y1 = -1.2f, y2 = 1.2f;
	float scaleX = mandelbrotImg.cols / (x2 - x1);
	float scaleY = mandelbrotImg.rows / (y2 - y1);
	//! [mandelbrot-transformation]

	double t1 = (double)getTickCount();

#ifdef CV_CXX11

	//! [mandelbrot-parallel-call-cxx11]
	parallel_for_(Range(0, mandelbrotImg.rows*mandelbrotImg.cols), [&](const Range& range) {
		for (int r = range.start; r < range.end; r++)
		{
			int i = r / mandelbrotImg.cols;
			int j = r % mandelbrotImg.cols;

			float x0 = j / scaleX + x1;
			float y0 = i / scaleY + y1;

			complex<float> z0(x0, y0);//画素の位置
			uchar value = (uchar)mandelbrotFormula(z0);//ZOの位置の価
			mandelbrotImg.ptr<uchar>(i)[j] = value;//画像に入力
		}
	});
	//! [mandelbrot-parallel-call-cxx11]

#else

	//! [mandelbrot-parallel-call]
	ParallelMandelbrot parallelMandelbrot(mandelbrotImg, x1, y1, scaleX, scaleY);
	parallel_for_(Range(0, mandelbrotImg.rows*mandelbrotImg.cols), parallelMandelbrot);
	//! [mandelbrot-parallel-call]

#endif

	t1 = ((double)getTickCount() - t1) / getTickFrequency();
	cout << "Parallel Mandelbrot: " << t1 << " s" << endl;

	Mat mandelbrotImgSequential(4800, 5400, CV_8U);
	double t2 = (double)getTickCount();
	sequentialMandelbrot(mandelbrotImgSequential, x1, y1, scaleX, scaleY);
	t2 = ((double)getTickCount() - t2) / getTickFrequency();
	cout << "Sequential Mandelbrot: " << t2 << " s" << endl;
	cout << "Speed-up: " << t2 / t1 << " X" << endl;

	imwrite("Mandelbrot_parallel.png", mandelbrotImg);
	imwrite("Mandelbrot_sequential.png", mandelbrotImgSequential);

	return EXIT_SUCCESS;
}
/////////////////////////////////////////////////////////////////////////!

/////////////////////////////////////////////////////////////////////////!

int main(int argc, char** argv) {
	std::string filename = "";
	std::cerr << "USAGE: " << std::endl;//プログラムエラーしても、出力する。
	std::cerr << argv[0] << std::endl;
	std::cerr << "<mode> [<filename]" << std::endl;
	std::cout << "======== <mode> ========" << std::endl;
	std::cout << "1: Mat_The_Basic_Image_Container" << std::endl;
	std::cout << "2: scan_image_objects_in_OpenCV" << std::endl;
	std::cout << "3: Changing_the_contrast_and_brightness_of_an_image" << std::endl;
	std::cout << "4: mat_mask_operations" << std::endl;
	std::cout << "5: imread_image_and_Check_edge" << std::endl;
	std::cout << "6: Adding_two_images_using_OpenCV" << std::endl;
	std::cout << "7: discrete_Fourier_transform" << std::endl;
	std::cout << "8: OpenCV_serialization_functionality" << std::endl;
	std::cout << "9: OpenCV_parallel_for_to_parallelize_your_code" << std::endl;

	int mode;
	switch (argc) {
	case 1:
		mode = 0;
		std::cout << "<mode> [<filename]" << std::endl;
		std::cin >> mode >> filename;
		break;

	case 2:
		mode = (std::atoi(argv[1]));
		if ( mode == 9 )
		{
			break;
		}
		else
		{
		std::cout << "[<filename]" << std::endl;
		//std::cin >> filename;
		break;
		}

	case 3:
		filename = argv[2];
		mode = std::atoi(argv[1]);//atoi は string を int にする。
		break;

	default:
		std::cout << "入力が間違いました。" << std::endl;
		std::system("PAUSE");
		break;
	}

	switch (mode) {
	case 1:
		if (argc == 2){
			filename = "C:\\opencv\\sources\\samples\\data\\aero1.jpg";
		}
		Mat_The_Basic_Image_Container(filename);
		std::system("PAUSE");
		break;

	case 2:
		if (argc == 2) {
			argv[1] = const_cast<char*>("C:\\Users\\tome\\Desktop\\tutorial_how_matrix_stored_2.png");
		    argv[2] = const_cast<char*>("10");
			argv[3] = const_cast<char*>("G");
			argc = 4;
		}
		scan_image_objects_in_OpenCV(argc, argv);
		std::system("PAUSE");
		break;

	case 3:
		if (argc == 2) {
			argv[1] = const_cast<char*>("C:\\Users\\tome\\Desktop\\tutorial_how_matrix_stored_2.png");
		}
		Changing_the_contrast_and_brightness_of_an_image(argc, argv);
		std::system("PAUSE");
		break;

	case 4:
		if (argc == 2) {
			argv[1] = const_cast<char*>("C:\\Users\\tome\\Desktop\\tutorial_how_matrix_stored_2.png");
			argv[2] = const_cast<char*>("G");
			argc = 3;
		}
		mat_mask_operations(argc, argv);
		std::system("PAUSE");
		break;

	case 5:
		imread_image_and_Check_edge(argc, argv);
		break;

	case 6:
		if (argc == 2) {
			argv[1] = const_cast<char*>("C:\\Users\\tome\\Desktop\\tutorial_how_matrix_stored_2.png");
		
		}
		Adding_two_images_using_OpenCV(argc, argv);
		break;

	case 7:
		if (argc == 2) {
			argv[1] = const_cast<char*>("C:\\Users\\tome\\Desktop\\tutorial_how_matrix_stored_2.png");
		}
		discrete_Fourier_transform(argc, argv);
		break;

	case 8:
		if (argc == 2) {
			argv[1] = const_cast<char*>("C:\\Users\\tome\\Desktop\\u889.yml");
		}
		OpenCV_serialization_functionality(argc, argv);
		std::system("PAUSE");
		break;

	case 9:
		OpenCV_parallel_for_to_parallelize_your_code();
		std::system("PAUSE");
		break;

	default://もしも値は以上の値ではない場合はbreakする。
		cout << "値を確認してください" << endl;
		std::system("PAUSE");
		break;
	}
	return 0;
}
