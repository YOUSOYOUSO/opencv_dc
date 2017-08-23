#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int BianYuanTQ()
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
	namedWindow("Extracted frame", 0);
	//承载每一帧边缘提取后的图像
	Mat edges;
	//显示边缘提取后的窗口
	namedWindow("edges", 1);
	int delay = 1000 / rate;
	//滤波器的核
	int kernel_size = 3;
	Mat kernel = Mat::ones(kernel_size, kernel_size, CV_32F) / (float)(kernel_size*kernel_size);
	//利用for循环读取帧
	//当前帧是设定的开始帧
	//currentFrame是在循环体中控制读取到指定的帧后循环结束的变量
	for (long currentFrame = frameToStart; currentFrame <= frameToStop; currentFrame++)
	{
		//读取下一帧
		if (!capture.read(frame))
		{
			cout << "读取视频失败" << endl;
			return -1;
		}
		//这里加滤波程序
		imshow("Extracted frame", frame);
		filter2D(frame, frame, -1, kernel);
		imshow("after filter", frame);
		cout << "正在读取第" << currentFrame << "帧" << endl;
		//进行边缘提取操作 
		cvtColor(frame, edges, CV_BGR2GRAY);
		Canny(edges, edges, 0, 123, 3);
		//显示边缘提取结果       
		imshow("edges", edges);
		//刷新图像	
		//waitKey(int delay=0)当delay ≤ 0时会永远等待；当delay>0时会等待delay毫秒
		waitKey(delay);
	}
	//关闭视频文件
	capture.release();
	waitKey(0);
	return 0;
}