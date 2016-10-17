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

using namespace cv;

int main(int argc, char** argv){
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

	return 1;
}
