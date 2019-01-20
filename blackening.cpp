#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

void display(Mat img)
{
  imshow("First file",img);
}

Mat read(String filename)
{
 Mat img=  imread(filename);
 return img;
}

void blacken(Mat img)
{
  int i,j;

  for(i=img.rows/3;i<img.rows;i++)
    {
      for(j=0;j<img.cols;j++)
	{
	  img.at<Vec3b>(i,j)[2]=0;
	  img.at<Vec3b>(i,j)[0]=0;
	  img.at<Vec3b>(i,j)[1]=0;
	}
    }
  display(img);
}

int main()
{
  Mat img;
  char name[100];
  cout<<"Enter the string"<<"\n";
  cin>>name;
  img = read(name);
  blacken(img);
  int  ikey =waitKey(50);
  waitKey(0);
  return 0;
}
