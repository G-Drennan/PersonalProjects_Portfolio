#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct apple{
    char * colour;
    int weight;
};

int main(){
    // struct apple myApple = {"Red", 150};
    // printf("My apple is %s, and has a weight of %d grams\n", myApple.colour, myApple.weight);

    struct apple * basket = malloc(sizeof(struct apple) * 0);

    int counter = 0;
    char newCols [10][10];

    while(1){

        printf("Would you like to add an apple [y/n]? ");
        char answer;
        scanf(" %c", &answer);

        if (answer == 'y'){
            
            counter++;
            basket = realloc(basket, sizeof(struct apple) * counter);

            int weight;
            printf("How much does this apple weigh? ");
            scanf(" %d", &weight);
            printf("What colour is this apple? ");
            scanf(" %s", newCols[counter-1]);

            basket[counter-1].colour = newCols[counter-1];
            basket[counter-1].weight = weight;
            printf("\n");

        } else {
            break;
        }
    }

    printf("\nThere a %d apples in the basket\n", counter);
    for (int i = 0; i < counter; i++){
        printf("Apple %d is %s and weighs %d grams\n", i + 1, basket[i].colour, basket[i].weight);
    }
}

