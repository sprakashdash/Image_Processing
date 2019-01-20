#include <iostream>
#include <cmath>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
void vignette(int , void*);
int t;
int main()
{
	Mat img = imread("test.jpg");
	namedWindow("vignette",WINDOW_NORMAL);
	createTrackbar("vignette","vignette",&t,100,vignette,&img);
	// vignette(img);
	waitKey(0);
}

void vignette(int size,void* data)
{
	double d,dm;
	Mat* img = (Mat*)data;
	Mat img2(img->rows,img->cols,CV_8UC3);
	dm = sqrt((img->rows)/2*(img->rows)/2+(img->cols/2)*(img->cols/2));
	for(int i=0;i<img->rows;i++){
		for(int j=0;j<img->cols;j++){
			d = sqrt((i-img->rows/2)*(i-img->rows/2)+(j-img->cols/2)*(j-img->cols/2))*(t/100.0);
			for(int k=0;k<3;k++)
			img2.at<Vec3b>(i,j)[k] = img->at<Vec3b>(i,j)[k]*(1.0-d/dm);
		}
	}
	imshow("vignette",img2);
}