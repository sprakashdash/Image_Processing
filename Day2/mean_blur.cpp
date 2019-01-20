#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
void mean_blur(Mat img);

int main()
{
	Mat img = imread("test.jpg",0);
	imshow("original",img);
	mean_blur(img);
	waitKey(0);

}

void mean_blur(Mat img)
{
	Mat img2(img.rows,img.cols,CV_8UC1);
	for(int i=1;i<img.rows-1;i++){
		for(int j=1;j<img.cols-1;j++){
			int a=0;
			for(int k= i-1;k<i+2;k++){
				for(int l=j-1;l<j+2;l++){
					a += img.at<uchar>(k,l);
				}
			}
			img2.at<uchar>(i,j) = a/9;
		}
	}
	imshow("blur",img2);
}