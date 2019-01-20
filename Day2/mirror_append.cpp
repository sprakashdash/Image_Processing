#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("test.jpg",1);
	Mat img2(img.rows,img.cols,CV_8UC3);
	for(int i= 0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			img2.at<Vec3b> (i,j)[0] = img.at<Vec3b> (i,img.cols-j)[0];
			img2.at<Vec3b> (i,j)[1] = img.at<Vec3b> (i,img.cols-j)[1];
			img2.at<Vec3b> (i,j)[2] = img.at<Vec3b> (i,img.cols-j)[2];
		}
	}
	Mat img3(img.rows,2*img.cols,CV_8UC3);
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			img3.at<Vec3b> (i,j)[0] = img2.at<Vec3b> (i,j)[0];
			img3.at<Vec3b> (i,j)[1] = img2.at<Vec3b> (i,j)[1];
			img3.at<Vec3b> (i,j)[2] = img2.at<Vec3b> (i,j)[2];
		}
		for(int j=img.cols;j<2*img.cols;j++){
			img3.at<Vec3b> (i,j)[0] = img.at<Vec3b>(i,j-img.cols)[0];
			img3.at<Vec3b> (i,j)[1] = img.at<Vec3b>(i,j-img.cols)[1];
			img3.at<Vec3b> (i,j)[2] = img.at<Vec3b>(i,j-img.cols)[2];
				
		}
	}
	namedWindow("original+mirror",WINDOW_AUTOSIZE);
	imshow("original+mirror",img3);
	waitKey(0);
	return 0;
}