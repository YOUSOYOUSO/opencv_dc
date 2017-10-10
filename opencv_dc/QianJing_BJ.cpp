#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include "cv.h"
#include <math.h>
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include "opencv2/core/core.hpp"
#include <opencv\ml.h>
#include <iostream>
#include "highgui.h"
#include <vector>
#include <string.h>
#include <fstream>

using namespace cv;
using namespace std;

void chao_thinimage(Mat &srcimage);

int QianJing_BJ() {
	IplImage* pFrame = NULL;//视频中截取的一帧
	IplImage* pFrImg = NULL;//当前帧的灰度图
	IplImage* pBkImg = NULL;//当前背景的灰度图
	IplImage* pFrameTemp = NULL;

	CvMat* pFrameMat = NULL;//当前灰度矩阵
	CvMat* pFrMat = NULL;//当前前景图矩阵
	CvMat* pBkMat = NULL;//当前背景图矩阵


						 //形态学处理时内核大小
	IplConvKernel* Element = cvCreateStructuringElementEx(13, 13, 1, 1, CV_SHAPE_RECT, NULL);

	//轮廓边缘提取时的参数
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* contour = 0;//可动态增长元素序列
	int mode = CV_RETR_EXTERNAL;//只检索最外面的轮廓

								//在视频中画出感兴趣的区域
	CvPoint pt1, pt2, pt3, pt4, pt5;//pt3,pt4为轮廓矩阵的左下右上
	pt1.x = 292;//视频左下点
	pt1.y = 100;
	pt2.x = 412;//视频右上点
	pt2.y = 280;
	//用cvBoundingRect画出外接矩形时需要的矩形
	CvRect bndRect = cvRect(0, 0, 0, 0);
	//运动对象中心坐标
	int avgX = 0;
	int avgY = 0;


	//视频捕获
	CvCapture* pCapture = NULL;
	//图像的帧数
	int nFramNum = 0;

	//创建窗口
	cvNamedWindow("video", 1);
	cvNamedWindow("foreground", 1);
	cvMoveWindow("video", 30, 0);
	cvMoveWindow("foreground", 690, 0);

	pCapture = cvCaptureFromFile("7.mp4");
	//pFrame = cvQueryFrame(pCapture);


	pFrameTemp = cvQueryFrame(pCapture);
	pFrame = cvCreateImage(cvGetSize(pFrameTemp), 8, 3);//大小和pFrameTemp相同，8Bit深度3通道图像
	cvCopy(pFrameTemp, pFrame);//将所生成的临时帧复制到pFrame

							   //逐帧读取视频，cvQueryFrame从摄像头或者文件中抓取并返回一帧
	while (pFrameTemp = cvQueryFrame(pCapture)) {
		cvCopy(pFrameTemp, pFrame);
		nFramNum++;

		//如果是第一帧，申请内存并初始化
		if (nFramNum == 1) {
			pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);//8Bit深度，单通道图像
			pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height), IPL_DEPTH_8U, 1);
			pBkMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);//CV_32FC1 代表32位浮点型单通道矩阵
			pFrMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			pFrameMat = cvCreateMat(pFrame->height, pFrame->width, CV_32FC1);
			cvCvtColor(pFrame, pBkImg, CV_BGR2GRAY);//转换成单通道灰度图
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
			cvConvert(pFrImg, pFrameMat);//转换成矩阵
			cvConvert(pFrImg, pFrMat);
			cvConvert(pFrImg, pBkMat);

		}

		else if (nFramNum >= 2) {
			cvCvtColor(pFrame, pFrImg, CV_BGR2GRAY);
			cvConvert(pFrImg, pFrameMat);
			//先高斯滤波平滑图像
			cvSmooth(pFrameMat, pFrameMat, CV_GAUSSIAN, 3, 0, 0);

			//在视频中设置并画ROI区域
			cvRectangle(pFrame, pt1, pt2, CV_RGB(255, 0, 0), 2, 8, 0);//线条亮度（255,0,0）为白色，粗细2，类型8

																	  //当前帧跟背景图相减，计算两个数组差的绝对值
			cvAbsDiff(pFrameMat, pBkMat, pFrMat);

			//二值化前景图
			cvThreshold(pFrMat, pFrImg, 60, 255.0, CV_THRESH_BINARY);//阈值函数，类型为CV_THRESH_BINARY 二值化

																	 //膨胀操作，内核为Element
			cvDilate(pFrImg, pBkImg, Element, 1);

			//通过查找边界找出ROI矩形区域内的运动车辆
			cvFindContours(pBkImg, storage, &contour, sizeof(CvContour), mode, CV_CHAIN_APPROX_SIMPLE);//二值图像中寻找轮廓

																									   //处理当前框架中移动的轮廓，用函数cvBoundingRect
			for (; contour != 0; contour = contour->h_next) {
				//获得运动车辆的矩形
				bndRect = cvBoundingRect(contour, 0);
				//获得运动轮廓的平均x坐标
				avgX = bndRect.x + (bndRect.width) / 2;
				avgY = bndRect.y + (bndRect.height) / 2;

				//如果轮廓中心点在ROI内，显示
				if (avgX > 300 && avgX < 400 && avgY<280 && avgY>100) {
					pt3.x = bndRect.x;
					pt3.y = bndRect.y;
					pt4.x = bndRect.x + bndRect.width;
					pt4.y = bndRect.y + bndRect.height;

					//去除较小的干扰矩阵
					if (bndRect.height>35 && 600<(bndRect.width*bndRect.height)<10000) {
						cvRectangle(pFrame, pt3, pt4, CV_RGB(255, 0, 0), 1, 8, 0);
					}
				}
			}//查找边界for结束

			 //更新背景//////////////////////

			 //输入图像或序列-用于累加的图像或序列-移动平均时第一个空image所占的权重-操作符掩码
			cvRunningAvg(pFrameMat, pBkMat, 0.005, 0);//将pFrameMat累加到pBkMat
													  //将背景转换成图像格式，用以显示
			cvConvert(pBkMat, pBkImg);

			//显示图像///////////////////////
			cvShowImage("video", pFrame);
			cvShowImage("foreground", pFrImg);
			cvShowImage("background", pBkImg);


			//如果有按键操作，则等待
			if (cvWaitKey(2) >= 0)
				break;

		}
		waitKey(50);
	}//while循环结束
	 //删除结构元素
	cvReleaseStructuringElement(&Element);
	//销毁窗口
	cvDestroyWindow("video");
	cvDestroyWindow("background");
	cvDestroyWindow("foreground");

	//释放图像和矩阵
	cvReleaseImage(&pFrImg);
	cvReleaseImage(&pBkImg);

	cvReleaseMat(&pFrameMat);
	cvReleaseMat(&pFrMat);
	cvReleaseMat(&pBkMat);
	return 0;
}