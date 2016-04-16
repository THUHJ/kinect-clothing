#pragma once
#include <opencv2/opencv.hpp>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace cv;
class Wardrobe
{
public:
	Wardrobe(Mat&);
	~Wardrobe(void);
	void update(Mat& );
	void handle();
	void showupper();
	void showdown();
	void drawbutton();
	void showimage(Mat& ,Mat& ,int ,int ,int ,int );
	void nextupper();
	void lastupper();
	void nextdown();
	void lastdown();
	void showords(Mat& ,const char* ,int,int);
	void showdown_info();
	void showupper_info();
	void showstage();
	void showgesture(int);

	Mat backgroud;
	int uppernumber;
	int downnumber;
	int stage; 
};


