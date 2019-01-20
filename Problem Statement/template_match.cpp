#include <iostream>
#include <cstdlib>
#include <ctime>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"

using namespace std;
using namespace cv;
Mat shuffle(Mat *img);
void solve(Mat* img, Mat* img2);

int main()
{
	Mat img = imread("task1.jpg",1);
	namedWindow("original",WINDOW_NORMAL);
	imshow("original",img);
	Mat img2(img.rows,img.cols,CV_8UC3);
	img2 = shuffle(&img);
	solve(&img,&img2);
	waitKey(0);
}

Mat shuffle(Mat *img)
{
	srand(time(NULL));
	int r = img->rows, c = img->cols;
	Mat img2(r,c,CV_8UC3);
	bool visited[9];
	int shuf_order[9];
	for(int i=0;i<9;i++)
		visited[i] = false;
	int count = 0;
	while(count!=9){
		int rnd = rand()%9;
		if(visited[rnd]==false){
			shuf_order[count] = rnd;
			visited[rnd] = true;
			count++;
		}
	}
	int p=0,q=0;
	for(int i=0;i<9;i++){
		p = (i/3)*(r/3);
		int l = shuf_order[i];
		for(int x= (r/3)*(l/3);x<(r/3)*((l/3)+1);x++){
			q = (i%3)*(c/3);
			for(int y=(c/3)*(l%3);y<(c/3)*((l%3)+1);y++){
				for(int k=0;k<3;k++){
					img2.at<Vec3b>(p,q)[k] = img->at<Vec3b>(x,y)[k];
				}
				q++;
			}
			p++;
		}

	}
	namedWindow("shuffle",WINDOW_NORMAL);
	imshow("shuffle",img2);
	return img2;
}

void solve(Mat* img, Mat* img2)
{
	int r = img->rows,c=img->cols;
	Mat img3(r,c,CV_8UC3);
	Mat templ(r/3,c/3,CV_8UC3);
	Mat res(r-templ.rows+1,c-templ.cols+1,CV_8UC3);
	double minVal,maxVal;
	Point minLoc,maxLoc,matchLoc;
	for(int i=0;i<9;i++){
		int p=0,q=0;
		for(int x = (i/3)*(r/3);x<(r/3)*(i/3+1);x++){
			q=0;
			for(int y=(i%3)*(c/3);y<(c/3)*(i%3+1);y++){
				for(int k=0;k<3;k++){
					templ.at<Vec3b>(p,q)[k] = img->at<Vec3b>(x,y)[k];
				}
				q++;
			}
			p++;
		}
		matchTemplate(*img2,templ,res,CV_TM_SQDIFF);
		normalize( res, res, 0, 1, NORM_MINMAX, -1, Mat() );
		minMaxLoc(res,&minVal,&maxVal,&minLoc,&maxLoc,Mat());
		matchLoc = minLoc;
		p = (i/3)*(r/3);
		for(int x=matchLoc.y;x<matchLoc.y+templ.rows;x++){
			int q = (i%3)*(c/3);
			for(int y=matchLoc.x;y<matchLoc.x+templ.cols;y++){
				for(int k=0;k<3;k++){
					if(x<r && y<c)
						img3.at<Vec3b>(p,q)[k] = img2->at<Vec3b>(x,y)[k];
				}
				q++;
			}
			p++;
		}
	}
	namedWindow("solved",WINDOW_NORMAL);
	imshow("solved",img3);
}