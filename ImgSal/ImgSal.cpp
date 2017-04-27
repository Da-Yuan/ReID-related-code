// ImgSal.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>
#include <string>

#include "Saliency.h"

using namespace cv;

int main(int argc, char* argv[])
{
	Mat sal;
	Mat img3f = imread("./1.jpg");
	imshow("cvv", img3f);
	img3f.convertTo(img3f, CV_32FC3, 1.0 / 255);

	sal = Saliency::GetRC(img3f);

	imshow("cv", sal);
	waitKey(0);

	return 0;
}
