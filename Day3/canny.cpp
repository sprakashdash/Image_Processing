#include <iostream>
#include <cmath>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
void caller(int ,void *data);

int l;
int h;
int main()
{
	l=h=0;
	Mat img = imread("rubik.jpg",0);
	namedWindow("edge",WINDOW_NORMAL);
	createTrackbar("lower","edge",&l,256,caller,&img);
	createTrackbar("upper","edge",&h,256,caller,&img);
	waitKey(0);
}

void caller(int ,void *data)
{
	Mat img1 = *((Mat*)data);
	Mat img2(img1.rows,img1.cols,CV_8UC1);
	Canny(img1,img2,l,h,3);
	imshow("edge",img2);
}