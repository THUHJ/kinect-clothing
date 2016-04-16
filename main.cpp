#include <Windows.h>
#include <Kinect.h>
#include "Wardrobe.h"
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace cv;
void showimage(Mat& image) {
	Mat logo = imread("data/Button Next.png");
	Mat mask = imread("data/Button Next.png",0);
	Mat logo2 = imread("data/Button Previous.png");
	Mat mask2 = imread("data/Button Previous.png",0);

	cout<<logo.size().height<<endl;
	if (logo.empty())
	{
			cout<<"???<"<<endl;
	}

	//cvtColor(logo, logo, CV_RGB2RGBA);
	resize(logo, logo, Size(100,100));
	resize(mask, mask, Size(100,100));
	Mat imageROI = image(Rect(0,0,logo.cols,logo.rows));
	logo.copyTo(imageROI, mask);

	//cvtColor(logo2, logo2, CV_RGB2RGBA);
	resize(logo2, logo2, Size(100,100));
	resize(mask2, mask2, Size(100,100));
	Mat imageROI2 = image(Rect(200,400,logo.cols,logo.rows));
	logo2.copyTo(imageROI2, mask2);

	 imshow("image2", imageROI2);
}
int main() {
	
	
	srand(unsigned(time(0)));
	const char* imagename = "data/back.jpg";
 
    //从文件中读入图像
	Mat backimg =  imread(imagename);
	resize(backimg, backimg, Size(400,550));;
	Mat img = backimg.clone();
	
	Wardrobe ward = Wardrobe(img);
	while (true)
	{
		img = backimg.clone();
		ward.update(img);
		imshow("image", img);
		waitKey();
	}


    
	
	//如果读入图像失败
    if(img.empty())
    {
        fprintf(stderr, "Can not load image %s\n", imagename);
        return -1;
    }
 
    //显示图像
  //  imshow("image", img);
 
    //此函数等待按键，按键盘任意键就返回
   waitKey();
 
    //return 0;


	return 0;

	
}
