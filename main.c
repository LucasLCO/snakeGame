#include <stdio.h>
#include <stdlib.h>
#include "snake.h"

typedef struct player{
    char name[20];
    int score_value;
}player;


void write(char arq[], player *one);
void read(char arq[], int bool);

int main(void){
    player one;
    char arq[] = {"scores.bin"}; 
    int op;
    do{
        system("cls");
        printf("[1]Play\n[2]Scores\n[3]Leave\n: ");
        scanf("%i", &op);
        switch(op){
            case 1:
                printf("\nName: ");
                scanf("%s",&(one.name));
                fflush(stdin);
                one.score_value = play();
                write(arq,&one);
                system("cls");
                read(arq,0);
                system("pause");
                break;
            case 2:
                read(arq,1);
                system("pause");
                break;
            case 3:
                return 0;
        }
    }while(op != 3);
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

void read(char arq[], int bool){
    player two;
    FILE *score = fopen(arq,"rb");
    if(score){
        while(!(feof(score))){
            if(bool==1){
                if(fread(&two,sizeof(player),1,score))
                printf("\nPlayer: %s\nScore: %i\n",two.name,two.score_value);            
            }
            else{
                if(!(fread(&two,sizeof(player),1,score)))
                printf("\n%s Score: %i\n",two.name,two.score_value);    
            }
        }
        fclose(score);
    }
    else
        printf("There is @!#$");
}