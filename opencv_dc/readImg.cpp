#include <iostream> 
#include "opencv2/opencv.hpp" 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
using namespace std; 
using namespace cv;

int readImg()
{
	//读入图像，并将之转为单通道图像 
	Mat im1 = imread("1.png", 0);
	if (im1.empty())
	{
		cout << "Can not load image." << endl;        
			return -1;
	}
	namedWindow("1");		// 在窗口中显示游戏原画    
	imshow("1", im1);			// 等待6000 ms后窗口自动关闭    
	waitKey(2000);
	return 0;
}