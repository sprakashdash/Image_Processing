#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img(500,500,CV_8UC3,Scalar(0,0,255));
	for(int i=0;i<500;i++){
		for(int j=0;j<500;j++){
			if(i<j){
				img.at<Vec3b> (i,j)[1] = 255;
				img.at<Vec3b> (i,j)[2] = 0;
			}
		}
	}
	imshow("diag",img);
	waitKey(0);
	return 0;
}