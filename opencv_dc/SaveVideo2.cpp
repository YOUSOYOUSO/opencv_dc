#include <iostream>  
#include <opencv2/opencv.hpp>  


using namespace std;
using namespace cv;


int saveVideo2()
{
	Mat in_frame, out_frame;
	double fps = 30;
	char file_out[] = "recorded.avi";
	int i = 0;

	VideoCapture cap("2.mp4");//打开默认摄像机，videocapture函数还可以用来打开视频文件：VideoCapture(const string &filename)  
	if (!cap.isOpened())
	{
		cout << "Can not open a capture object." << endl;
		return -1;
	}

	//获取输入视频每一帧的宽度和高度  
	int width = (int)cap.get(CAP_PROP_FRAME_WIDTH);
	int height = (int)cap.get(CAP_PROP_FRAME_HEIGHT);
	VideoWriter recVid(file_out, VideoWriter::fourcc('M', 'P', '4', '2'), fps, Size(width, height),0);
	// MSVC是微软视频，仅可在Windows上解码使用，还可选择MJPG,PIM1，FLV1等  
	if (!recVid.isOpened())
	{
		cout << "Error!Video File is not open...\n";
	}

	while (cap.read(in_frame))
	{
		
		cvtColor(in_frame, out_frame, COLOR_BGR2GRAY);
		out_frame.convertTo(out_frame, CV_8U);
		recVid << out_frame; // 将转换后的灰度图写入视频文件  
		cout << i++ <<endl;
	}
	cap.release();
	return 0;
}