#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

typedef struct player{
    char name[20];
    int score_value;
}player;


void write(char arq[], player *one);
void read(char arq[], player *one);


int main(void){
    player one;
    char arq[] = {"scores.bin"}; 
    int op;
    do{
        system("cls");
        printf("[1]Play\n[2]Scores\n: ");
        scanf("%i", &op);
        switch(op){
            case 1:
                printf("\nName: ");
                scanf("%s",&(one.name));
                fflush(stdin);
                one.score_value = play();
                write(arq,&one);
                break;
            case 2:
                
                break;
        }
    }while(op != 1 && op != 2);
}

void write(char arq[], player *one){
    FILE *score = fopen(arq,"ab");
    if (score){
        fwrite(one, sizeof(player),1, score);
        fclose(score);
    }
    else
        printf("There is @!#$");
}