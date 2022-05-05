#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H
 
// all structs and funtions used in main and SM_main_funct.
struct State {
    int data;
    struct State* next;
};

struct StateMachine {
    int id;
    struct State** states;
};

typedef struct StateMachine StateMachine;
typedef struct State State;

// This function is used to access the functions to be exicuted.
//  This function matches a given int n to the state it reffers to.
void getState(int n);



//function used to create a linked list
// A linked list pointer is passed in State** arrRef
// And the newData is placed in the list
void push(State** arrRef, int newData);

// Function to reverse the linked list
// takes input as a pointer to a linked list arrRef
void reverse(State** arrRef);

// Takes pointer of a linked list and a desired index
// as arguments and returns the data that is found at the index
int GetNth(State* arr, int index);



/* checks that the inputed signals for a state_machine are within bounds
struct StateMachine* ID and returns a 1 if the inputted signal are valid else 
it returns a 0.
    @in StateMachine* ID is a struct created with an ID and a link list
    @in arrLen is the lenght of the arr
    @in indexN is the curretn statemachine index ID we are working on
    @out 0 for false 1 for true*/
int ValidSig(StateMachine* ID,int arrLen, int indexN);

/*ensures that a transition_signal is unque for each state in the 
struct StateMachine* ID
    @in StateMachine* ID is a struct created with an ID and a link list
    @in arrLen is the lenght of the arr
    @in indexN is the curretn statemachine index ID we are working on
    @out 0 for false 1 for true*/
int nonDetermin(StateMachine* ID,int arrLen, int indexN);



/* find the index the ID is stored at
    @in inputNum is the ID you are trying to find in ID
    @in StateMachine* ID is a struct created with an ID and a link list
    @out The index in StateMachine* ID that refferes to the ID of the state_machine*/
int WhatIsTheIdIndex(int inputNum,StateMachine* ID);

/* sorts an array of int into accending order
    @in array arr and its length len
    @out an arr in a sorted form*/
int* sortAccend(int *arr, int len);

/* prints the number of states in an state_machine id and 
returns an new array with each state that was recorded
    @in len is the length of the orignial array
    @in index is the location of the state machine being counted
    @in StateMachine* ID is a struct created with an ID and a link list
    @in lenNewArr is the length of the new array thats 
    @out lenNewArr returned to count the number of states
    @out SortArr is the sorted New array with each state in
         the state machine in accending order */
int* NumStatesCount(int len, StateMachine* ID, int index, int *lenNewArr);

/* this function makes state transitions and 
updates an int in the array last a state

indexSM is the index we are working at
    @in id the id of the state machine thats being inquired
    @in TransSig is the signal type that causes a transion 
    @in StateMachine* ID is a struct created with an ID and a link list
    @in State* arrLenStore is an arr of int that reffernece the 
    @in length of an ID at it relevent index 
    @out LastState is where the state_machine is currently*/
int StateOpFunc(int indexSM, int id,int TransSig, StateMachine* ID, State* arrLenStore, int LastState);

/* indexSM is the index we are working at
    @in id the id of the state machine thats being inquired
    @in StateMachine* ID is a struct created with an ID and a link list
    @in State* arrLenStore is an arr of int that reffernece the 
    @in LastState is where the state_machine is currently */
void CurrentStateTMS(int id, StateMachine* ID, int *CurrentState);

/*indexSM is the index we are working at
    @in id the id of the state machine thats being inquired
    @in StateMachine* ID is a struct created with an ID and a link list
    @in State* arrLenStore is an arr of int that reffernece the 
    @in LastState is where the state_machine is currently*/
void TransSingAvailable(int id, StateMachine* ID, int *CurrentState, State* arrLenStore);

/*Provides all information on a state_machine
    @in id id the id of the state machine thats being inquired
    @in StateMachine* ID is a struct created with an ID and a link list
    @in State* arrLenStore is an arr of int that reffernece the 
        length of an ID at it relevent index */
void InformSMID(int id, StateMachine* ID, State* arrLenStore);

#endif
