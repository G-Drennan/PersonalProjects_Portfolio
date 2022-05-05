#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "state_machine.h"

#define BUFFER 1000

void ControlSM(StateMachine* ID, State* arrLenStore, int NumStates){
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int LastState[NumStates];  

    for(int n=0; n<NumStates; n++){
            //the inital state for a SM id is the 0 state Initialise
            LastState[n] = 0;        
    }
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //Take the user input while there is still input
    while(1){
        //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        char order[BUFFER],*inputSig, *commandTM, *TypeOrder;
        int inputNums[10], i=0,ExitsIDs=0;
        
        //get the input and its relevent info.
        fgets(order,BUFFER,stdin);
        order[strlen(order) - 1] = '\0';

        //if the input is empty break and end program
        if(strlen(order)==0){
            break;
        }
        //What does the suer want to do?
        inputSig = strtok(order, " ");

        //Store the type of output we want
        TypeOrder = inputSig;
        
        while( inputSig != NULL ){
            
            // assumption on the lenght of SM is 4 input and TM input is 3
            if(i>=1 && isalpha(inputSig[0])==0){
                //start at index 1 of inputNums
                inputNums[i]= (int)atol(inputSig);
            }
            else if(i>=3 && isalpha(inputSig[0])!=0){
                // only stored in TM where it is the 4th input at the 3rd index
                //informs the type of querry the user wants
                commandTM = inputSig;
                
            }
            inputSig=strtok(NULL, " ");                
            i++;        
        }

        
        //check the ID being called is correct
        for(int k=0; k<NumStates; k++){
            if(inputNums[1] == ID[k].id){ 
                //printf("%d = %d\n",inputNums[1], ID[k].id);
                //if it does exist make ExitsIDs non zero
                ExitsIDs=1;
            }
        }
        // if not correct display an error message and continue processing input
        if(ExitsIDs==0){
            if(TypeOrder[0]=='S'){
                printf("Error: Invalid state machine ID for command: ID %d\n",inputNums[1]);
            }
            else if(TypeOrder[0]=='T'){
            printf("Error: Invalid state machine ID queried: ID %d\n",inputNums[1]);
            }
            continue;
        }


        //Process the input to output
        if(TypeOrder[0]=='S'){ //make a transition
            // Find the trassition from last state to the next state with the input signal 
            int indexSM=WhatIsTheIdIndex(inputNums[1],ID);
            LastState[indexSM]=StateOpFunc(indexSM, inputNums[1], inputNums[3],ID, arrLenStore, LastState[indexSM]);
            
            //if the error state was entered exit the program
            if(LastState[indexSM]==-1){
                break;
            }
        }

        else if (TypeOrder[0]=='T'){
            //expected input TM <state machine ID> <time stamp> <command>
            if(commandTM[0]=='a'){
                //give information of the state mahine
                InformSMID(inputNums[1], ID, arrLenStore);            
            }
            else if(commandTM[0]=='t'){ 
                //Display the valid transitions signals
                TransSingAvailable(inputNums[1], ID, LastState, arrLenStore);
            }
            else if (commandTM[0]=='s'){
                // Display the current state and its name 
                CurrentStateTMS(inputNums[1], ID, LastState);                }
            else{
                printf("Error: Unknown querying instruction command: %s\n",commandTM);
            }

        }

    }

}

int GetSMID(StateMachine* ID, State* arrLenStore, int NumStates){

    int intialState=0; // used to tell if the ID 0 was created

    
    int counterArr; // Used Keep trak of the size of arr in memeory.

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
        // ID after the fourth entered are ignored due to - realloc(): invalid next size
        if(n<3){ // n statrs at zero

            // crate a linked list to store the 
            // transitions of the current SM id
            State ** arr = (State **) malloc(sizeof(State*) * 0);
            
            counterArr=1;
            while( token != NULL ) {

                arr = realloc(arr, sizeof(State*) * counterArr);
                // convert token to int 
                storeNum = atol(token);
                
                // create the link list and add no. that linked list storeing the number      
                push(&arr[n], storeNum); 
                // Note arr[0] = ID[n].id This will not be used but is avalible

                // grab the next number from the input line 
                token = strtok(NULL, "> <");

                // keep track of the length of arr. Store it in its own linked list?
                arrLen++;
                counterArr++;
                
            }
            counterArr=0;
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
    }

    return 1;

}

