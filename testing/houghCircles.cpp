#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;
/** @function main */
int main(int argc, char** argv)
{
      Mat src, src_gray;
        /// Read the image
      src = imread(argv[1],1);

      if(!src.data){
          return -1;
      }

      cvtColor(src, src_gray, CV_BGR2GRAY);
      GaussianBlur(src_gray, src_gray, Size(9,9), 2, 2);
      // inRange(src_gray, Scalar(0,0,0),
      //       Scalar(255,255,50), src_gray);
      // Canny(src_gray,src_gray , 100, 100*3,5);

      vector<Vec3f> circles;

      // HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200,100, 0,0);
      HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/64, 10,15, 5,20);

      for(size_t i=0; i<circles.size(); ++i){
          Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
          int radius = cvRound(circles[i][2]);

          circle(src, center, 3, Scalar(0,255,0), -1, 8,0);
          circle(src, center, radius,   Scalar(0,0,255), 3, 8, 0);
      }
      namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
      imshow("Hough Circle Transform Demo",src);

      waitKey(0);

      return 0;
}
