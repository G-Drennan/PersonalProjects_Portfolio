#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "bitmap.h"
#include "CamDetectFuncs.h"

int NumLinesInTxtFile(char* fname){
 
    char line[10][BUFFER];      int i = 0;	

    // open a txt file
    FILE *fptr;     fptr = fopen(fname, "r");
    
    // store the lines into an array and count how many there are	
    while(fgets(line[i], BUFFER, fptr) )
        i++;

    // close the file and return the number of lines
    fclose(fptr);
    return i;
}

void GetMidNDiffHue(int *midHue,int *diffHue, int *Saturat, int* Value, char *fname, char** obj){
    FILE* fptr;
        fptr = fopen(fname, "r"); 
        int num=0;
        int len = NumLinesInTxtFile(fname);
        char line[BUFFER];
        char* string;
        // Retrive information from the txt file
        while(fgets(line, BUFFER, fptr)!=NULL && num<len){
            
            string = strtok(line," ");
            // give apropirate memory to obj
            obj[num] = malloc(sizeof(char) * strlen(string));  
            // copy the string into the arr obj thats returned
            strcpy(obj[num],string); 

            // get the midhue & mid diff, satureation & value as intergers
            char *token; 
             
            token = strtok(NULL, " ");
            midHue[num]= (int)atol(token); //mid hue

            token = strtok(NULL, " ");
            diffHue[num] = (int)atol(token); //hue diff

            token = strtok(NULL, " ");
            Saturat[num] = (int)atol(token); // saturation

            token = strtok(NULL, " ");
            Value[num] = (int)atol(token); // value
            num++;    
        }
        fclose(fptr);
}

void showCal(char *fname){

    printf("Calibrated Objects:\n"); 
    int len=NumLinesInTxtFile(fname);
    int midHue[len], diffHue[len], Sat[len], Val[len];
    char  **obj = malloc(sizeof(char*)*len);

    GetMidNDiffHue(midHue, diffHue, Sat, Val, fname, obj);
    
    //display the information from the txt file
    for(int n=0; n<len; n++){ 
        printf("%s: ",obj[n]);
        free(obj[n]);
        printf("Hue: %d", midHue[n]); //mid hue
        printf(" (Max. Diff: %d),", diffHue[n]); //hue diff
        printf(" Min. SV: %d", Sat[n]);
        printf(" %d\n", Val[n]);
        //free(obj[n]); //free the obj[n]
    }

    // Free the whole obj
    free(obj); 
}

void Calibrate(char *fname){ 
    
    Bmp CalImage;
    printf("%s ", fname);

        //Create the file name from the inputed name
        char fileName[BUFFER]= "images/";
        strcat(fileName, fname);
        strcat(fileName, ".bmp");

        // get infomation from the image
        CalImage = read_bmp(fileName);
        // get the min and max hue for every pixel in the modle 50x50 pixels
        // set Max to the lowest value and Min to the highest value 
        int MaxHue=0, MinHue=360;   
        HSV ImageHSV; 
        for(int rows=((CalImage.height/2)-24); rows<=((CalImage.height/2)+24); rows++){    
            for(int cols=((CalImage.width/2)-24); cols<=((CalImage.width/2)+24); cols++){
                unsigned char *arrRGB = CalImage.pixels[rows][cols];
                
                ImageHSV = rgb2hsv(arrRGB);
                //compare to the max and min hues
                if(ImageHSV.hue >= MaxHue)
                    MaxHue = ImageHSV.hue;   
                if(ImageHSV.hue <= MinHue)
                     MinHue = ImageHSV.hue; 
            }
        }

        int hueMid=hue_midpoint(MinHue, MaxHue);
        printf("%d ", hueMid);
        
        // Find the greatest distance
        int hueDiff = hue_difference(hueMid, MaxHue);
        if(hueDiff > hue_difference(hueMid, MinHue))
          hueDiff = hue_difference(hueMid, MinHue);  
        
        printf("%d", hueDiff);
        printf(" 50 30\n"); // Min saturation and min Value given
}

void enque(Que* q, int x, int y){
    q->rear = (q->rear+1)%q->capacity;
    q->xArr[q->rear] = x;
    q->yArr[q->rear] = y;
    (q->size)++;
}

void deque(Que* q, int* x, int* y){
    *x = q->xArr[q->front];
    *y = q->yArr[q->front];
    q->front = (q->front+1)%q->capacity;
    (q->size)--;
}

int inQ(Que* q, int x, int y){

    int f = q->front;
    while(f % q->capacity !=q->rear){
        if(q->xArr[f%q->capacity]==x && q->yArr[f%q->capacity]==y){
            return 1;
        }
        f++;
    }

    if(q->xArr[f%q->capacity]==x && q->yArr[f%q->capacity]==y){
            return 1;
    }

    return 0;
}

int inVisited(int* VisX, int* VisY, int x, int y, int count){

    for(int i=0; i<count; i++){
        if(VisX[i]==x && VisY[i]==y){
            return 1;
        }
    }
    return 0;
}

int findIntInMatrix(int value, int* x, int *y, int width, int height, int matrix[height][width]){
    
    for(int row=0; row<height; row++){
        for(int cols=0; cols<width; cols++){
            if(matrix[row][cols]==value){
                *x=cols;
                *y=row;
                return 1;
            }
            else{
                continue;
            }
        }
    }
    // Didn't find the value
    return 0;
}

