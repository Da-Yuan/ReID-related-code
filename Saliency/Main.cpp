// Main.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Saliency.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void main()
{
	// Assume we already have an unsigned integer buffer inputImg of
	// inputWidth and inputHeight (in row-major order).
	// Each unsigned integer has 32 bits and contains pixel data in ARGB
	// format. I.e. From left to right, the first 8 bits contain alpha
	// channel value and are not used in our case. The next 8 bits
	// contain R channel value; the next 8 bits contain G channel value;
	// the last 8 bits contain the B channel value.
	//
	// Now create a Saliency object and call the GetSaliencyMap function on it.

	Saliency sal;
	vector<double> salmap(0);
	sal.GetSaliencyMap(inputImg, inputWidth, inputHeight, salmap);

	// salmap is a floating point output (in row major order)
}