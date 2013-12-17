#ifndef __BALLDETECT_H_INCLUDED__
#define __BALLDETECT_H_INCLUDED__

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;
using namespace cv;

class ballDetect{

    // max number of objects to be detected in frame
    static const int MAX_NUM_OBJECTS = 50;

    //minimum and maximum object area
    // static const int MIN_OBJECT_AREA = 5*5;
    static const int MIN_OBJECT_AREA = 200;

    // static const int MAX_OBJECT_AREA = 20*20;
    static const int MAX_OBJECT_AREA = 400;

    //FRAME_HEIGHT*FRAME_WIDTH/1.5;

    //default capture width and height
    static const int FRAME_WIDTH = 640;
    static const int FRAME_HEIGHT = 480;
    Scalar *minval, *maxval;

    int shot, shotTemp, shotStart, flag;
    int contourTemp, contourCount;
    int xPrev, yPrev;

    public:

    ballDetect();
    string intToString(int);
    void drawObject(int, int, Mat &);
    void morphOps(Mat &);
    void trackFilteredObject(int &, int &, Mat, Mat &);
    void initDetect(char *);
    void detectShot();
};

#endif
