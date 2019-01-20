#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
void shrink(Mat img);
int main()
{
	Mat img = imread("test.jpg");
	imshow("orig",img);
	shrink(img);	
	waitKey(0);
}

void shrink(Mat img)
{
	Mat img2(img.rows/2,img.cols/2,CV_8UC3);
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			img2.at<Vec3b>(i/2,j/2)[0] += img.at<Vec3b>(i,j)[0]/4; 
			img2.at<Vec3b>(i/2,j/2)[1] += img.at<Vec3b>(i,j)[1]/4;
			img2.at<Vec3b>(i/2,j/2)[2] += img.at<Vec3b>(i,j)[2]/4;
		}
	}
	imshow("half",img2);
}
