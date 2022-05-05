#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
 
#include "state_machine.h" // contains most functions used in the program
#include "operation_functions.h"
#include "SM_Main_funct.h" // contains larger funtions that drive the code

//Buffer used to initalize stings and fgets size
#define BUFFER 1000 

//int GetSMID(StateMachine** ID,State** arrLenStore, int NumStates);

int main(int argc, char** argv){   
    // ensure the correct input is placed in 
    if( argc!=2){
        printf("Error: Invalid input arguments\n");
        return 0;
    }

    // recored the expected number of state machines
    int NumStates=atol(argv[1]);

    StateMachine* ID = malloc(sizeof(StateMachine) * NumStates);
    State* arrLenStore = malloc(sizeof(State) * NumStates); 
    // was planing on making this a linked list however now 
    //  its a struct to relate it to make it similar/related to ID.
    
    /* This block takes and stores user input on the state machines
        they wish to initalize. It also checks that the input is valid.*/
    if(GetSMID(ID, arrLenStore, NumStates)==0){
        return 0;
    } 

    // display the ID that have been created
    for(int i=0; i<NumStates; i++){
        printf("State machine [ID: %d] has been initialised\n", ID[i].id);       
    }

    // Process user input to control the state machines
    ControlSM(ID, arrLenStore, NumStates);

    // free all the memory after use 
    free(ID);
    free(arrLenStore);
}





// ~Notes on the stuct and possible aproches to the problem possible junk code~

/* This block takes and stores user input on the state machines
        they wish to initalize. It also check that the input is valid.*/ 

    /*int intialState=0; // used to tell if the ID 0 was created

    for(int n=0; n<NumStates; n++){
        int storeNum, arrLen=0; 
        char *token, str[BUFFER];

        // get the user input
        fgets(str,BUFFER,stdin);
        str[strlen(str) - 1] = '\0'; 
        //printf("%s\n",str);

        // The first int in the input line is stored and 
        // use to start the strtok process 
        token= strtok(str, "> <");
        ID[n].id = atol(token);

        // Limited to 3 SM_IDs
        // ID after the fourth entered are ignored due to memory leak that causes a segfault
        if(n<3){ // n statrs at zero
            State ** arr = malloc(sizeof(State) * 0);
             
            while( token != NULL ) {

                // convert token to int 
                storeNum = atol(token);                 //printf( " %s", token ); //printf(" = %d\n", storeNum);
                
                // create the link list and add no. that linked list storeing the number      
                push(&arr[n], storeNum);
                // Note arr[0] = ID[n].id This will not be used but is avalible

                // grab the next number from the input line 
                token = strtok(NULL, "> <");

                // keep track of the length of arr. Store it in its own linked list?
                arrLen++;
            }
            // store the lenght of the current arr.
            arrLenStore[n].data = arrLen;
            //arrLenStore[n].next = &arrLenStore[n+1];

            // reverse the order of the linked list and store it
            reverse(&arr[n]); 
            ID[n].states = &arr[n];
        }

        // Only check the ID 0 exits for the initialise state 
        if(ID[n].id==0 && GetNth(*ID[n].states, 1)!=0){
            printf("Error: State Machine has no default starting state\n");
            free(ID);
            free(arrLenStore);
            return 0;
        }

        // does the inital state ID exist?
        if(ID[n].id==0){
            intialState=1;
        }

        // go thru each pair of states and transition signal
        // ensure they are determinist and a valid number
        if(nonDetermin(ID, arrLen, n)==0){
            free(ID);
            free(arrLenStore);
            return 0;
        }

        if(ValidSig(ID, arrLen, n)==0){
            free(ID);
            free(arrLenStore);
            return 0;
        }       
    }

    // if the intialState doesn't exist.
    if(intialState==0){
        printf("Error: State Machine has no default starting state\n");
        free(ID);
        free(arrLenStore);
        return 0;
    }*/

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/*struct State {
    int data;
    struct State* next;
};

struct StateMachine {
    int id;
    struct State** states;
};

typedef struct StateMachine StateMachine;
typedef struct State State;*/ 

    //char int float charORint float
    /*strtok(signalInput, " ") 
        switch between SM and TM 
        void function that takes 
        signalInput as the input, and the states ID and arr and arrlen*/
      
   //return 0;
   // GetNth(*ID[i].states, 0);  


