#ifndef MAIN_AANS
#define MAIN_AANS

// SM_Main_funct.c  SM_Main_funct.h that perform/ 
// runs the majority of the program.

/* This block takes and stores user input on the state machines
        they wish to initalize. It also check that the input is valid.
        @var StateMachine** ID,State a struct that contrians a int id and a int linked list
        @var State** arrLenStore an arr of lengths for each id
        @in int NumStates is the initalized states the user is going to make*/        
int GetSMID(StateMachine* ID,State* arrLenStore, int NumStates);

 /*Process user input to control the state machines
    @in StateMachine* ID a struct that contrians a int id and a int linked list
    @in State* arrLenStore an arr of lengths for each id
    @in int NumStates how many state_machine id were created */
void ControlSM(StateMachine* ID, State* arrLenStore, int NumStates);

#endif
