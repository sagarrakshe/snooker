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
    // cvInRangeS(imgHSV, cvScalar(0,0,0), cvScalar(255,255,50), thresholdedImg);

    // Detect Yellow Ball
    cvInRangeS(imgHSV, cvScalar(20,100,100), cvScalar(30,255,255), thresholdedImg);

    cvReleaseImage(&imgHSV);
    
    return thresholdedImg;
}

int main(int argc, char *argv[])
{
    IplImage *src, *image, *frame;
    
    CvCapture *capture;
    
    CvMoments *moments = (CvMoments*)malloc(sizeof(CvMoments));
    
    double moment10, moment01, area;
   
    static int posX=0, posY=0;
    int lastX=posX, lastY=posY;
    
    // cvMoments(thresdedimage, moments, 1);
    src = cvLoadImage(argv[2]);
    // image = GetThresholdedImage(src);

    capture = cvCreateFileCapture(argv[1]);

    cvNamedWindow("Detect yellow Ball",CV_WINDOW_AUTOSIZE);
    cvNamedWindow("Threshold", CV_WINDOW_AUTOSIZE);
    while(1){
        frame = cvQueryFrame(capture);
        if(!frame)
            break;

        image = GetThresholdedImage(frame);

        cvMoments(image, moments, 1);
        moment10 = cvGetSpatialMoment(moments, 1, 0);
        moment01 = cvGetSpatialMoment(moments, 0, 1);
        area = cvGetCentralMoment(moments, 0, 0);
        
        // cout<<moment10<<"\t"<<moment01<<"\t"<<area<<endl;
        posX = moment10/area;
        posY = moment01/area;

        if(lastX>0 && lastY>0 && posX>0 && posY>0)
        {
            // Draw a yellow line from the previous point to the current point
            cvLine(src, cvPoint(posX, posY), cvPoint(lastX, lastY), cvScalar(0,255,255), 1);        
            cout<<posX<<"\t"<<posY<<endl;
        }

        cvShowImage("Detect yellow Ball", src);
        cvShowImage("Threshold", image);
        
        lastX = posX;
        lastY = posY;

        char c = cvWaitKey(33);
        if(c==27){
            break;
        }
    }
    // cvWaitKey(0);

	return 0;
}
