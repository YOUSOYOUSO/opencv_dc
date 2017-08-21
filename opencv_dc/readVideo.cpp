#include <iostream> 
#include "opencv2/opencv.hpp" 

using namespace std; using namespace cv;
int readVideo()
{

	//打开视频文件 
	VideoCapture cap("1.mp4");

	//检查是否成功打开 
	if (!cap.isOpened())
	{
		cerr << "Can not open a camera or file." << endl;
		return -1;
	}

	Mat edges;     //创建窗口 
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		//从cap中读一帧，存到frame 
		cap >> frame;         
		//如果未读到图像 
		if (frame.empty()) {
			break;
		}
		//将读到的图像转为灰度图 
		cvtColor(frame, edges, CV_BGR2GRAY);
		//进行边缘提取操作 
		Canny(edges, edges, 0, 123, 3);
		//显示结果       
		imshow("edges", edges);
		waitKey(100);

	}
	return 0;
}
