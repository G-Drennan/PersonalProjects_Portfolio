#ifndef _CAMDETFUN_
#define _CAMDETFUN_

#define BUFFER 1000

//main code 
/*
    Input: image file name
    output: Displays the information in the txt file as 
    e.g; Calibrated Objects:
    <File name>: Hue <midHue> (Max. Diff: <Diffhue>), Min. SV: 50 30
where <items in arrow brakets> are from the file
*/
void showCal(char *fname);

/*
This fuction takes the middle 50 pixles of an image and outputs the following
    Input: image file name
    output: <object_name> <Middle Hue> <Max. Hue Difference> <Minimum Saturation> <Minimum Value> 
    This output can be piped onto a txt file like so;
    ./cam_detect c redapple redapple.bmp >> calibration.txt
*/
void Calibrate(char *fname);

/*
This fuction takes the middle 50 pixles of an image and outputs the following
    Input: txt file name & image file name 
    output: A image with boxes around the object described in the txt file
   
*/
void DetectObj(char* CalibratedTxt, char* ImageName);

//Other function
/*
    Input: A interger value you are looking for, matrix with dimesions
    Output: A binary value 0 if the value isn't found 1 if it is found
    x & y are the coordinates in the matrix where the value is first found 
*/
int findIntInMatrix(int value, int* x, int *y, int width, 
                    int height, int matrix[height][width]);


//que orientated code
typedef struct Que{

    int front;
    int rear;
    int size;
    int capacity;

    int* xArr;
    int* yArr;

}Que;

// Adds to the que
void enque(Que* q, int x, int y);
// Removes from the que, outputtting its x & y values
void deque(Que* q, int* x, int* y);

#endif
