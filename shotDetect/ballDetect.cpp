#include "ballDetect.h"

int shot=1, shotTemp=0, shotStart=0, flag=0;
int contourCount=0, contourTemp=0;
int xPrev=0, yPrev=0;

ballDetect :: ballDetect(){

    this->minval = new Scalar(0,0,200); 
    this->maxval = new Scalar(255,70,255); 
}

string ballDetect :: intToString(int number){

    stringstream ss;
    ss << number;
    return ss.str();
}

void ballDetect ::  drawObject(int x, int y,Mat &frame){

    circle(frame,Point(x,y),7,Scalar(0,0,0),2);

    putText(frame,"Shot No. "+intToString(shot),Point(90,40),1,1,Scalar(255,0,0),2);
    putText(frame,"White",Point(x,y-5),1,1,Scalar(255,255,0),1);

    if((abs(x-xPrev)) && (abs(y-yPrev)) && !flag){
        if(shotTemp>20){
            flag=1;
            shotStart=1;
        }
        else
            shotTemp++;
    }

    if(contourCount==0)
    {
        if(contourTemp>15 && shotStart){
            shot++; 
            cout<<"Shot No: "<<shot<<endl;
            shotStart=0;
            flag=0;
        }
        else
            contourTemp++;
    }

    xPrev=x;
    yPrev=y;
}

void ballDetect :: morphOps(Mat &processed){

    Mat erodeElement = getStructuringElement( MORPH_ELLIPSE,Size(3,3));
    Mat dilateElement = getStructuringElement( MORPH_ELLIPSE,Size(7,7));

    erode(processed,processed,erodeElement);
    erode(processed,processed,erodeElement);

    dilate(processed,processed,dilateElement);
    dilate(processed,processed,dilateElement);
}

void ballDetect :: trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){

    Mat temp;
    threshold.copyTo(temp);

    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(temp,contours,hierarchy,CV_RETR_CCOMP,CV_CHAIN_APPROX_SIMPLE );

    double refArea = 0;
    bool objectFound = false;
    if (hierarchy.size() > 0) {
        int numObjects = hierarchy.size();

        if(numObjects<MAX_NUM_OBJECTS){
            for (int index = 0; index >= 0; index = hierarchy[index][0]) {

                Moments moment = moments((cv::Mat)contours[index]);
                double area = moment.m00;

                if(area>MIN_OBJECT_AREA && area<MAX_OBJECT_AREA && area>refArea){
                    x = moment.m10/area;
                    y = moment.m01/area;
                    objectFound = true;

                }else objectFound = false;
            }

            if(objectFound ==true){
                drawObject(x,y,cameraFeed);
            }
        }
    }
}

void ballDetect :: initDetect(char *videoInput){

    VideoCapture capture;
    Mat src,src_HSV,processed;
    int x=0; int y=0; 

    Mat currentFrame,back,fore;   
    BackgroundSubtractorMOG2 bg;

    std::vector<std::vector<cv::Point> > contours;
    capture.open(videoInput);
    capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    while(1){

        capture.read(src);
        cvtColor(src,src_HSV,COLOR_BGR2HSV);

        bg.operator ()(src,fore);
        bg.getBackgroundImage(back);
        erode(fore,fore,Mat());
        dilate(fore,fore,Mat());
        findContours(fore,contours,CV_RETR_EXTERNAL,CV_CHAIN_APPROX_NONE);
        // drawContours(src,contours,-1,Scalar(0,0,255),2);
        contourCount=contours.size();

        inRange(src_HSV,*minval,*maxval,processed);
        morphOps(processed);
        trackFilteredObject(x,y,processed,src);
        imshow("source",src);
        waitKey(5);
    }
}
