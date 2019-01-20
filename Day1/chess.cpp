#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	Mat img(8,8,CV_8UC1);
	namedWindow("chessboard",WINDOW_NORMAL);
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if((i+j)%2==0){
				img.at<uchar> (i,j) = 255;  
			}
		}
	}
	imshow("chessboard",img);
	waitKey(0);
	return 0;
}