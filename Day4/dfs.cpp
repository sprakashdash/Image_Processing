// #include <iostream>
#include <iostream>
#include <ctime>
#include <cmath>
#include <bits/stdc++.h>
#include <cstdlib>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

stack<pair <int, int > > s;
void dfs(Mat img);
pair<int,int> make_pair(int i, int j);

int main()
{
    Mat img = imread("dfs_path.jpg",0);
    Mat img2(img.rows,img.cols,CV_8UC1);
    dfs(img);
    waitKey(0);
}

void dfs(Mat img)
{
    // vector<vector<bool> > v[img.rows][img.cols];
    srand(time(NULL));
    Mat img2(img.rows,img.cols,CV_8UC3,Scalar(255,255,255));
    int v[img.rows][img.cols];
    int blobs = 0;
    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            v[i][j] = 0;
        }
    }
    for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            if(img.at<uchar>(i,j)<200 && v[i][j] == 0){
                blobs++;
                int rnd1 = rand()%256;
                int rnd2 = rand()%256;
                int rnd3 = rand()%256;
                img2.at<Vec3b>(i,j)[0] = rnd1;
                img2.at<Vec3b>(i,j)[1] = rnd2;
                img2.at<Vec3b>(i,j)[2] = rnd3;
                s.push(make_pair(i,j));

                v[i][j] = 1;
                while(!s.empty()){
                    pair<int, int> p = s.top();
                    s.pop();
                    for(int k=p.first-1;k<p.first+2;k++){
                        for(int l=p.second-1;l<p.second+2;l++){
                            if(k>=0 && k<img.rows && l>=0 && l<img.cols){
                                if(v[k][l] == 0 && img.at<uchar>(k,l) <200){
                                    v[k][l] = 1;
                                    s.push(make_pair(k,l));
                                    img2.at<Vec3b>(k,l)[0] = rnd1;
                                    img2.at<Vec3b>(k,l)[1] = rnd2;
                                    img2.at<Vec3b>(k,l)[2] = rnd3;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout<<"no. of blobs = "<<blobs<<endl;
    /*for(int i=0;i<img.rows;i++){
        for(int j=0;j<img.cols;j++){
            if(v[i][j] ==1){
                img2.at<Vec3b>(i,j)[0] = 255;
                img2.at<Vec3b>(i,j)[1] = 0;
                img2.at<Vec3b>(i,j)[2] = 0;
            }
            else if(v[i][j] ==2){
                img2.at<Vec3b>(i,j)[0] = 0;
                img2.at<Vec3b>(i,j)[1] = 255;
                img2.at<Vec3b>(i,j)[2] = 0;
            }
            else if(v[i][j] == 3){
                img2.at<Vec3b>(i,j)[0] = 0;
                img2.at<Vec3b>(i,j)[1] = 0;
                img2.at<Vec3b>(i,j)[2] = 255;
            }
            else if(v[i][j] = 4){
                img2.at<Vec3b>(i,j)[0] = 255;
                img2.at<Vec3b>(i,j)[1] = 255;
                img2.at<Vec3b>(i,j)[2] = 255;
            }
        }
    }
*/ imshow("colours",img2);
}

pair<int,int> make_pair(int i, int j)
{
    pair<int, int> p;
    p.first = i;
    p.second = j;
    return p;
}