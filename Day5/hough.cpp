#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <cmath>

using namespace std;
using namespace cv;

Mat img = imread("pentagon.png");
void hough(Mat img2,int i,int j);
void lines(Mat img2);

int main()
{
	Mat img2(2*(img.rows+img.cols),360,CV_8UC1,Scalar(0));
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			if(img.at<uchar>(i,j)==255)
				hough(img2,i,j);
		}
	}
	namedWindow("hough_transform",WINDOW_NORMAL);
	imshow("hough_transform",img2);
	lines(img2);
	waitKey(0);
}

void hough(Mat img2,int i,int j)
{
	for(int k=0;k<360;k++){
		int r = ((float)i)*cos((k/360.0)*2*3.14) + ((float)j)*sin((k/360.0)*2*3.14);
		// if(r>= -(img.rows+img.cols) && r<(img.rows+img.cols))
			img2.at<uchar> (r+img.rows+img.cols,k)+=10;
	}
}

void lines(Mat img2)
{
	Mat img3(img.rows,img.cols,CV_8UC1);
	int pts = 0;
	for(int i=0;i<img2.rows;i++){
		for(int j=0;j<img2.cols;j++){
			if(img2.at<uchar>(i,j)>0){
				for(int x=0;x<img.rows;x++){
				// int x = i*cos((j*3.14)/180.0);
					int y = ((float)i-(float)x*cos(((float)j*3.14)/180.0))/sin(((float)j*3.14)/180.0);
					if(y>=0 && y<img.cols){
						img3.at<uchar> (x,y) = 255;
						pts++;
					}
				}
				// for(int y=0;y<img.cols;y++){
				// 	int x = (i-y*sin((j*3.14)/180.0))/cos((j*3.14)/180.0);
				// 	if(x>0 && x<img.rows)
				// 		img3.at<uchar>(x,y) = 255;
				// }
				
			}
		}
	}
	cout<<"pts = "<<pts<<endl;
	namedWindow("lines",WINDOW_NORMAL);
	imshow("lines",img3);
}