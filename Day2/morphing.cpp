#include <iostream>
#include <algorithm>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
int t;
Mat img1 = imread("img1.jpg");
Mat img2 = imread("a.png");
void morph(int, void*);

int main()
{
	namedWindow("morph",WINDOW_NORMAL);
	createTrackbar("morph","morph",&t,100,morph,&img1);
	waitKey(0);
}

void morph(int, void*)
{
	Mat img(img1.rows,img1.cols,CV_8UC3);
	float alpha = t/100.0;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			for(int k=0;k<3;k++){
				img.at<Vec3b>(i,j)[k] = (alpha)*img2.at<Vec3b>(i,j)[k]+(1-alpha)*img1.at<Vec3b>(i,j)[k]; 
			}
		}
	}
	imshow("morph",img);
}