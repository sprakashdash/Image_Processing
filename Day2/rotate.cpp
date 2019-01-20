#include <iostream>
#include <cmath>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
void rotate(int size, void *data);
void median_blur(Mat img);

int t;
int main()
{
	t=0;
	Mat img = imread("test.jpg",1);
	namedWindow("rotation",WINDOW_NORMAL);
	createTrackbar("angle","rotation",&t,360,rotate,&img);
	imshow("rotation",img);
	waitKey(0);
}

void rotate(int size, void *data)
{
	double theta = ((double)t/180)*3.14159;
	Mat* img = (Mat*)data;
	int a = sqrt(img->rows*img->rows + img->cols*img->cols);
	Mat img2(a,a,CV_8UC3,Scalar(0,0,0));
	for(int i=0;i<img->rows;i++){
		for(int j=0;j<img->cols;j++){
			int p = i - img->rows/2;
			int q = j - img->cols/2;
			int x =  ((double)p)*cos(theta) + ((double)q)*sin(theta);
			int y = (-(double)p)*sin(theta) + ((double)q)*cos(theta);
			for(int k=0;k<3;k++){
				img2.at<Vec3b>(x+a/2,y+a/2)[k] = img->at<Vec3b>(i,j)[k];
			}
		}
	}
	imshow("rotation",img2);

}
