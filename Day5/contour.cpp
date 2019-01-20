#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;
void caller(int t,void *data);


int main()
{
	int t=0;
	Mat img = imread("blue.png",0);
	namedWindow("orig",WINDOW_NORMAL);
	createTrackbar("threshold","orig",&t,255,caller,&img);
	waitKey(0);
}

void caller(int t,void *data)
{
	vector<vector<Point> >contours;
	vector<Vec4i>heirarchy;
	Mat img1 = *((Mat*)data);
	Mat img2(img1.rows,img1.cols,CV_8UC1);
	Canny(img1,img2,t,2*t,3);
	findContours(img2,contours,heirarchy,RETR_EXTERNAL,CHAIN_APPROX_NONE);
	Mat img3(img1.rows,img1.cols,CV_8UC1);
	for(int i=0;i<contours.size();i++){
		drawContours(img3,contours,i,255,2,8,heirarchy,1);
	}
	imshow("orig",img3);
	imwrite("contour.png",img3);
	exit(0);
}

