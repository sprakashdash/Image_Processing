#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

void rotate(int t, void* data)
{
	int i,j;
	Mat* img2=((Mat*)data),img=imread("a.png",1),img1;
	img1=*img2;
	for(i=-img.rows/2;i<img.rows/2;i++)
		for(j=-img.cols/2;j<img.cols/2;j++)
			img1.at<Vec3b>(i*cos(t*3.1416/180)-j*sin(t*3.1416/180)+img1.rows/2,i*cos(t*3.1416/180)+j*sin(t*3.1416/180)+img1.cols/2)=img.at<Vec3b>(i+img.rows/2,j+img.cols/2);
	imshow("rotate",img1);
}

int main()
{
	int t=0;
	Mat img=imread("a.png",1),img1(sqrt((img.rows*img.rows)+(img.cols*img.cols)),sqrt((img.rows*img.rows)+(img.cols*img.cols)),CV_8UC3);
	namedWindow("rotate",WINDOW_NORMAL);
	createTrackbar("degree","rotate",&t,180,rotate,&img1);
	waitKey(0);
	
	
	return 0;
}