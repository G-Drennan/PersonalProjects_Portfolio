#ifndef __FUNCTIONS_H_
#define __FUNCTIONS_H_

typedef struct {
    char name[100];
    int amount;
} item;

// these functions use the previous output file to build the array of items
int findNumItems(char* filename);
void readPreviousOutputFile(char* filename, item** itemArray);

// these functions pertain to the mode 'modify'
int checkInput(char* operation, char* numberChange);
int modifyItem(item* desiredItem, char* numberChange, item** itemArray, int itemNumber);
void modeModify(item** itemArray_ptr, int itemNumber);

// functions to write a new output file
void writeOutputFile(char* filename, item** itemArray, int itemNumber);

void freeMemory(item** itemArray, int numItems);

void printInventory(item** itemArray, int numItems);

#endif
