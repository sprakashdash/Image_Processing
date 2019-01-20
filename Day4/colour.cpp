#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
Mat img = imread("shapes.jpg",0);
void callback(int event, int x, int y, int d, void*);

int main()
{
	srand(time(NULL));
	namedWindow("window",WINDOW_NORMAL);
	// imshow("window",img);
	setMouseCallback("window",callback);
	waitKey(0);
}

void callback(int event, int x, int y, int d, void*)
{
	// int rnd = rand()%256;
	if(event == EVENT_MOUSEMOVE){
		img.at<uchar>(y,x) = 0;
		cout<<x<<" "<<y<<endl; 
	}
	imshow("window",img);
	// if(event==EVENT_MOUSEMOVE)
		
}