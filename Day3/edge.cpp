#include <iostream>
#include <cmath>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

Mat gradient_y(Mat img);
void disp(int , void*);
Mat gradient_x(Mat img);

int t;
int main()
{
	t=0;
	Mat img = imread("rubik.jpg",0);
	imshow("original",img);
	namedWindow("edges",WINDOW_NORMAL);
	// Mat img2 = gradient_x(img);
	// Mat img3 = gradient_y(img);
	// Mat a[2];
	// a[0] = img2; a[1]=img3;
	createTrackbar("strong","edges",&t,256,disp,&img);
	waitKey(0);

}

void disp(int , void* data)
{

	Mat img1 = gradient_x(*(Mat*)data);
	Mat img2 = gradient_y(*(Mat*)data);
	Mat img(img1.rows,img1.cols,CV_8UC1,Scalar(0));
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			int a = fabs(img1.at<uchar>(i,j));
			int b = fabs(img2.at<uchar>(i,j)); 
			if(a + b > t)
				img.at<uchar>(i,j) = 255;
		}
	}
	imshow("edges",img);
}

Mat gradient_x(Mat img)
{
	Mat img2(img.rows,img.cols,CV_8UC1);
	for(int i=0;i<img.rows-2;i++){
		for(int j=0;j<img.cols-2;j++){
			int a=0;
			for(int k=0;k<3;k++){
				for(int l=0;l<3;l++){
					if(k==0){
						a+= img.at<uchar>(i+l,j+k)*(-1);
						// if(l==1)
							// a-=img.at<uchar>(i+l,j+k);
					}
					else if(k==2){
						a+= img.at<uchar>(i+l,j+k);
						// if(l==1)
							// a+=img.at<uchar>(i+l,j+k);
					}
				}
			}

			if(a<0)
				img2.at<uchar>(i+1,j+1) = 0;
			else if(a>255)
				img2.at<uchar>(i+1,j+1) = 255;
			else img2.at<uchar>(i+1,j+1) = a;
		}
	}
	return img2;
}

Mat gradient_y(Mat img)
{
	Mat img2(img.rows,img.cols,CV_8UC1);
	for(int i=0;i<img.rows-2;i++){
		for(int j=0;j<img.cols-2;j++){
			int a=0;
			for(int k=0;k<3;k++){
				for(int l=0;l<3;l++){
					if(k==0){
						a+= img.at<uchar>(i+k,j+l)*(-1);
						// if(l==1)
							// a-=img.at<uchar>(i+k,j+l);
					}
					else if(k==2){
						a+= img.at<uchar>(i+k,j+l);
						// if(l==1)
							// a+=img.at<uchar>(i+k,j+l);
					}
				}
			}
			if(a<0)
				img2.at<uchar>(i+1,j+1) = 0;
			else if(a>255)
				img2.at<uchar>(i+1,j+1) = 255;
			else img2.at<uchar>(i+1,j+1) = a;
		}
	}
	return img2;
}