#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <bits/stdc++.h>
using namespace std;
using namespace cv;
void check_blobs(int, void *data);

struct point{
  int x;
  int y;
};
int t;

point makepoint(int x,int y){
  point temp;
  temp.x=x;
  temp.y=y;
  return temp;
}

bool checkcolor(Mat A,int i,int j){
  if(A.at<uchar>(i,j) < t)
    return true;
  else return false;
}

bool isValid(Mat A,int x,int y){
  int m=A.rows;
  int n=A.cols;
  if(x>=0 && x<m && y>=0 && y<n)
    return true;
  else return false;
}


int main()
{
  t= 0;
  Mat A=imread("chandana_food.jpg",0);
  namedWindow("dfs",WINDOW_NORMAL);
  createTrackbar("pixel_val","dfs",&t,255,check_blobs,&A);
  waitKey(0);
  return 0;
}

void check_blobs(int, void *data)
{
  Mat A = *(Mat*)data;
  int ar[A.rows][A.cols];
  for(int i=0;i<A.rows;i++){
    for(int j=0;j<A.cols;j++)
      ar[i][j]=0;
  int blobs=0;
  stack<point>s;
  for(int i=0;i<A.rows;i++){
    for(int j=0;j<A.cols;j++){
      if(checkcolor(A,i,j) && ar[i][j]!=1){
  s.push(makepoint(i,j));
  ar[i][j]=1;
  blobs++;
  while(!s.empty()){
   point u=s.top();
   s.pop();
   for(int k=u.x-1;k<=u.x+1;k++){
     for(int l=u.y-1;l<=u.y+1;l++){
       if(isValid(A,k,l)){
    if(ar[k][l]!=1 && checkcolor(A,k,l)){
     s.push(makepoint(k,l));
     ar[k][l]=1;
    }
       }
     }
   }
  }
      }
    }
  }
  Mat B(A.rows,A.cols,CV_8UC1,Scalar(0));
  for(int i=0;i<A.rows;i++){
    for(int j=0;j<A.cols;j++){
      if(ar[i][j]==1)
  B.at<uchar>(i,j)=255;
      else
  B.at<uchar>(i,j)=0;
    }
  }
  // namedWindow("dfs",WINDOW_AUTOSIZE);
  imshow("dfs",B);
  cout<<"Number of blobs is "<<blobs<<endl;
  waitKey(0);
}
}