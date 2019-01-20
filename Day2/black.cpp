#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

void slide(int size, void *data);


using namespace std;
using namespace cv;
int r,R,g,G,b,B;
Mat img = imread("a.png",1);

int main()
{
	namedWindow("apple",WINDOW_NORMAL);
	r=0;R=0;g=0;G=0;b=0;B=0;
	int var_max = 256;
	createTrackbar("Redmin","apple",&r,var_max,slide,&img);
	createTrackbar("Redmax","apple",&R,var_max,slide,&img);
	createTrackbar("Bluemin","apple",&b,var_max,slide,&img);
	createTrackbar("Bluemax","apple",&B,var_max,slide,&img);
	createTrackbar("Greenmin","apple",&g,var_max,slide,&img);
	createTrackbar("Greenmax","apple",&G,var_max,slide,&img);
	// imshow("apple",img);
	int ikey = waitKey(5);
	waitKey(0);
	return 0;

}

void slide(int size,void *data)
{
	Mat *img = ((Mat*)data);
	Mat img2(img->rows,img->cols,CV_8UC3);
	for(int i=0;i<img->rows;i++){
		for(int j=0;j<img->cols;j++){
			if(img->at<Vec3b>(i,j)[0]>b &&img->at<Vec3b>(i,j)[0]<B &&img->at<Vec3b>(i,j)[1]>g&&img->at<Vec3b>(i,j)[1]<G && img->at<Vec3b>(i,j)[2]>r && img->at<Vec3b>(i,j)[2]<R){
				img2.at<Vec3b>(i,j)[0] = img->at<Vec3b>(i,j)[0];
				img2.at<Vec3b>(i,j)[1] = img->at<Vec3b>(i,j)[1];
				img2.at<Vec3b>(i,j)[2] = img->at<Vec3b>(i,j)[2];
			}
			else{
				img2.at<Vec3b>(i,j)[0] = 0;
				img2.at<Vec3b>(i,j)[1] = 0;
				img2.at<Vec3b>(i,j)[2] = 0;
			}
		}
	}
	imshow("apple",img2);
}
