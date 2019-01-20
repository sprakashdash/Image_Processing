#include <iostream>
#include <bits/stdc++.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
bool check_brown(Mat* img, int i, int j);
bool checkpt(Mat* img, int i,int flag);
Mat brown_detect(Mat &img);

int main()
{
	Mat img = imread("sample.jpg",1);
	img = brown_detect(img);

}

Mat brown_detect(Mat &img)
{
	queue <pair <int, int> > q;
	Mat img2(img.rows,img.cols,CV_8UC1,Scalar(0));
	Mat img3(img.rows,img.cols,CV_8UC1,Scalar(0));
	srand(time(NULL));
	int blobs = 0;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			if(check_brown(&img,i,j) && img2.at<uchar>(i,j) == 0){
				blobs++;
				q.push(make_pair(i,j));
				img2.at<uchar>(i,j) = 255;
				// int rnd1 = rand()%256;
    //             int rnd2 = rand()%256;
    //             int rnd3 = rand()%256;
                // img3.at<Vec3b>(i,j)[0] = 0;
                // img3.at<Vec3b>(i,j)[1] = 255;
                // img3.at<Vec3b>(i,j)[2] = 255;
                img3.at<uchar>(i,j) = 255;
				while(!q.empty()){
					pair<int, int> p = q.front();
					q.pop();
					// img2.at<uchar>(p.first,p.second) = 255;
					for(int k=p.first-1;k<p.first+2;k++){
						for(int l=p.second-1;l<p.second+2;l++){
							if(checkpt(&img,k,0)&&checkpt(&img,l,1)){
								if(img2.at<uchar>(k,l)==0 && check_brown(&img,k,l)){
									img2.at<uchar>(k,l) = 255;
									q.push(make_pair(k,l));
					                // img3.at<Vec3b>(k,l)[0] = 0;
					                // img3.at<Vec3b>(k,l)[1] = 255;
					                // img3.at<Vec3b>(k,l)[2] = 255;
					                img3.at<uchar>(k,l) = 255;
								}
							}
						}
					}
				}
			}
		}
	}
	imshow("yellow-detect",img3);
	waitKey(0);
	return img3;
 }

bool check_brown(Mat* img, int i, int j)
{
	int bg_min = 80;
	int bg_max = 120;
	int red_min = 130;
	int red_max = 180;
	if(img->at<Vec3b>(i,j)[0]>bg_min && img->at<Vec3b>(i,j)[0]< bg_max && img->at<Vec3b>(i,j)[1]> bg_min && img->at<Vec3b>(i,j)[1]<bg_max && img->at<Vec3b>(i,j)[2] > red_min &&img->at<Vec3b>(i,j)[2]<red_max){
		return true;
	}
	return false;
}

bool checkpt(Mat* img, int i,int flag)
{
	if(flag==0){
		if(i>=0 && i<img->rows)
			return true;
	}
	else{
		if(i>=0 && i<img->cols)
			return true;
	}
	return false;
}