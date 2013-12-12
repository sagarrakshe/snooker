#include "ballDetect.h"

Point white_initial, white_collide;
vector <Point> white_position;
// int white_flag=0;

ballDetect :: ballDetect(){

    this->minval = new Scalar(0, 0, 200); 
    this->maxval = new Scalar(255, 70, 255); 

    this->shot = 1;
    this->shotTemp = this->shotStart = this->flag = 0;
    this->contourTemp = this->contourCount = 0;
    this->xPrev = this->yPrev = 0;

    white_initial.x = 269;
    white_initial.y = 281;

    white_collide.x = -1;
    white_collide.y = -1;
}

string ballDetect :: intToString(int number){

    stringstream ss;
    ss << number;
    return ss.str();
}

void onMouseClick(int event,int x,int y,int flags, void* userdata)
{
    Mat img = *((Mat *)userdata);
    flags = 0;

    if(event == EVENT_LBUTTONDOWN)
    {
        // cout<<x<<" "<<y<<endl;
        if((x>=68+7 && x<=1091-7) && (y>=73+7 && y<=603-7)){
            white_collide.x = x;
            white_collide.y = y;
        }
    }		 

    else if  (event == EVENT_RBUTTONDOWN)
        setMouseCallback("source", NULL,NULL);
}

void ballDetect ::  drawObject(int x,  int y, Mat &frame){

    circle(frame, Point(x, y), 7, Scalar(0, 0, 0), 2);

    putText(frame, "Shot No. "+intToString(shot), Point(90, 40), 1, 1, Scalar(255, 0, 0), 2);
    putText(frame, "White", Point(x, y-5), 1, 1, Scalar(255, 255, 0), 1);

    // if(white_flag)
        white_position.push_back(Point(x,y));

    if((abs(x-xPrev)) && (abs(y-yPrev)) && !flag){
        // if(shotTemp>=10)
            // white_flag=1;
        if(shotTemp>20){
            flag=shotStart=1;
        }
        else
            shotTemp++;
    }

    if(contourCount==0) {
        if(contourTemp>15 && shotStart){
            shot++; 
            cout<<"Shot No: "<<shot<<endl;
            shotStart=flag=shotTemp=0;

            white_collide.x = white_collide.y = -1;
            white_initial.x =x;
            white_initial.y =y;
            cout<<"No. of points"<<white_position.size()<<endl;
            // for(int i=0;i<(int)white_position.size()-1;++i){
            //     line(frame, white_position[i], white_position[i+1], Scalar(255, 255, 255), 1, CV_AA); 
            // }
            white_position.clear();
            // white_flag=0;
        }
        else
            contourTemp++;
    }

    xPrev=x;
    yPrev=y;
}

void ballDetect :: morphOps(Mat &processed){

    Mat erodeElement = getStructuringElement(MORPH_ELLIPSE, Size(3, 3));
    Mat dilateElement = getStructuringElement(MORPH_ELLIPSE, Size(7, 7));

    erode(processed, processed, erodeElement);
    erode(processed, processed, erodeElement);

    dilate(processed, processed, dilateElement);
    dilate(processed, processed, dilateElement);
}

void ballDetect :: trackFilteredObject(int &x, int &y, Mat threshold, Mat &cameraFeed){

    Mat temp;
    threshold.copyTo(temp);

    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

    findContours(temp, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE );

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
                drawObject(x, y, cameraFeed);
            }
        }
    }
}

void ballDetect :: initDetect(char *videoInput){

    VideoCapture capture;
    Mat src, src_HSV, processed;
    int x=0; int y=0; 

    Mat currentFrame, back, fore;   
    BackgroundSubtractorMOG2 bg;

    std::vector<std::vector<cv::Point> > contours;

    capture.open(videoInput);
    capture.set(CV_CAP_PROP_FRAME_WIDTH, FRAME_WIDTH);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, FRAME_HEIGHT);

    // int xyz=1;

    while(1){

        // cout<<xyz++<<endl;
        capture.read(src);
        cvtColor(src, src_HSV, COLOR_BGR2HSV);

        bg.operator ()(src, fore);
        bg.getBackgroundImage(back);
        erode(fore, fore, Mat());
        dilate(fore, fore, Mat());
        findContours(fore, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
        // drawContours(src,  contours,  -1,  Scalar(0,  0,  255),  2);
        contourCount=contours.size();

        if(white_collide.x != -1 && white_collide.y!=-1){
            circle(src, white_collide, 2, Scalar(0, 0, 0), 2);
            circle(src, white_initial, 2, Scalar(0, 0, 0), 2);
            line(src, white_initial, white_collide, Scalar(255, 255, 255), 1, CV_AA);
        }

        inRange(src_HSV, *minval, *maxval, processed);
        morphOps(processed);
        trackFilteredObject(x, y, processed, src);

        for(int i=0;i<(int)white_position.size()-1;++i){
            line(src, white_position[i], white_position[i+1], Scalar(255, 255, 255), 1, CV_AA); 
        }
        while(white_collide.x == -1 && white_collide.y==-1){
            setMouseCallback("source", onMouseClick, &src);
            putText(src, "Specify Point", Point(750, 40), 1, 1, Scalar(255, 0, 0), 2);
            imshow("source", src);
            waitKey(5);
        }

        imshow("source", src);
        waitKey(5);
    }
}
