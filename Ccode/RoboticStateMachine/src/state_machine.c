#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "state_machine.h"
#include "operation_functions.h"
 
#define BUFFER 1000

// sorts an array of int into accending order
// Takes the array arr and its length len
int* sortAccend(int *arr, int len){
    
    int temp; // temporary var
    for (int i = 0; i < len; i++){ 
        for (int j = i + 1; j < len; j++) {          
            if (arr[i] > arr[j]) {
                //swap the values around
                temp =  arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return arr;

}

int WhatIsTheIdIndex(int inputNum, StateMachine* ID){
        int i=0;
        
        while(1){
            if(inputNum==ID[i].id){
                //reutrn with the index the inputNum is found at
                return i;
            }
            i++;
        }
        // error if here
        return -1;
}

int* NumStatesCount(int len, StateMachine* ID, int index, int *lenNewArr){

    int *NewArr = malloc(len*0); //assign memeory to the array

    int appears=0; //1=0, appears3=0;
    int i,n, count=1, add, TransSig;
    // loop the first value in the signal then the third
    // these are the states in the state machine ID
    for(add=0; add!=4; add+=2){ 

        for(n=1; n<len; n+=3){ //loop each Transiton siganl
            
            //store the Transiton siganl state we want to check against
            TransSig=GetNth(*ID[index].states, n+add);

            for(i=0; i<len; i++){
                //make sure the array has memmory that can be accessed
                if(sizeof(NewArr)!=0){ 
                    if(TransSig==NewArr[i]){
                        appears=1;
                        break; 
                    }
                }
            }
            
            if(appears==0 || count==1){
                //place the new trans signal inot the new arr
                NewArr = realloc(NewArr, count);
                NewArr[count-1] = TransSig;
                count++;
            }
            appears=0;
        }
    }

    // make count the same length as NewArr
    count--;
    *lenNewArr = count; //take out the length of this arr
    printf("Total number of states: %d\n", count);

    //Sort array in accending order
    int *SortArr = sortAccend(NewArr, count);
    return SortArr;

}

void InformSMID(int id, StateMachine* ID, State* arrLenStore){ 

    int LocationA=WhatIsTheIdIndex(id,ID);
    printf("SM %d (t = 0.00):\n", ID[LocationA].id);
                    
    int lenStatesArrA=0;
    int *StatesArrA=NumStatesCount(arrLenStore[LocationA].data, ID, LocationA, &lenStatesArrA);
                    
    int NumTransA=(arrLenStore[LocationA].data/3);
    printf("Total number of transitions: %d\n",NumTransA);
                    
    printf("State IDs: ["); //print the state IDs
    for(int q=0; q<lenStatesArrA;q++){
        if(q!=(lenStatesArrA-1)){
            printf("%d, ", StatesArrA[q]);
        } 
        else{
            printf("%d]", StatesArrA[q]);
        }
    }
    printf("\n");
 
}

//A char array used by two functions needs to act as a global var
char StateNames[20][30]={"Initialise","Idle","Sleep","On","Off",
                    "Reset","Setup","Rotate Arm","Close Grip","Open Grip",
                    "Analyse Scene","Verify Objects","Capture Image","Process Camera Data","Confirm Successful Grip",
                    "Confirm Chalice Location","Calculate Scene Uncertainty","Compute Covariance","B.P State","The Void"};

int StateOpFunc(int indexSM, int id,int TransSig, StateMachine* ID, State* arrLenStore, int LastState){
    int ComparValueF, compareSig, StateTo, FoundNDisplay=0;
    //state names array for refference
    /*char StateNames[20][30]={"Initialise","Idle","Sleep","On","Off",
                    "Reset","Setup","Rotate Arm","Close Grip","Open Grip",
                    "Analyse Scene","Verify Objects","Capture Image","Process Camera Data","Confirm Successful Grip",
                    "Confirm Chalice Location","Calculate Scene Uncertainty","Compute Covariance","B.P State","The Void"};*/

    for(int n=1; n<arrLenStore[indexSM].data; n+=3){
        // The state we are going from           
        ComparValueF = GetNth(*ID[indexSM].states,n);
        // the signal used to make the transition 
        compareSig = GetNth(*ID[indexSM].states,n+1);
        // The state we are going to
        StateTo = GetNth(*ID[indexSM].states,n+2);
        if(TransSig==4){
            printf("Error: Error state called - Exiting Program\n");
            FoundNDisplay=1;
            return -1; //error state
            break;
        }

        if(LastState==ComparValueF && TransSig==compareSig){
            printf("SM %d (t = 0.00): Transitioned from State: ", id);
            printf("%s to State: %s\n", StateNames[ComparValueF],StateNames[StateTo]);
            LastState=StateTo;

            //run the program associated with the state
            getState(StateTo); 
            
            // it has been found
            FoundNDisplay=1;
            // This var is used to indicate that the transition was made
            break;
        }
                    
    }

    // If it wasn't found or an error state
    if(FoundNDisplay==0 /*&& inputNums[3]!=4*/){
        printf("SM %d (t = 0.00): ", id);
        printf("Cannot transition from State: %s with signal %d\n", StateNames[LastState], TransSig);
    }

    /*will return either an updated last 
    state or the last states that was inputted*/
    return LastState;
}

void CurrentStateTMS(int id, StateMachine* ID, int *CurrentState){
    //state names array for refference
    /*char StateNames[20][30]={"Initialise","Idle","Sleep","On","Off",
                    "Reset","Setup","Rotate Arm","Close Grip","Open Grip",
                    "Analyse Scene","Verify Objects","Capture Image","Process Camera Data","Confirm Successful Grip",
                    "Confirm Chalice Location","Calculate Scene Uncertainty","Compute Covariance","B.P State","The Void"};*/

    int IndexS=WhatIsTheIdIndex(id,ID); //find the index
    //print the curretn state and it name
    printf("SM %d (t = 0.00): Current state: ", id);
    printf("[%d : %s]\n",CurrentState[IndexS], StateNames[CurrentState[IndexS]]);
}

void TransSingAvailable(int id, StateMachine* ID, int *CurrentState, State* arrLenStore){
    
    printf("SM %d (t = 0.00): Valid transition signals: ",id);
    int LocationT=WhatIsTheIdIndex(id,ID);// makes them unique to here
                    // what is the current state of this id?
    int lenghtT = arrLenStore[LocationT].data;
    int indexT=1;
    while(indexT < lenghtT){
        if(GetNth(*ID[LocationT].states,indexT)==CurrentState[LocationT]){
            printf("[%d : %d]", GetNth(*ID[LocationT].states,(indexT+1)),GetNth(*ID[LocationT].states,(indexT+2)));              
        }
        indexT+=3;
    }

    printf("\n");
}



int ValidSig(StateMachine* ID,int arrLen, int indexN){
    // variables used to check the input transition signals
        int aFromS, bSignal, cToS;  //aCheck, bCheck;
        // a is the first value we are going from Valid ranges; 0-19
        // b is the second value that indiaces the type of transition Valid ranges; 0-4
        // c is the last value the state we are going to Valid ranges; 0-19
        int n = indexN;

        /* each transition signal will be checked as a group.
            since the arrLen was initalized at zero the following code
            will not run if the arrLen = 0 and was never incremented*/      
        for(int stateIndex=1; stateIndex<arrLen; stateIndex+=3){
            //NumSig++; //count the num of signals
            // assign each inex of a state ID to a varaible
            aFromS=GetNth(*ID[n].states, stateIndex); // From state
            bSignal=GetNth(*ID[n].states, (stateIndex+1)); // signal
            cToS=GetNth(*ID[n].states, (stateIndex+2)); // to state
            //printf("%d,%d,%d\n",aFromS,bSignal, cToS);

            // check the states and signals are correct
            if(aFromS>19){
                printf("Error: State Machine state %d is invalid\n",aFromS);
                // return 0 if not valid
                return 0;
            }
            else if(bSignal>4){
                printf("Error: State Machine state %d is invalid\n",cToS);
                return 0;
            }
            else if(cToS>19){
                printf("Error: State Machine state %d is invalid\n",cToS);
                return 0;
            }
        }

        //Its valid
        return 1;
}

int nonDetermin(StateMachine* ID,int arrLen, int indexN){
    int aFromS, bSignal,  aCheck, bCheck;
    // a is the first value we are going from
    // b is the second value that indiaces the type of transition
    // check is the a or b we are comparing against

    for(int index=1; index<arrLen; index+=3){
            aFromS=GetNth(*ID[indexN].states, index); // From state
            bSignal=GetNth(*ID[indexN].states, (index+1)); // signal
            
            //compare with the rest of the transitions and not itself
            for(int i=1; i<arrLen; i+=3){
            aCheck=GetNth(*ID[indexN].states, i);
            bCheck=GetNth(*ID[indexN].states, i+1);
                if(aCheck==aFromS && bCheck==bSignal && i!=index){
                    printf("Error: State Machine is non-deterministic "
                    "(state %d has ambiguous transitions)\n", ID[indexN].id);
                    return 0;
                }
            }       
        }

        //Its deterministic
        return 1;
}

int GetNth(State* arr, int index){
    
    State* current = arr;
 
    // Count is the index of the current node 
    int count = 0;
    while (current != NULL) {
        // when the count = the index given output that value
        if (count == index)
            return (current->data);
        count++;
        current = current->next;
    }
 
    // if here an error has occured 
    return 0;
}

void reverse(State** arrRef){

    State* prev = NULL;
    State* current = *arrRef;
    State* next = NULL;
    // Move thru the linked list and swap the order
    while (current != NULL) {
        // Store next
        next = current->next;
 
        // Reverse current node pointer
        current->next = prev;
 
        // Move pointers one position ahead.
        prev = current;
        current = next;
    }
    *arrRef = prev;
}

void push(State** arrRef, int newData){
    // allocate node
    State* newNode = (State*)malloc(sizeof(State));
 
    // put in the data
    newNode->data = newData;
 
    // link the old list off the new node
    newNode->next = (*arrRef);
 
    // move the arr to point to the new node
    (*arrRef) = newNode;
}

void getState(int n){

    // find the relevent function
    switch (n){

        case 0:
        operation_zero();
        break;

        case 1:
        operation_one();
        break;

        case 2:
        operation_two();
        break;

        case 3:
        operation_three();
        break;

        case 4:
        operation_four();
        break;

        case 5:
        operation_five();
        break;

        case 6:
        operation_six();
        break;

        case 7:
        operation_seven();
        break;

        case 8:
        operation_eight();
        break;

        case 9:
        operation_nine();
        break;

        case 10:
        operation_ten();
        break;
        
        case 11:
        operation_eleven();
        break;

        case 12:
        operation_twelve();
        break;

        case 13:
        operation_thirteen();
        break;

        case 14:
        operation_fourteen();
        break;

        case 15:
        operation_fifteen();
        break;

        case 16:
        operation_sixteen();
        break;

        case 17:
        operation_seventeen();
        break;

        case 18:
        operation_eighteen();
        break;

        case 19:
        operation_nineteen();
        break;
    }
}

