#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;

int main()
{
	VideoCapture vid("video.mp4");
	Mat img;
	while(vid.read(img))
	{
		// vid.read(img);
		Mat img2;
		// Canny(img,img2,200,500,5);
		imshow("video",img);
		waitKey(60);
	}
}