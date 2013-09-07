// This is the program to detect the ball from the given image
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char **argv){
    
    Mat src, src_gray, processed, temp;
    Mat blueBall, pinkBall, whiteBall, redBall, brownBall, blackBall, yellowBall;
    
    if(argc<2){
        fprintf(stderr, "Usage: ./test <image-argument>\n");
        exit(1);
    }

    src = imread(argv[1]);

    /*Up-sampling(exapanding) the image - Laplacian Pyramid*/
    pyrUp(src, src);

    /*Converts an image from one color space to another*/
    cvtColor(src, src_gray, CV_BGR2HSV);

    blur(src_gray, src_gray, Size(3,3));
    
    /*
    opencv uses 0-180 for Hue
    Red     {0,150,150  10,255,255}
    White   {0,0,200    255,70,255}
    Black   {0,0,0      255,255,50}
    Blue    {120,0,0    130,255,255}
    Yellow  {25,150,140 35,255,255}
    Pink    {155,0,0    165,255,255}
    Inverted{40,0,0     130,255,255}
    */

    /*Blue ball detection*/
    /*
    inRange(src_gray, Scalar(120,0,0),
            Scalar(130,255,255), processed);
    Canny(processed, blueBall, 100, 100*3,5);
    */
    /*Pink ball detection
    inRange(src_gray, Scalar( 155,0,0),
            Scalar(165,255,255), processed);
    Canny(processed, pinkBall, 100, 100*3,5);
    bitwise_or(pinkBall, blueBall, temp);
    */
    /*White ball detection
    inRange(src_gray, Scalar(0,0,200),
            Scalar(255,50,255), processed);
    Canny(processed, whiteBall, 100, 100*3,5);
    bitwise_or(temp, whiteBall, temp);
    
    Red ball detection
    inRange(src_gray, Scalar(0,150,150),
            Scalar(10,255,255), processed);
    Canny(processed, redBall, 100, 100*3,5);
    bitwise_or(temp, redBall, temp);
    */
    //Black ball detection
    inRange(src_gray, Scalar(0,0,0),
            Scalar(255,255,50), processed);
    Canny(processed, blackBall, 100, 100*3,5);
    // bitwise_or(temp, blackBall, temp);
    /*
    Yellow ball detection
    inRange(src_gray, Scalar(25,150,140),
            Scalar(35,255,255), processed);
    Canny(processed, yellowBall, 100, 100*3,5);
    bitwise_or(temp, yellowBall, temp);
    
    Brown ball detection
    inRange(src_gray, Scalar(10,160,140),
            Scalar(20,220,200), processed);
    Canny(processed, brownBall, 100, 100*3,5);
    bitwise_or(temp, brownBall, processed);
    */
    vector<Vec3f> circles;
    
    HoughCircles(blackBall,circles, CV_HOUGH_GRADIENT,1,src_gray.rows/64,10,15,5,20);
    
    for( size_t i = 0; i < circles.size(); i++ ) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        
        /* circle center*/
        circle( src, center, 3, Scalar(150,255,150), -1, 8, 0 );
        
        /* circle outline*/
        circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );    
    }
    
    namedWindow( "src", CV_WINDOW_AUTOSIZE );
    namedWindow("processed ");

    imshow( "src", src);
    imshow("processed",processed);
    
    waitKey(0);

    return 0;
}
