#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("test.jpg",1);
	Mat img2(img.rows,img.cols,CV_8UC1);
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			img2.at<uchar> (i,j) = (0.114*img.at<Vec3b> (i,j)[0] +0.299*img.at<Vec3b> (i,j)[1]+0.587*img.at<Vec3b> (i,j)[2]);
		}
	}
	imshow("gray",img2);
	waitKey(0);
	return 0;
}