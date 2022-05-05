#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// ./inventory
int main(void) {

    char* filename = "inventoryFile.txt";
    int itemNumber = findNumItems(filename);

    item** itemArray = (item**)malloc(sizeof(item*)*itemNumber);

    readPreviousOutputFile(filename, itemArray);

    modeModify(itemArray, itemNumber);

    printf("\nHere is a list of everything in your inventory:\n");

    printInventory(itemArray, itemNumber);

    writeOutputFile("missingItems.txt", itemArray, itemNumber);

    freeMemory(itemArray, itemNumber);

    return 0;
}
