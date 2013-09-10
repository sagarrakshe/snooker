/*******************************************************************************************************************
 * Author: Sagar Rakshe 
 * Date: 10/09/2013
 * Problem Statement: Detect Black Ball.
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

IplImage *GetThresholdedImage(IplImage *image){

    IplImage *imgHSV = cvCreateImage(cvGetSize(image), 8, 3);
    IplImage * thresholdedImg = cvCreateImage(cvGetSize(image), 8, 1);

    // Convert the image into HSV
    cvCvtColor(image, imgHSV, CV_BGR2HSV);

    // Detect Black Ball
    cvInRangeS(imgHSV, cvScalar(0,0,0), cvScalar(255,255,50), thresholdedImg);

    // Detect Yellow Ball
    // cvInRangeS(imgHSV, cvScalar(20,100,100), cvScalar(30,255,255), thresholdedImg);

    cvReleaseImage(&imgHSV);
    
    return thresholdedImg;
}

int main(int argc, char *argv[])
{
    IplImage *src, *image;

    src = cvLoadImage(argv[1]);

    image = GetThresholdedImage(src);

    namedWindow("Source", CV_WINDOW_AUTOSIZE);
    namedWindow("Threshold", CV_WINDOW_AUTOSIZE);

    cvShowImage("Source", src);
    cvShowImage("Threshold", image);

    waitKey(0);

	return 0;
}
