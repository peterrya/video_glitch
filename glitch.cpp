#include "opencv2/videoio.hpp"
#include "opencv2/opencv.hpp"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/imgcodecs.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

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
