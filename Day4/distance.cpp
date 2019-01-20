#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <bits/stdc++.h>
#include <algorithm>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

queue <pair <int, int> > q;
pair<int,int> make_pair(int i, int j);
bool checkpt(Mat* img, int i,int flag);
bool checkcolor(Mat* img, int i, int j);
void bfs(Mat img,int i, int j);
float Dist(pair<int, int >x,pair<int, int > y);
void bfs_(Mat img, int x, int y);
Mat img = imread("dfs_path.jpg",0);
Mat img2(img.rows,img.cols,CV_8UC1,Scalar(0));

int main()
{
	int blobs = 0;
	Mat img = imread("dfs_path.jpg",0);
	vector< pair<int,int> > pts(4);
	// start.first = start.second = 0;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			if(checkcolor(&img,i,j) && img2.at<uchar>(i,j) == 0){
				pts[blobs].first = i;
				pts[blobs].second = j;
				bfs(img,i,j);
				cout<<"No.of blobs = "<<blobs<<endl;
				blobs++;
			}
		}
	}
	vector<float> dist;
	for(int i=0;i<4;i++){
		for(int j=i+1;j<4;j++){
			dist.push_back(Dist(pts[i],pts[j]));
		}
	}
	int key = max_element(dist.begin(), dist.end()) - dist.begin();
	cout<<"key = "<<key<<endl;
	int x,y;
	switch(key){
		case 0:  x=1;y=2;
		break;
		case 1: x=1;y=3;
		break;
		case 2: x=1;y=4;
		break;
		case 3: x=2;y=3;
		break;
		case 4: x=2;y=4;
		break;
		case 5: x=3;y=4;
		break;
	}
	bfs_(img,x,y);
	waitKey(0);
}

void bfs(Mat img,int i, int j)
{
	int blobs=0;
	Mat img3(img.rows,img.cols,CV_8UC3,Scalar(255,255,255));
	srand(time(NULL));
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
	// cout<<"No. of blobs = "<<blobs<<endl;
	// imshow("wn",img3);
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

float Dist(pair<int,int>x,pair<int,int> y)
{
	int x2 = x.first-y.first;
	int y2 = x.second - y.second;
	return sqrt(x2*x2-y2*y2);
}

void bfs_(Mat img, int x, int y)
{
	int blobs = 0;
	queue <pair<int, int> > q;
	// Mat img2(img.rows,img.cols,CV_8UC1,Scalar(0));
	Mat img3(img.rows,img.cols,CV_8UC3,Scalar(255,255,255));
	srand(time(NULL));
	int rand1 = rand()%256;
    int rand2 = rand()%256;
    int rand3 = rand()%256;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			if(checkcolor(&img,i,j) && img2.at<uchar>(i,j) == 0){
			    int rnd1 = rand()%256;
			    int rnd2 = rand()%256;
			    int rnd3 = rand()%256;
				blobs++;
				q.push(make_pair(i,j));
				img2.at<uchar>(i,j) = 255;
				if(blobs == x || blobs == y){
				img3.at<Vec3b>(i,j)[0] = rand1;
                img3.at<Vec3b>(i,j)[1] = rand2;
                img3.at<Vec3b>(i,j)[2] = rand3;
				}
				else{
	                img3.at<Vec3b>(i,j)[0] = rnd1;
	                img3.at<Vec3b>(i,j)[1] = rnd2;
	                img3.at<Vec3b>(i,j)[2] = rnd3;
	            }
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
									if(blobs == x || blobs == y){
										img3.at<Vec3b>(k,l)[0] = rand1;
						                img3.at<Vec3b>(k,l)[1] = rand2;
						                img3.at<Vec3b>(k,l)[2] = rand3;
									}
									else{
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
	}
	
	// cout<<"No. of blobs = "<<blobs<<endl;
	imshow("wn",img3);
}