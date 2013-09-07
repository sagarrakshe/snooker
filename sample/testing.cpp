/*******************************************************************************************************************
 * Author: Sagar Rakshe 
 * Date: 
 * Problem Statement: 
*******************************************************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, char *argv[])
{
    Mat source, dest;

    source = imread(argv[1]);
    
    resize(source, dest, Size(), 2, 2, CV_INTER_LINEAR);
    imwrite("newImage.png", dest);

    namedWindow("Testing Window", CV_WINDOW_AUTOSIZE);
    imshow("Testing Window", source);
    waitKey(0);

	return 0;
}
