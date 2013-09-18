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
    string filename = "../media/game.avi";
    VideoCapture capture(filename);

    Mat frame,src_gray,processed,white;
    if(!capture.isOpened()){
        fprintf(stderr,"Error: opening video");
        exit(EXIT_FAILURE);
    }
    namedWindow("Testing", 1);
    
    while(1){
        if(!capture.read(frame)){
            break;
        }
       
        //my-logic 
        pyrUp(frame,frame);
        // resize(frame, frame, Size(), 1.5,1.5,INTER_CUBIC);
        cvtColor(frame,src_gray,CV_BGR2HSV);
        blur(src_gray, src_gray, Size(3,3));
    
        inRange(src_gray, Scalar(0,0,200), Scalar(255,50,255), processed);

        // Canny(processed, white, 100, 100*3,5);
        vector<Vec3f> circles;
        HoughCircles(processed,circles, CV_HOUGH_GRADIENT,1,src_gray.rows/64,10,15,5,20);
        for( size_t i = 0; i < circles.size(); i++ ) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); int radius = cvRound(circles[i][2]);
            // circle center
            circle( frame, center, 3, Scalar(150,255,150), -1, 8, 0 );
            // circle outline
            circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
        putText(frame, "White", cvPoint(cvRound(circles[i][0])+10,cvRound(circles[i][1])-10), 
                FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,0), 1, CV_AA);
        cout<<"X: "<<cvRound(circles[i][0])<<"\tY: "<<cvRound(circles[i][1])<<endl;
        }
        imshow("Testing",frame);
        char key = waitKey(10);
        if(key==27){
            break;
        }
    }

    cvDestroyWindow("Testing");

	return 0;
}
