/*******************************************************************************************************************
 * Author: Sagar Rakshe 
 * Date: 
 * Problem Statement: Setting Region of Interest in the image(ROI).
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
    string filename = "video.avi";
    VideoCapture capture(filename);

    Mat frame;
    if(!capture.isOpened()){
        fprintf(stderr,"Error: opening video");
        exit(EXIT_FAILURE);
    }
    namedWindow("Testing Window", 1);
    
    while(1){
        if(!capture.read(frame)){
            break;
        }
        Mat subImage = frame(cvRect(150,150,200,200));
        imshow("Testing Window", subImage);
        char key = waitKey(30);
        if(key==27){
            break;
        }
    }

    cvDestroyWindow("Testing Window");

	return 0;
}
