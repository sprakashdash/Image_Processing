#include <iostream>
#include <algorithm>
#include <vector>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
Mat erosion(Mat img);
Mat dilation(Mat img);

int main()
{
	Mat img = imread("filter4.png",0);
	imshow("original",img);
	img = erosion(img);
	img = dilation(img);
	img = dilation(img);
	// img = erosion(img);
	imshow("filtered",img);
	waitKey(0);
}

Mat erosion(Mat img)
{
	Mat img2(img.rows,img.cols,CV_8UC1);
	for(int i=0;i<img.rows-2;i++){
		for(int j=0;j<img.cols-2;j++){
			std::vector<int> v;
			for(int k=i;k<i+3;k++){
				for(int l=j;l<j+3;l++){
					v.push_back(img.at<uchar>(k,l));
				}
			}
			int a = *min_element(v.begin(), v.end());
			for(int k=i;k<i+3;k++){
				for(int l=j;l<j+3;l++){
					img2.at<uchar>(k,l) = a;
				}
			}
		}
	}
	return img2;
	// imshow("erosion",img2);
}

Mat dilation(Mat img)
{
	Mat img2(img.rows,img.cols,CV_8UC1);
	for(int i=0;i<img.rows-2;i++){
		for(int j=0;j<img.cols-2;j++){
			std::vector<int> v;
			for(int k=i;k<i+3;k++){
				for(int l=j;l<j+3;l++){
					v.push_back(img.at<uchar>(k,l));
				}
			}
			int a = *max_element(v.begin(), v.end());
			for(int k=i;k<i+3;k++){
				for(int l=j;l<j+3;l++){
					img2.at<uchar>(k,l) = a;
				}
			}
		}
	}
	// imshow("dilation",img2);
	// erosion(img2);
	return img2;
}
