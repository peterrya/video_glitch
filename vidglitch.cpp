/* 
 *Opens video and procceses it frame by frame
*/

#include "opencv2/videoio.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cv.h>
#include <highgui.h>

typedef unsigned char byte;
using namespace cv;

std::vector<byte> mat_to_bytes (Mat frame)
{
    	int size = frame.total() * frame.elemSize();
    	std::vector<byte> fr_bytes(size);
    	fr_bytes.assign(frame.datastart, frame.dataend);
    	return fr_bytes;
}

Mat bytes_to_mat (std::vector<byte> bytes,int width,int height)
{
    	Mat frame(height,width,CV_8UC3,bytes.data());  
    	return frame;
}

int main(int argc, char** argv){
	std::vector<byte> bytvec;
	Mat hold;
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
		
		
		imshow("Preview",frame);
		out << hold;
		if (waitKey(1) >=0){
			break;
		}
	}

	return 1;
}
