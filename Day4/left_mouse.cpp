#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
void callback(int event, int x, int y, int d, void*);

Mat img = imread("test.jpg");
int main()
{
	namedWindow("window",WINDOW_NORMAL);
	imshow("window",img);
	setMouseCallback("window",callback);
	waitKey(0);
}

void callback(int event, int x, int y, int d, void*)
{
	// if(event == EVENT_LBUTTONDOWN);
	if(event==EVENT_MOUSEMOVE)
		cout<<x<<" "<<y<<endl;
}