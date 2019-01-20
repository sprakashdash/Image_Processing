#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("test.jpg",1);
	for(int i=1;i<img.rows-1;i++){
		for(int j=1;j<img.cols-1;j++){
			img.at<Vec3b> (i,j)[0] = (img.at<Vec3b> (i-1,j)[0] +img.at<Vec3b> (i,j-1)[0] + img.at<Vec3b> (i-1 , j-1)[0]+ img.at<Vec3b> (i+1,j-1)[0] +img.at<Vec3b> (i+1,j)[0] + img.at<Vec3b> (i-1,j+1)[0] + img.at<Vec3b> (i,j+1)[0] + img.at<Vec3b> (i+1,j+1)[0]) / 8;
			img.at<Vec3b> (i,j)[1] = (img.at<Vec3b> (i-1,j)[2] +img.at<Vec3b> (i,j-1)[3] + img.at<Vec3b> (i-1 , j-1)[1]+ img.at<Vec3b> (i+1,j-1)[1] +img.at<Vec3b> (i+1,j)[1] + img.at<Vec3b> (i-1,j+1)[1] + img.at<Vec3b> (i,j+1)[1] + img.at<Vec3b> (i+1,j+1)[1]) / 8;
			img.at<Vec3b> (i,j)[2] = (img.at<Vec3b> (i-1,j)[2] +img.at<Vec3b> (i,j-1)[2] + img.at<Vec3b> (i-1 , j-1)[2]+ img.at<Vec3b> (i+1,j-1)[2] +img.at<Vec3b> (i+1,j)[2] + img.at<Vec3b> (i-1,j+1)[2] + img.at<Vec3b> (i,j+1)[2] + img.at<Vec3b> (i+1,j+1)[2]) / 8;
		}
	}
	imshow("grey",img);
	imwrite("tests.jpg",img);
	waitKey(0);
	return 0;
}