#include<iostream>
#include "ballDetect.h"

using namespace std;
using namespace cv;

int main(int argc, char **argv){

    ballDetect detect;
    
	// argv[1]="F:\\Vinay\\Dropbox\\BE Project\\Media\\Videos\\Test_New.avi";

    detect.initDetect(argv[1]);

    return 0;
}
