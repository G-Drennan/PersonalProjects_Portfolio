#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bitmap.h"
#include "CamDetectFuncs.h"   

int main(int argc, char **argv){ //argc==int argv=cha     

    if(argv[1][0]=='s')
        //Displaying a calibration file
        //expects ./cam_detect s test_calibrations/redblob.txt 
        showCal(argv[2]); 
    else if(argv[1][0]=='c' )
        // Calibrate the file
        // expects ./cam_detect c blueblob
        Calibrate(argv[2]);
    else if (argv[1][0]=='d') 
        //detect objs in an image. 
        //expects ./cam_detect d test_calibrations/redblob.txt images/redblob.bmp
        DetectObj(argv[2], argv[3]);                    
    else 
        printf("Incorrect input\n");
}

// ./cam_detect d test_calibrations/duck.txt images/combined001.bmp

