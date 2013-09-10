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
    // pyrUp(src, src);

    /*Converts an image from one color space to another*/
    cvtColor(src, src_gray, CV_BGR2HSV);
    blur(src_gray, src_gray, Size(3,3));
    

    //Black ball detection
    inRange(src_gray, Scalar(0,0,0),
            Scalar(255,255,50), processed);
    Canny(processed, blackBall, 100, 100*3,5);
    
    vector<Vec3f> circles;
    
    HoughCircles(blackBall,circles, CV_HOUGH_GRADIENT,1,src_gray.rows/64,10,15,5,20);
    
    // for( size_t i = 0; i < circles.size(); i++ ) {
    //     Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
    //     int radius = cvRound(circles[i][2]);
    //     
    //     /* circle center*/
    //     circle( src, center, 3, Scalar(150,255,150), -1, 8, 0 );
    //     cout<<i<<"\t"<<center<<endl; 
    //     /* circle outline*/
    //     circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );   
    // }

    // For now sake it's hard-coded logic, will make generalized once game is finalized.
    int height,width;
    
    height = abs(circles[0][1]-circles[2][1]);
    width = abs(circles[0][0]-circles[2][0]);

    cout<<circles[0][0]<<" "<<circles[0][1]<<endl;
    cout<<height<<"\t"<<width<<endl;
    Mat subImage = src(cvRect(circles[0][0],circles[0][1],width,height));

    namedWindow( "src", CV_WINDOW_AUTOSIZE );
    namedWindow( "subimage", CV_WINDOW_AUTOSIZE );

    imshow( "src", src);
    imshow( "subimage", subImage);
    
    waitKey(0);

    return 0;
}
