#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img(500,500,CV_8UC3,Scalar(255,255,255));
	cvtColor(img,img,CV_BGR2HSV);
	namedWindow("yellow",WINDOW_NORMAL);
	cout<<"1st value = "<<img.at<Vec3b>(0,0)[0]<<endl;
	cout<<"2nd val = "<<img.at<Vec3b>(0,0)[1]<<endl;
	cout<<"3rd Val = "<<img.at<Vec3b>(0,0)[2]<<endl;
	imshow("yellow",img);
	waitKey(0);
	return 0;
}