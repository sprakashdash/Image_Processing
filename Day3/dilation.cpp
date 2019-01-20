#include <iostream>
#include <algorithm>
#include <vector>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
void dilation(Mat img);
int main()
{
	Mat img = imread("filter2.png",0);
	imshow("original",img);
	dilation(img);
	waitKey(0);
}

void dilation(Mat img)
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
	imshow("dilation",img2);
}
