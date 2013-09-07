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
    Mat cdst;

    src = imread(argv[1]);
    
    blur(src, src, Size(3,3));

    // Canny Edge Detection
    Canny(src, dest, 50, 200, 3) ;
    
    // Convert the image to grayscale
    cvtColor(dest, cdst, CV_RGB2GRAY);

    vector<Vec2f> lines;
    HoughLines(cdst, lines, 1, CV_PI/180, 100, 0, 0);

    // for(size_t i=0; i<lines.size(); i++ ){
    //     float rho = lines[i][0], theta = lines[i][1];
    //     Point pt1, pt2;
    //     double a = cos(theta), b = sin(theta);
    //     double x0 = a*rho, y0=b*rho;
    //     pt1.x = cvRound(x0+1000*(-b));
    //     pt1.y = cvRound(y0+1000*(a));
    //     pt2.x = cvRound(x0-1000*(-b));
    //     pt2.y = cvRound(y0-1000*(a));
    //     line(cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
    // }
    
    namedWindow("Window", CV_WINDOW_AUTOSIZE);
    imshow("Window", src);

    namedWindow("Testing Window", CV_WINDOW_AUTOSIZE);
    imshow("Testing Window",dest);

    waitKey(0);

	return 0;
}
