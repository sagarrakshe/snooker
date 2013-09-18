#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main(int argc, char **argv){

    Mat src,src_gray,processed,blue,pink,white,red,brown,black,yellow,temp;
    src = imread(argv[1]);

    pyrUp(src, src);
    // pyrUp(src, src,Size(2,2));
    // resize(src, src, Size(), 1.2,1.2,INTER_CUBIC);

    cvtColor(src, src_gray, CV_BGR2HSV);
    blur(src_gray, src_gray, Size(3,3));
    
    //white
    inRange(src_gray, Scalar(0,0,200), Scalar(255,50,255), processed);
    // Canny(processed, white, 100, 100*3,5);

    vector<Vec3f> circles;
    HoughCircles(processed,circles, CV_HOUGH_GRADIENT,1,src_gray.rows/64,10,15,5,20);
    for( size_t i = 0; i < circles.size(); i++ ) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1])); int radius = cvRound(circles[i][2]);
        circle( src, center, 3, Scalar(150,255,150), -1, 8, 0 );
        circle( src, center, radius, Scalar(0,0,255), 3, 8, 0 );        
        // cout<<circles[i][0]<<"\t"<<circles[i][1]<<endl;
    putText(src, "White", cvPoint(cvRound(circles[i][0])+5,cvRound(circles[i][1])-5), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,0), 1, CV_AA);
    }

    namedWindow( "src", CV_WINDOW_AUTOSIZE );
    imshow( "src", src);
    
    waitKey(0);
    
    return 0;
}