void findObjsBFS(int x, int y, int rowsLen, int colsLen, int matrix[rowsLen][colsLen], char* obj, Bmp NewImage){
    Que* q = (Que*)malloc(sizeof(Que));

    q->front = 0;   q->size = 0;
    q->capacity = colsLen*rowsLen;
    q->rear = (q->capacity) -1;

    q->xArr = malloc(sizeof(int)*(q->capacity));
    q->yArr = malloc(sizeof(int)*(q->capacity));
    int visitedX[q->capacity], visitedY[q->capacity];
            
    // Breath first search 
    while(1){   
        int c=0; // Rest the count and max and min values.
        int maxX=0, minX=colsLen, maxY=0, minY=rowsLen;
        enque(q, x, y); 
        while(q->size>0){

            deque(q, &x,&y); 
            visitedX[c]=x;  visitedY[c]=y;
            c++; 

            // store the max and min x y coords 
            if(x>maxX)
                maxX=x;
            if(x<minX) 
                minX=x;
            if(y>maxY)
                maxY=y; 
            if(y<minY) 
                minY=y;

            // add the pixels next to the current image to the que.
            if( (x+1)<colsLen && matrix[y][x+1]==1 &&
                !inVisited(visitedX, visitedY, x+1, y,c) && !inQ(q,x+1,y)   ){
                enque(q,x+1,y);
            }
            if( (y+1)<rowsLen && matrix[y+1][x]==1 && 
                !inVisited(visitedX, visitedY, x, y+1,c) && !inQ(q,x,y+1)   ){
                enque(q,x,y+1);
            }
            if( (x-1)>=0 && matrix[y][x-1]==1 && 
                !inVisited(visitedX, visitedY, x-1, y,c) && !inQ(q,x-1,y)   ){
                enque(q,x-1,y);
            }
            if( (y-1)>=0 && matrix[y-1][x]==1 && 
                !inVisited(visitedX, visitedY, x, y-1,c) && !inQ(q,x,y-1)   ){
                    enque(q,x,y-1);
            }
        } 

        // clear the obj thats been visited so that it wont be visited again.
        for(int n=0; n<c; n++){ 
            matrix[ visitedY[n] ][ visitedX[n] ]=0;
        }
        
        if((maxX-minX+1>=20) && (maxY-minY+1>=20)){
            printf("Detected %s: ", obj); 
            printf("%d %d ", minX, minY);// x, y
            printf("%d %d\n", maxX-minX+1, maxY-minY+1);//width, height

            // show the box on the image.
            draw_box(NewImage, minX, minY, maxX-minX+1, maxY-minY+1);
            write_bmp(NewImage, "NewImage.bmp");
        }  
                
        // next obj find its location             
        if(findIntInMatrix(1, &x, &y, colsLen, rowsLen, matrix)==0){
            return; //no more obj then move onto the next obj to detect
        }
    }
}

void threshold(Bmp DisImage, int MaxHue, int MinHue, int val, int sat, 
                int rowsLen, int colsLen, int matrix[rowsLen][colsLen], int *x, int *y){

    HSV ImageHSV; 
    //threshold the image by go backwards thru the image. 
    // As to ensure the last values of x and y are the first value in the image.
    for(int r=(rowsLen-1); r>=0; r--){   
        for(int c=(colsLen-1); c>=0; c--){
            unsigned char *arrRGB = DisImage.pixels[r][c];
            ImageHSV = rgb2hsv(arrRGB);

            // If the obj is found mark with a 1 in the matirx
            if( (ImageHSV.hue <= MaxHue && ImageHSV.hue >= MinHue) && 
                (ImageHSV.value >= val &&
                 ImageHSV.saturation >= sat) ){ 
                        
                matrix[r][c]=1;
                //set the starting coordinates 
                *x=c; *y=r; // updated most loops            
            } 
            // else set the matirx as zero. 
            else{ 
                matrix[r][c]=0; //not the obj we want.
            }               
        }
    }
}


void DetectObj(char* CalibratedTxt, char* ImageName){
    int lines = NumLinesInTxtFile(CalibratedTxt); 
    int midHue[lines], diffHue[lines], sat[lines], val[lines];
    char  **obj = malloc(sizeof(char*)*lines);
    // Get the infomation on the objects from the txt file
    GetMidNDiffHue(midHue, diffHue, sat, val, CalibratedTxt, obj);

    // Read the image file.
    Bmp DisImage = read_bmp(ImageName); 
    int rowsLen =  DisImage.height, colsLen= DisImage.width;
    int matrix[rowsLen][colsLen];
    
    // copy the image for editing
    Bmp NewImage = copy_bmp(DisImage); 

    // Go thru each obj
    for(int objsIndex=0; objsIndex<lines; objsIndex++){
        
        // Find the max and min hue.
        int MaxHue, MinHue, x=0, y=0; 
        MaxHue = midHue[objsIndex] + diffHue[objsIndex];
        MinHue = midHue[objsIndex] - diffHue[objsIndex];
      
        threshold(DisImage, MaxHue, MinHue, val[objsIndex], sat[objsIndex], 
            rowsLen, colsLen, matrix, &x, &y);
            
        // Create a que for the breath first search
        findObjsBFS(x, y, rowsLen, colsLen, matrix, obj[objsIndex], NewImage);
        free(obj[objsIndex]); //free the obj                
    } 

    // free obj and image
    free_bmp(NewImage);
    free(obj); // Free the whole obj
}

