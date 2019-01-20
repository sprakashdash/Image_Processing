#include <iostream>
#include <algorithm>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img= imread("lena_low.png",0);
	float alpha = 1.2;
	int beta = 15;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			unsigned int a = img.at<uchar>(i,j)*alpha;
			img.at<uchar>(i,j) = img.at<uchar>(i,j) >  a? img.at<uchar>(i,j) : a; 
			if(img.at<uchar>(i,j)<255-beta)
				img.at<uchar>(i,j)+= beta;
			else{
				img.at<uchar>(i,j) = 255;
			}
		}
	}
	imshow("lena_high",img);
	waitKey(0);
}