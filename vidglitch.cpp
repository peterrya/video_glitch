/* 
 *Opens video and procceses it frame by frame
*/

#include "opencv2/videoio.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/imgcodecs.hpp"



typedef unsigned char byte;
using namespace cv;

std::vector<byte> mat_to_bytes (Mat frame)
{
    	int size = frame.total() * frame.elemSize();
    	std::vector<byte> fr_bytes(size);
    	fr_bytes.assign(frame.datastart, frame.dataend);
    	return fr_bytes;}

Mat bytes_to_mat (std::vector<byte> bytes,int width,int height)
{
    	Mat frame = Mat(height,width,CV_8UC3,bytes.data()).clone();  
    	return frame;}

//will return to, will work with simpler glitches first
int glitch_png(){
	char buf[] = {'3'};
	FILE *png = fopen("output.png","r+");
	fseek(png, 50, SEEK_SET);
	//fwrite(buf, sizeof(char), 23, png);
	return 1;
}

//basic glitch to get the overall process working
Mat glitch_test(Mat frame,int width,int height){
	/*This is based on changing a file for development purposes, will be removed once I am confident with the proper method
	char buf[] = {'3'};
	char *fileval;
	FILE *bmp = fopen("output.bmp","rb+");
	int x;
	fseek(bmp, 55, SEEK_SET);
	for(x=55;x<90000;x++){
		fwrite(buf, sizeof(char),sizeof(buf),bmp);
	}
	*/
	std::vector<byte> framevec;  
	framevec = mat_to_bytes(frame);
	for (unsigned int x = 0; x < framevec.size()-1; ++x){
		framevec[x] = framevec[x+1]+framevec[x];
	}
	return bytes_to_mat(framevec, width, height);
}

Mat glitch_bmp_row(Mat frame,int width,int height){
	std::vector<byte> framevec;  
	framevec = mat_to_bytes(frame);
	for (unsigned int x = 6; x < framevec.size()-1; ++x){
		framevec[x] = framevec[x-3]/2+framevec[x]-framevec[x-6]/2;
	}
	return bytes_to_mat(framevec, width, height);
}

Mat glitch_bmp_col(Mat frame,int width,int height){
	std::vector<byte> framevec;  
	framevec = mat_to_bytes(frame);
	for (unsigned int x = width*6; x < framevec.size()-1; ++x){
		framevec[x] = framevec[x-width*3]/2+framevec[x]-framevec[x-width*6]/2;
	}
	return bytes_to_mat(framevec, width, height);

}

Mat glitch_bmp_ave(Mat frame,int width,int height){
	std::vector<byte> framevec;  
	framevec = mat_to_bytes(frame);
	std::vector<byte> copy = framevec;
	for (unsigned int x = width*2; x < framevec.size()-1; ++x){
		framevec[x] = (framevec[x] + framevec[x-width] + framevec[x+width]+framevec[x+1] + framevec[x-1])/5;
	}
	return bytes_to_mat(framevec, width, height);

}

Mat glitch_bmp_sort_varpass(Mat frame,int width,int height,int iter){
	byte hold;
	std::vector<byte> framevec;
	framevec = mat_to_bytes(frame);
	for (int z = 0; z < iter; ++z){
		for (unsigned int x = 0; x < framevec.size()-2; ++x){
			if (framevec[x] > framevec[x+1]){
				hold=framevec[x+1];
				framevec[x+1] = framevec[x];
				framevec[x] = hold;
			}
		}
		if (framevec.size()-2 > framevec.size()-1){
			hold=framevec[framevec.size()-1];
			framevec[framevec.size()-1] = framevec[framevec.size()-2];
			framevec[framevec.size()-2] = hold;
		}
	}
	return bytes_to_mat(framevec, width, height);
}

int main(int argc, char** argv){
	std::vector<byte> bytvec;
	Mat hold;
	int framecount;
	if (argc < 2){
		std::cout << "Proper use is ./vidglitch [filename]" << std::endl;
		return 0;
	}
	//Open Capture
	Mat frame;
	VideoCapture cap;
	cap.open(argv[1]);
	
	if (!cap.isOpened()) {
		std::cerr << "Unable to open camera" << std::endl;
		return -1;
	}
	int FPS = static_cast<int>(cap.get(CV_CAP_PROP_FPS));
	int width = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_WIDTH));
   	int height = static_cast<int>(cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	
	VideoWriter out("output.mov", CV_FOURCC('m','p','4','v'), FPS, Size(width,height));
	for(;;){
		cap.read(frame);
		if(frame.empty()) {
			std::cerr << "Blank Frame" << std::endl;
			break;
		}
		
		//next three lines are for png work
		//std::vector<int> comparams;
		//comparams.push_back(CV_IMWRITE_PNG_COMPRESSION);
		//comparams.push_back(9);
		imwrite("output.bmp", hold);
		hold = glitch_bmp_sort_varpass(frame,width,height,50);

		imshow("Preview", hold);
		
		out << hold;
		if (waitKey(1) >=0){
			break;
		}
	}

	return 1;
}
