#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int findNumItems(char* filename) {
    FILE * fp = fopen(filename, "r"); 
    if (fp == NULL) {
        //Error message printf("Inventory file DOES NOT EXIST! Exiting ...");
        exit(1);
    }
    char chr = getc(fp);
    int itemNumber = 0;

    while (chr != EOF) {
        if (chr == '\n') {
            itemNumber ++;
        }
        chr = getc(fp);
    }
    fclose(fp);

    return itemNumber;
}

void readPreviousOutputFile(char* filename, item** itemArray) {

    FILE * fp = fopen(filename, "r");
    if (fp == NULL) {
        //Error message printf("Could not open previous output file\n");
        exit(0);
    }

    char line[100];
    int itemIndex = 0;

    while (fgets(line, 100, fp)) {

        item* currentItem = (item*)malloc(sizeof(item));
        sscanf(line, "%s %d", currentItem->name, &(currentItem->amount));
        itemArray[itemIndex] = currentItem;

        itemIndex++;
    }
    fclose(fp);
}

// return -1 if item doesn't exist, return 0 on success
int modifyItem(item* desiredItem, char* numberChange, item** itemArray, int itemNumber) {

    int numberMod = atoi(numberChange);

    for (int counter = 0; counter < itemNumber+1; counter++) {
        if (strcmp(itemArray[counter]->name, desiredItem->name) == 0) {
            itemArray[counter]->amount = itemArray[counter]->amount + numberMod;
        }
    }
    return 0;
}

// function that controls everything to do with modifying the item's amount
void modeModify(item** itemArray, int itemNumber) {
    int itemIndex = 0;
    while (itemIndex < itemNumber+1) {
        item* desiredItem = itemArray[itemIndex];

        char numberChange[100];
       // printf("How many %s would you like to add? ", desiredItem->name);
       // fgets(numberChange, 100, stdin);
        numberChange[strcspn(numberChange, "\n")] = 0;
        // fflush(stdin);

        int check = modifyItem(desiredItem, numberChange, itemArray, itemNumber);
        if (check == -1) {
           //Error message  printf("The item you are trying to modify does not currently exist\n");
        }
        itemIndex++;
    }
}

void writeOutputFile(char* filename, item** itemArray, int itemNumber) {

    FILE * fp = fopen(filename, "w");
    if (fp == NULL) {
        //Error message printf("Could not open output file\n");
        exit(0);
    }
    for (int line = 0; line < itemNumber+1; line++) {
        fprintf(fp, "%s %d\n", itemArray[line]->name, itemArray[line]->amount);
    }

    fclose(fp);
}

void freeMemory(item** itemArray, int numItems){

    for(int i = 0; i<numItems; i++){
        free(itemArray[i]);
    }
    // Free the pointer to the array
    free(itemArray);

}

void printInventory(item** itemArray, int numItems){

    //printf("\n---------------------------------\n");
    //printf("|%11s%7s|%9s%3s|\n", "Item", " ", "Amount", " ");
    //printf("---------------------------------\n");

    for (int j = 0; j < numItems+1; j++) {
       // printf("| %-16s | %10d |\n", itemArray[j]->name, itemArray[j]->amount);
    }
   // printf("---------------------------------\n\n");

    return;
}
