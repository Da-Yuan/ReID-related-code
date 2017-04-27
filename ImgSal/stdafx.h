// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once
#pragma warning(disable: 4996)
#pragma warning(disable: 4819)

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO:  在此处引用程序需要的其他头文件
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <time.h>
#include <queue>
#include <omp.h>
#include <Windows.h>
using namespace std;


// OpenCV
#include <cvaux.h>
#include <highgui.h>
#ifdef _DEBUG
#pragma comment(lib, "opencv_world320d.lib")
#else
#pragma comment(lib, "opencv_world320.lib")
#endif // _DEBUG
using namespace cv;

typedef vector<string> vecS;
typedef vector<int> vecI;
typedef vector<float> vecF;
typedef vector<double> vecD;
typedef pair<double, int> CostIdx;
typedef pair<float, int> CostfIdx;

#include "Segmentation/segment-image.h"

template<typename T> inline T sqr(T x) { return x * x; }
template<class T> inline T vecDist3(const Vec<T, 3> &v1, const Vec<T, 3> &v2) { return sqrt(sqr(v1[0] - v2[0]) + sqr(v1[1] - v2[1]) + sqr(v1[2] - v2[2])); }
template<class T> inline T vecSqrDist3(const Vec<T, 3> &v1, const Vec<T, 3> &v2) { return sqr(v1[0] - v2[0]) + sqr(v1[1] - v2[1]) + sqr(v1[2] - v2[2]); }
template<class T1, class T2> inline void operator /= (Vec<T1, 3> &v1, const T2 v2) { v1[0] /= v2; v1[1] /= v2; v1[2] /= v2; }
template<class T> inline T pntSqrDist(const Point_<T> &p1, const Point_<T> &p2) { return sqr(p1.x - p2.x) + sqr(p1.y - p2.y); }


#define CV_Assert_(expr, args) \
{\
	if(!(expr)) {\
	string msg = cv::format args; \
	CmLog::LogError("%s in %s:%d\n", msg.c_str(), __FILE__, __LINE__); \
	cv::error(cv::Exception(CV_StsAssert, msg, __FUNCTION__, __FILE__, __LINE__) ); }\
}