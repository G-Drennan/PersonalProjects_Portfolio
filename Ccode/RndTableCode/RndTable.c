#include <stdio.h> 
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

int RndBetween(int min, int max);
void questGenerator();
void NPCsGenerator();
//gcc -o go RndTable.c
int main(){
    //printf ("The random number is:\n"); 
   

    //generate random seed for making the random number
    time_t t;
    srand((unsigned) time(&t));
    printf("Select from the following options: quest, npcs, end.\n");
    char str1[20];
    scanf("%19s", str1);
    //tolower(str1);
    if(strcmp(str1, "quest")==0)
        questGenerator(); 
    else if (strcmp(str1, "end")==0)
        return 0;
    else if (strcmp(str1, "npcs")==0)
        NPCsGenerator();
    else{
        printf("The entered text doesn't match any of the options try again\n");
        main();
    }
        


    
}

void questGenerator(){
     char * list[] = {"Stop the dungeon’s monstrous inhabitants from raiding the surface world",
                     "Foil a villain’s evil scheme", 
                     "Destroy a magical threat inside the dungeon",
                     "Acquie treasure", 
                     "Find a particular item for a specific purpose",
                     "Retrieve a stolen item hidden in the dungeon", 
                     "Find information needed for a special purpose",
                     "Rescue a captive", 
                     "Discover the fate of a previous adventuring party",
                     "Find an NPC who disappeared in the area", 
                     "Hunt a specific monster", 
                     "Discover the nature and origin of a strange location or phenomenon",
                     "Pursue fleeing foes taking refuge in the dungeon", 
                     "Escape from captivity in the dungeon",
                     "Clear a ruin so it can be rebuilt and reoccupied",
                     "Discover why a villain is interested in the dungeon",
                     "Win a bet or complete a rite of passage by surviving in the dungeon for a certain amount of time",
                     "Parley with a villain in the dungeon",
                     "Hide from a threat outside the dungeon",
                     };
    int Quest1 = -1, Quest2 = -1;

    Quest1 = RndBetween(1, 20);

    if(Quest1!=20) 
        printf("\nQuest -  %s\n\n", list[Quest1-1]); 
    else{
        Quest1 = RndBetween(1, 19);
        printf("\nQuest -  %s", list[Quest1-1]); 
        Quest2 = RndBetween(1, 19); 
        while(Quest1==Quest2){ //make sure they are not equal
            Quest2 = RndBetween(1, 19);
        }
        printf(" &  %s\n\n", list[Quest2-1]);
    }
    main(); //go back to the start of main
}

void NPCsGenerator(){
    char * Abilities[] = { "Strength", "Dexterity", "Constitution",
    "Intelligence", "Wisdom", "Charisma"};
    int Ab1 = RndBetween(1, 6), Ab2 = RndBetween(1, 6);
    while(Ab1==Ab2){ //make sure they are not equal
        Ab2 = RndBetween(1, 6);
    }
    printf("\nAbilities: Low %s High %s\n\n", Abilities[Ab1-1], Abilities[Ab2-1]);
    main(); //go back to the start of main  
} 

int RndBetween(int min, int max){

    int InRange=0, num=-1;
    //int random_number = rand() % range + min;
    while(InRange==0){    
        num = rand() % (max) + min;
        if(num<=max || num>=min){
            InRange=1;
            return num;
        }

    }
    return -1;
} 
