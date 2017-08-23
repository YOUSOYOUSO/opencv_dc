#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#define threshold_diff 20

using namespace std;
using namespace cv;

int QianJingTQ()
{
	//打开视频文件：其实就是建立一个VideoCapture结构
	VideoCapture capture("1.mp4");
	//检测是否正常打开:成功打开时，isOpened返回ture
	if (!capture.isOpened())
	{
		cout << "fail to open!" << endl;
		return -1;
	}
	//获取整个帧数
	long totalFrameNumber = capture.get(CV_CAP_PROP_FRAME_COUNT);
	cout << "整个视频共" << totalFrameNumber << "帧" << endl;

	//设置开始帧()
	long frameToStart = 1;
	capture.set(CV_CAP_PROP_POS_FRAMES, frameToStart);
	cout << "从第" << frameToStart << "帧开始读" << endl;

	//设置结束帧
	int frameToStop = 1270;

	if (frameToStop < frameToStart)
	{
		cout << "结束帧小于开始帧，程序错误，即将退出！" << endl;
		return -1;
	}
	else
	{
		cout << "结束帧为：第" << frameToStop << "帧" << endl;
	}

	//获取帧率
	double rate = capture.get(CV_CAP_PROP_FPS);
	cout << "帧率为:" << rate << endl;

	//定义一个用来控制读取视频循环结束的变量
	bool stop = false;
	//承载每一帧的图像
	Mat frame;
	//显示每一帧的窗口
	namedWindow("Extracted frame", 1);
	//承载每一帧的图像以及灰度化后的图像
	Mat img_src1, img_src2, img_dst, gray1, gray2, gray_diff;
	//显示前景提取后的窗口
	namedWindow("foreground", 2);
	//两帧间的间隔时间:
	int delay = 1000 / rate;
	//滤波器的核
	int kernel_size = 3;
	Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
	//利用for循环读取帧
	//当前帧是设定的开始帧
	//currentFrame是在循环体中控制读取到指定的帧后循环结束的变量
	for(long currentFrame = frameToStart;currentFrame<= frameToStop;currentFrame++)
	{
		//读取下一帧
		if (!capture.read(frame))
		{
			cout << "读取视频失败" << endl;
			return -1;
		}
		cout << "正在读取第" << currentFrame << "帧" << endl;
		imshow("Extracted frame", frame);
		//前景提取
		//获取前一帧图像
		capture >> img_src1;
		//滤波
		filter2D(img_src1, img_src1, -1, kernel);
		//灰度化
		cvtColor(img_src1, gray1, CV_BGR2GRAY);
		//形态学处理（包括腐蚀，膨胀，开闭运算）
		// 如果把结构元素设置为Mat()，则将用默认的3*3的矩形结构元素
		Mat eroded;
		erode(gray1, eroded, Mat());
		Mat dilated;
		dilate(gray1, dilated, Mat());
		//定义结构元素
		Mat sa(5, 5, CV_8U, Scalar(1));
		Mat closed;
		morphologyEx(gray1, closed, MORPH_CLOSE, sa);
		Mat opened;
		morphologyEx(gray1, opened, MORPH_OPEN, sa);
		waitKey(5);
		//获取后一帧图像
		capture >> img_src2;
		//滤波
		filter2D(img_src2, img_src2, -1, kernel);
		//灰度化
		cvtColor(img_src2, gray2, CV_BGR2GRAY);
		//形态学处理（包括腐蚀，膨胀，开闭运算）
		// 如果把结构元素设置为Mat()，则将用默认的3*3的矩形结构元素
	    eroded;
		erode(gray2, eroded, Mat());
		dilated;
		dilate(gray2, dilated, Mat());
		// 定义结构元素
	    Mat sb(5, 5, CV_8U, Scalar(1));
		closed;
		morphologyEx(gray2, closed, MORPH_CLOSE, sb);
		opened;
		morphologyEx(gray2, opened, MORPH_OPEN, sb);
		waitKey(5);
		//背景差发后一帧减前一帧得到移动物体
		subtract(gray1, gray2, gray_diff);
		for (int i = 0; i<gray_diff.rows; i++)
			for (int j = 0; j<gray_diff.cols; j++)
				if (abs(gray_diff.at<unsigned char>(i, j)) >= threshold_diff)//这里模板参数一定要用unsigned char，否则就一直报错
					gray_diff.at<unsigned char>(i, j) = 255;
				else gray_diff.at<unsigned char>(i, j) = 0;
				//设置阈值
				threshold(gray_diff, gray_diff, 255 * (0.5), 255, THRESH_BINARY);
				// 再进行一次形态学处理
				eroded;
				erode(gray_diff, eroded, Mat());
				dilated;
				dilate(gray_diff, dilated, Mat());
				// 定义结构元素
				Mat sc(5, 5, CV_8U, Scalar(1));
				closed;
				morphologyEx(gray_diff, closed, MORPH_CLOSE, sc);
				opened;
				morphologyEx(gray_diff, opened, MORPH_OPEN, sc);
				//显示前景物体
				imshow("foreground", gray_diff);
				//刷新图像	
				//waitKey(int delay=0)当delay ≤ 0时会永远等待；当delay>0时会等待delay毫秒
				waitKey(delay);
	}
	//关闭视频文件
	capture.release();
	waitKey(0);
	return 0;
}