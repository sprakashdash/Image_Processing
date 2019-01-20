#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

queue <pair <int, int> > q;
pair<int,int> make_pair(int i, int j);
bool checkpt(Mat* img, int i,int flag);
bool checkcolor(Mat* img, int i, int j);
void bfs(Mat img);


int main()
{
	Mat img = imread("dfs_path.jpg",0);
	bfs(img);
	waitKey(0);
}

void bfs(Mat img)
{
	Mat img2(img.rows,img.cols,CV_8UC1,Scalar(0));
	Mat img3(img.rows,img.cols,CV_8UC3,Scalar(255,255,255));
	srand(time(NULL));
	int blobs = 0;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			if(checkcolor(&img,i,j) && img2.at<uchar>(i,j) == 0){
				blobs++;
				q.push(make_pair(i,j));
				img2.at<uchar>(i,j) = 255;
				int rnd1 = rand()%256;
                int rnd2 = rand()%256;
                int rnd3 = rand()%256;
                img3.at<Vec3b>(i,j)[0] = rnd1;
                img3.at<Vec3b>(i,j)[1] = rnd2;
                img3.at<Vec3b>(i,j)[2] = rnd3;
				while(!q.empty()){
					pair<int, int> p = q.front();
					q.pop();
					// img2.at<uchar>(p.first,p.second) = 255;
					for(int k=p.first-1;k<p.first+2;k++){
						for(int l=p.second-1;l<p.second+2;l++){
							if(checkpt(&img,k,0)&&checkpt(&img,l,1)){
								if(img2.at<uchar>(k,l)==0 && checkcolor(&img,k,l)){
									img2.at<uchar>(k,l) = 255;
									q.push(make_pair(k,l));
					                img3.at<Vec3b>(k,l)[0] = rnd1;
					                img3.at<Vec3b>(k,l)[1] = rnd2;
					                img3.at<Vec3b>(k,l)[2] = rnd3;
								}
							}
						}
					}
				}
			}
		}
	}
	cout<<"No. of blobs = "<<blobs<<endl;
	imshow("wn",img3);
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

bool checkcolor(Mat* img, int i, int j)
{
	int threshold = 20;
	if(img->at<uchar>(i,j)<threshold){
		return true;
	}
	return false;
}

pair<int,int> make_pair(int i, int j)
{
    pair<int, int> p;
    p.first = i;
    p.second = j;
    return p;
}