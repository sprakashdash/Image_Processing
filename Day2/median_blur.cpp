#include <iostream>
#include <vector>
#include <algorithm>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

void median_blur(Mat img);

int main()
{
	Mat img = imread("test.jpg",1);
	imshow("original",img);
	median_blur(img);
	waitKey(0);
}

void median_blur(Mat img)
{
	Mat img2(img.rows,img.cols,CV_8UC3);
	for(int i=1;i<img.rows-1;i++){
		for(int j=1;j<img.cols-1;j++){
			vector<int> v1,v2,v3;
			for(int k= i-1;k<i+2;k++){
				for(int l=j-1;l<j+2;l++){
					v1.push_back(img.at<Vec3b>(k,l)[0]);
					v2.push_back(img.at<Vec3b>(k,l)[1]);
					v3.push_back(img.at<Vec3b>(k,l)[2]);
				}
			}
			sort(v1.begin(),v1.end());
			sort(v2.begin(), v2.end());
			sort(v3.begin(), v3.end());
			img2.at<Vec3b> (i,j)[0] = v1[4];
			img2.at<Vec3b> (i,j)[1] = v2[4];
			img2.at<Vec3b> (i,j)[2] = v3[4];

		}
	}
	imshow("median_blur",img2);

}
