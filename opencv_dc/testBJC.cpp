#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int testBJC()
{
	Mat test1 = imread("test1.png");
	Mat background;
	Mat temp;
	Mat result;
	VideoCapture capture("7.mp4");
	capture.read(background);

	resize(background, background, Size(300, 200));//resize为300*200的图像，原来是720*480
	cvtColor(background, background, CV_RGB2GRAY);//转为灰度图

	resize(test1, test1, Size(300, 200));//resize为300*200的图像，原来是720*480
	cvtColor(test1, test1, CV_RGB2GRAY);//转为灰度图

	absdiff(background, test1, result);//和背景作差

	//遍历图像，二值化，阈值为50
	for (int i = 0; i < result.rows; i++) {
		for (int j = 0; j < result.cols; j++) {
			if (result.at<uchar>(i, j)<50) {
				result.at<uchar>(i, j) = 0;
			}
			else {
				result.at<uchar>(i, j) = 255;
			}

		}
	}
	imshow("result",result);

	waitKey(0);
	return 0;
}