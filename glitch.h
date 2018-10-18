#ifndef GLITCH_H
#define GLITCH_H
#include "opencv2/videoio.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/imgcodecs.hpp"
#include "glitch.h"

typedef unsigned char byte;
using namespace cv;
std::vector<byte> mat_to_bytes (Mat frame);

Mat bytes_to_mat (std::vector<byte> bytes,int width,int height);

Mat glitch_bmp_row(Mat frame,int width,int height);

Mat glitch_bmp_col(Mat frame,int width,int height);

Mat glitch_bmp_ave(Mat frame,int width,int height);

Mat glitch_bmp_sort_varpass(Mat frame,int width,int height,int iter);
#endif
