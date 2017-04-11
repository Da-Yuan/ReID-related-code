// Main.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Saliency.h"  

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>  

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Saliency sal;

	Mat src = imread("./xr.jpg");

	if (src.empty()) return -1;

	vector<unsigned int >imgInput;
	vector<double> imgSal;

	//Mat to vector
	int nr = src.rows; // number of rows  
	int nc = src.cols; // total number of elements per line  
	if (src.isContinuous()) {
		// then no padded pixels  
		nc = nc*nr;
		nr = 1;  // it is now a 1D array  
	}

	for (int j = 0; j<nr; j++) {
		uchar* data = src.ptr<uchar>(j);
		for (int i = 0; i<nc; i++) {
			unsigned int t = 0;
			t += *data++;
			t <<= 8;
			t += *data++;
			t <<= 8;
			t += *data++;
			imgInput.push_back(t);
			
		}                
	}

	sal.GetSaliencyMap(imgInput, src.cols, src.rows, imgSal);

	//vector to Mat
	int index0 = 0;
	Mat imgout(src.size(), CV_64FC1);
	for (int h = 0; h < src.rows; h++) {
		double* p = imgout.ptr<double>(h);
		for (int w = 0; w < src.cols; w++) {
			*p++ = imgSal[index0++];
		}
	}
	normalize(imgout, imgout, 0, 1, NORM_MINMAX);
	
	imshow("原图像", src);
	imshow("显著性图像", imgout);

	waitKey(0);
	
	return  0;
}
