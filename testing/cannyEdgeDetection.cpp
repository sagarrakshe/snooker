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
    Mat src, dest;

    src = imread(argv[1]);
    
    blur(src, src, Size(3,3));

    // Convert the image to grayscale
    cvtColor(src, dest, CV_BGR2GRAY);

    // Canny Edge Detection
    Canny(dest, dest, 100, 300, 3) ;

    namedWindow("Window", CV_WINDOW_AUTOSIZE);
    imshow("Window", src);

    namedWindow("Testing Window", CV_WINDOW_AUTOSIZE);
    imshow("Testing Window", dest);

    waitKey(0);

	return 0;
}
