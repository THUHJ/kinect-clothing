#include "Wardrobe.h"



const int GESTURE_UP = 1;
const int GESTURE_DOWN = 2;
const int GESTURE_LEFT = 3;
const int GESTURE_RIGHT = 4;

const int UPPERandINFO = 1;
const int INFOandDOWN = 2;
const int UPPERandDOWN = 3;

const int screen_height = 550; 
const int screen_width = 400;

const int upper_all = 11;
const int down_all = 9 ;

void Wardrobe::showimage(Mat& back,Mat& logo,int wi,int he,int x,int y) {
	
	Mat mask;
	cvtColor(logo, mask, CV_BGR2GRAY);
	//cvtColor(logo, logo, CV_RGB2RGBA);
	resize(logo, logo, Size(wi,he));
	resize(mask, mask, Size(wi,he));
	Mat imageROI = back(Rect(x,y,logo.cols,logo.rows));
	logo.copyTo(imageROI, mask);
}
void Wardrobe::showords(Mat& back,const char* showMsg, int x,int y)
{
		 //the font variable    
    CvFont font;    
    double hScale=1;   
    double vScale=1;    
    int lineWidth=2;// 相当于写字的线条    
    //char showMsg[]="hello image!";   
    // 初始化字体   
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, hScale,vScale,0,lineWidth);//初始化字体，准备写到图片上的   
    // cvPoint 为起笔的x，y坐标  
	CvMat cvMat = back;
	CvArr* s=(CvArr*)&cvMat;
    cvPutText(s,showMsg,cvPoint(x,y),&font,CV_RGB(0,0,0));//在图片中输出字符   
}
Wardrobe::Wardrobe(Mat&  t1)
{
	backgroud=t1;
	stage = UPPERandDOWN;
	uppernumber=0;
	downnumber=0;
}
void Wardrobe::update(Mat& t1)
{
	backgroud=t1;
	handle();
}
void Wardrobe::showupper()
{
	char str[10];
	sprintf(str,"%d",uppernumber);
	String num_str = str;
	String filename = "data/upper/";
	filename+="upper ("+num_str+").jpg";
	
	Mat upper = imread(filename);
	if (upper.empty())
	{
		cout<<"upper filename: "<<filename<< " cannot find"<<endl;
		
		return;
	}
	showimage(backgroud,upper,screen_width,screen_height/2,0,0);
}
void Wardrobe::showupper_info()
{
	char str[10];
	sprintf(str,"%d",downnumber);
	String num_str = str;
	String filename = "data/upper/";
	filename+="upper ("+num_str+").txt";

	fstream fin(filename);
	if(!fin){  
		cout<<"upper filename: "<<filename<< " cannot find"<<endl;
		
      
	}
	char buffer[256];
	String result="" ;
	while (! fin.eof() )  
	{  
		 fin.getline(buffer,100);
		 String s(buffer);
		 result+=s+" ";
		 
	 }  
	fin.close();
	
	showords(backgroud,result.data() ,10,screen_height/2+50);
}
void Wardrobe::showdown()
{
	char str[10];
	sprintf(str,"%d",downnumber);
	String num_str = str;
	String filename = "data/down/";
	filename+="down ("+num_str+").jpg";
	
	Mat down = imread(filename);
	if (down.empty())
	{
		cout<<"down filename: "<<filename<< " cannot find"<<endl;
		return;
	}
	showimage(backgroud,down,screen_width,screen_height/2,0,screen_height/2);
}
void Wardrobe::showdown_info()
{
	char str[10];
	sprintf(str,"%d",downnumber);
	String num_str = str;
	String filename = "data/down/";
	filename+="down ("+num_str+").txt";

	fstream fin(filename);
	if(!fin){  
		cout<<"down filename: "<<filename<< " cannot find"<<endl;
       
	}
	char buffer[256];
	String result="" ;
	while (! fin.eof() )  
	{  
		 fin.getline(buffer,100);
		 String s(buffer);
		 result+=s+" ";
		 
	 }  
	fin.close();
	
	showords(backgroud,result.data() ,5,50);
 
}
void Wardrobe::drawbutton()
{
}
void Wardrobe::nextupper()
{
	uppernumber=(uppernumber+1) % upper_all;
	//showupper();
}
void Wardrobe::nextdown()
{
	downnumber=(downnumber +1) % down_all;
	//showdown();
}
void Wardrobe::lastupper()
{
	uppernumber=(uppernumber-1+upper_all) % upper_all;
	//showupper();
}
void Wardrobe::lastdown()
{
	downnumber=(downnumber-1+down_all)% down_all;
	//showdown();
}
void Wardrobe::showstage()
{
	cout<<"stage is ";
	switch (stage)
	{
	case UPPERandDOWN:
		cout<<"upper and down"<<endl;;
		
		break;
	case UPPERandINFO:
		cout<<"upper and info"<<endl;;
		break;
	case INFOandDOWN:
		cout<<"info and down"<<endl;;
		break;
	default:
		break;
	}


	

}
void Wardrobe::showgesture(int tmp)
{
	cout<<"Gesture is ";
	switch(tmp)
	{
	case GESTURE_DOWN:
		cout<<"down"<<endl;
		break;
	case GESTURE_UP:
		cout<<"up"<<endl;
		break;
	case GESTURE_RIGHT:  //向右手势，当前衣服换下一套
		cout<<"right"<<endl;
		break;
	case GESTURE_LEFT://向左手势，当前衣服换上一套
		cout<<"left"<<endl;
		break;
	}
}
int GetGesture()
{
	return rand()%4+1;
}
void Wardrobe::handle()
{

	showstage();
	
	switch (stage)
	{
	case UPPERandDOWN:
		showupper();
		showdown();
		
		break;
	case UPPERandINFO:
		showupper();
		showupper_info();
		break;
	case INFOandDOWN:
		showdown_info();
		showdown();
		break;
	default:
		break;
	}

	
	int tmp = GetGesture();//得到手势
	showgesture(tmp);
	switch(tmp)
	{
	case GESTURE_DOWN:
		if (stage==UPPERandDOWN)//做一个向下的手势，那么下装的部分消失。
			stage = UPPERandINFO;
		else
		if (stage==INFOandDOWN)//上装出现
			stage = UPPERandDOWN;
		break;
	case GESTURE_UP:
		if (stage==UPPERandDOWN)//做一个向上的手势，那么上装的部分消失。
			stage = INFOandDOWN;
		else
		if (stage==UPPERandINFO)//下装出现
			stage=UPPERandDOWN;
		break;
	case GESTURE_RIGHT:  //向右手势，当前衣服换下一套
		if (stage==UPPERandINFO)
			nextupper();
		if (stage==UPPERandDOWN)
		{
			nextupper();
			nextdown();
		}
		if (stage==INFOandDOWN)
			nextdown();
		break;
	case GESTURE_LEFT://向左手势，当前衣服换上一套
		if (stage==UPPERandINFO)
			lastupper();
		if (stage==UPPERandDOWN)
		{
			lastupper();
			lastdown();
		}
		if (stage==INFOandDOWN)
			lastdown();
		break;
	}


}

Wardrobe::~Wardrobe(void)
{
}
