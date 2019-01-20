#include <iostream>
#include <bits/stdc++.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
// void colour(int event, int x, int y, int d, void* data);
// brown = 96 93 148 // 356.73o, 37.16% 58.04%
// pink = 157 98 186 // 319.77o 47.31% 72.94%
// yellow = 58 208 246 // 47.87o 76.42% 96.47% 
Mat gauss_filter(Mat img);
Mat yellow_detect(Mat img);
bool checkcolor(Mat* img, int i, int j);
bool checkpt(Mat* img, int i,int flag);
pair<int,int> make_pair(int i, int j);
pair<int, int> pink_detect(Mat img);
bool check_pink(Mat* img, int i, int j);
bool check_brown(Mat* img, int i, int j);
Mat brown_detect(Mat img);
Mat erosion(Mat &img);

int main()
{
	VideoCapture vid("task2.mp4");
	Mat img;
	// namedWindow("window",WINDOW_NORMAL);
	vector<vector<Point> >contours;
	vector<Vec4i>heirarchy;
	vector<vector<Point> >contoursb;
	vector<Vec4i>heirarchyb;
	int score=0;
	int frames = 0;
	int flag = 0;
	Mat yellow;
	Mat brown;
	while(vid.read(img))
	{
		// cout<<"read frames = "<<++frames<<endl;
		frames++;
		img = gauss_filter(img);
		// cout<<"fileterd frame"<<frames<<endl;
		if(frames == 1){
			yellow = yellow_detect(img);
			// yellow = erosion(yellow);
			brown = brown_detect(img);
			brown = erosion(brown);
			// waitKey(10);
			cout<<"detected yellow & brown colours\n";
		}
		namedWindow("yellow",WINDOW_NORMAL);
		imshow("yellow",yellow);
		namedWindow("brown",WINDOW_NORMAL);
		imshow("brown",brown);
		// waitKey(10);
		pair<int, int> pink = pink_detect(img);
		// cout<<"located bot in frame "<<frames<<" at "<<pink.first<<" "<<pink.second<<endl;
		int p=0,q=0;
		Mat kernb(201,201,CV_8UC1);
		for(int i=pink.first-100;i<pink.first+101;i++){
			q = 0;
			for(int j=pink.second-100;j<pink.second+101;j++){
				if(i>=0 && i<brown.rows && j>=0 && j<brown.cols){
					kernb.at<uchar>(p,q) = brown.at<uchar>(i,j);
				}
				q++;
			}
			p++;
		}
		p=0;
		// kernb = erosion(kernb);
		Mat kerny(201,201,CV_8UC1);
		for(int i=pink.first-100;i<pink.first+101;i++){
			q=0;
			for(int j=pink.second-100;j<pink.second+101;j++){
				if(i>=0 && i<yellow.rows && j>=0 && j<yellow.cols){
					kerny.at<uchar>(p,q) = yellow.at<uchar>(i,j);
				}
				q++; 
			}
			p++;
		}
		// kerny = erosion(kerny);
		namedWindow("kernb",WINDOW_NORMAL);
		imshow("kernb",kernb);
		// if(frames==2)
		// 	waitKey(0);
		waitKey(10);
		Canny(kernb,kernb,128,256,3);
		findContours(kernb,contoursb,heirarchyb,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
		if(contoursb.size()>0 && flag == 1){
			cout<<"reached home\n";
			flag = 0;
		}
		namedWindow("kerny",WINDOW_NORMAL);
		imshow("kerny",kerny);
		waitKey(10);
		Canny(kerny,kerny,128,256,3);
		findContours(kerny,contours,heirarchy,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);
		// Mat tempb(kerny.rows,kerny.cols,CV_8UC1);
		// drawContours(tempb,contours,0,255,2,8,heirarchy,1);
		if(contours.size()>0 && flag == 0){
			if(contours[0].size() == 3){
				score+=200;
				flag = 1;
				cout<<"found a triangle\n";
			}
			else if(contours[0].size() == 4){
				score+=100;
				flag = 1;
				cout<<"found a square\n";
			}

		}

		// break;
	}
	cout<<"score = "<<score<<endl;
	return 0;


}

Mat gauss_filter(Mat img)
{
	// cout<<"entered filter\n";
 	Mat img2(img.rows,img.cols,CV_8UC3);
 	for(int i=1;i<img.rows-1;i++){
 		for(int j=1;j<img.cols;j++){
 			for(int k=0;k<3;k++){
 				int a=0;
 				a = (img.at<Vec3b>(i-1,j-1)[k] + img.at<Vec3b>(i-1,j+1)[k] + img.at<Vec3b>(i+1,j-1)[k] + img.at<Vec3b>(i+1,j+1)[k])/16 + (img.at<Vec3b>(i,j-1)[k] + img.at<Vec3b>(i,j+1)[k] + img.at<Vec3b>(i+1,j)[k] + img.at<Vec3b>(i-1,j)[k])/8 + (img.at<Vec3b>(i,j)[k])/4;
 				img2.at<Vec3b>(i,j)[k] = a;
 			}
 		}
 	}
 	// imshow("gaussian_blur",img2);
 	// waitKey(0);
 	return img2;
 }

Mat yellow_detect(Mat img)
{
	queue <pair <int, int> > q;
	Mat img2(img.rows,img.cols,CV_8UC1,Scalar(0));
	Mat img3(img.rows,img.cols,CV_8UC1,Scalar(0));
	srand(time(NULL));
	int blobs = 0;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			if(checkcolor(&img,i,j) && img2.at<uchar>(i,j) == 0){
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
								if(img2.at<uchar>(k,l)==0 && checkcolor(&img,k,l)){
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
	// imshow("yellow-detect",img3);
	// waitKey(0);
	return img3;
 }

bool checkcolor(Mat* img, int i, int j)
{
	int min_threshold = 150;
	int max_threshold = 150;
	if(img->at<Vec3b>(i,j)[0]<min_threshold && img->at<Vec3b>(i,j)[1]>max_threshold && img->at<Vec3b>(i,j)[2]>max_threshold){
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

pair<int,int> make_pair(int i, int j)
{
    pair<int, int> p;
    p.first = i;
    p.second = j;
    return p;
}

pair<int, int> pink_detect(Mat img)
{
	queue <pair <int, int> > q;
	double x=0,y=0;
	Mat img2(img.rows,img.cols,CV_8UC1,Scalar(0));
	Mat img3(img.rows,img.cols,CV_8UC1,Scalar(0));
	srand(time(NULL));
	int blobs = 0;
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			if(check_pink(&img,i,j) && img2.at<uchar>(i,j) == 0){
				blobs++;
				q.push(make_pair(i,j));
				x+=i;
				y+=j;
				img3.at<uchar>(i,j) = 255;
				img2.at<uchar>(i,j) = 255;
				while(!q.empty()){
					pair<int, int> p = q.front();
					q.pop();
					// img2.at<uchar>(p.first,p.second) = 255;
					for(int k=p.first-1;k<p.first+2;k++){
						for(int l=p.second-1;l<p.second+2;l++){
							if(checkpt(&img,k,0)&&checkpt(&img,l,1)){
								if(img2.at<uchar>(k,l)==0 && check_pink(&img,k,l)){
									img2.at<uchar>(k,l) = 255;
									q.push(make_pair(k,l));
									x+=k;
									y+=l;
									img3.at<uchar>(k,l) = 255;
									blobs++;
								}	
							}
						}
					}
				}
			}
		}
	}
	x/=blobs;
	y/=blobs;
	// cout<<"pink-location: "<<x<<" "<<y<<endl;
	namedWindow("pink",WINDOW_NORMAL);
	imshow("pink",img3);
	waitKey(10);
	return make_pair((int)x,(int)y);
	
}

bool check_pink(Mat* img, int i, int j)
{
	int b_min = 140;
	int b_max = 180;
	int g_min = 75;
	int g_max = 150;
	int r_min = 180;
	int r_max = 256;	
	if(img->at<Vec3b>(i,j)[0]>b_min && img->at<Vec3b>(i,j)[0]<b_max && img->at<Vec3b>(i,j)[1]>g_min &&img->at<Vec3b>(i,j)[1]<g_max && img->at<Vec3b>(i,j)[2]>r_min && img->at<Vec3b>(i,j)[2]<r_max){
		return true;
	}
	return false;
}

Mat brown_detect(Mat img)
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
	// imshow("yellow-detect",img3);
	// waitKey(0);
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

Mat erosion(Mat &img)
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
	// imshow("erosion",img2);
	return img2;
}