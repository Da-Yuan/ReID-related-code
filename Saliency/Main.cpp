// Main.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "Saliency.h"  

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>//画图类

#include <iostream>

using namespace std;
using namespace cv;

void getHistImg(const Mat src, Mat &hist, Mat &histimg) {
	Mat hue;

	int hsize = 16;//直方图bin的个数
	float hranges[] = { 0,180 };
	const float* phranges = hranges;

	int ch[] = { 0, 0 };
	hue.create(src.size(), src.depth());
	mixChannels(&src, 1, &hue, 1, ch, 1);//得到H分量

	calcHist(&hue, 1, 0, Mat(), hist, 1, &hsize, &phranges);

	normalize(hist, hist, 0, 255, NORM_MINMAX);

	histimg = Scalar::all(0);
	int binW = histimg.cols / hsize;
	Mat buf(1, hsize, CV_8UC3);
	for (int i = 0; i < hsize; i++)
		buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
	cvtColor(buf, buf, COLOR_HSV2BGR);

	for (int i = 0; i < hsize; i++)
	{
		int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
		rectangle(histimg, Point(i*binW, histimg.rows),
			Point((i + 1)*binW, histimg.rows - val),
			Scalar(buf.at<Vec3b>(i)), -1, 8);
	}
}

void getSalHistImg(const Mat src, const Mat mask, Mat &hist, Mat &histimg) {
	Mat hue;

	int hsize = 16;//直方图bin的个数
	float hranges[] = { 0,180 };
	const float* phranges = hranges;

	int ch[] = { 0, 0 };
	hue.create(src.size(), src.depth());
	mixChannels(&src, 1, &hue, 1, ch, 1);//得到H分量

	calcHist(&hue, 1, 0, mask, hist, 1, &hsize, &phranges);

	normalize(hist, hist, 0, 255, NORM_MINMAX);

	histimg = Scalar::all(0);
	int binW = histimg.cols / hsize;
	Mat buf(1, hsize, CV_8UC3);
	for (int i = 0; i < hsize; i++)
		buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
	cvtColor(buf, buf, COLOR_HSV2BGR);

	for (int i = 0; i < hsize; i++)
	{
		int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
		rectangle(histimg, Point(i*binW, histimg.rows),
			Point((i + 1)*binW, histimg.rows - val),
			Scalar(buf.at<Vec3b>(i)), -1, 8);
	}
}

int main(int argc, char** argv)
{
	Saliency sal;

	Mat srcImage = imread("./3.jpg");
	Mat hist1,hist2;

	if (srcImage.empty()) return -1;

	vector<unsigned int >imgInput;
	vector<double> imgSal;

	//Mat to vector
	int nr = srcImage.rows; // number of rows  
	int nc = srcImage.cols; // total number of elements per line  
	if (srcImage.isContinuous()) {
		// then no padded pixels  
		nc = nc*nr;
		nr = 1;  // it is now a 1D array  
	}

	for (int j = 0; j<nr; j++) {
		uchar* data = srcImage.ptr<uchar>(j);
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

	sal.GetSaliencyMap(imgInput, srcImage.cols, srcImage.rows, imgSal);

	//vector to Mat
	int index0 = 0;
	Mat salImage(srcImage.size(), CV_64FC1);
	for (int h = 0; h < srcImage.rows; h++) {
		double* p = salImage.ptr<double>(h);
		for (int w = 0; w < srcImage.cols; w++) {
			*p++ = imgSal[index0++];
		}
	}
	normalize(salImage, salImage, 0, 1, NORM_MINMAX);
	Mat dst;
	threshold(salImage, dst, 0.2, 255, 0);
	dst.convertTo(dst, CV_8U);

	Mat srcHistImg = Mat::zeros(200, 300, CV_8UC3);
	Mat srcSalHistImg = Mat::zeros(200, 300, CV_8UC3);

	getHistImg(srcImage, hist1, srcHistImg);
	getSalHistImg(srcImage, dst, hist2, srcSalHistImg);
	Mat sumHist;
	sumHist = hist1 + hist2;


	imshow("原图像", srcImage);
	imshow("直方图", srcHistImg);
	imshow("显著区域直方图", srcSalHistImg);
	imshow("显著性图像", salImage);
	imshow("二值化", dst);

	waitKey(0);
	
	return  0;
}
