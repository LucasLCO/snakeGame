#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "snake.h"

typedef struct player{
    char name[20];
    int score_value;
    int id;
}player;


void file_write(char arq[], player *one);
int read_last(char arq[]);
void high_score(char arq[],player one);
void idk(player **two,int i);

int main(void){
    player one;
    char arq[] = {"scores.bin"}; 
    int op;
    if (access(arq, F_OK) == 0)
        one.id = (read_last(arq))+1; 
    else
        one.id=0;
    do{
        system("cls");
        printf("[1]Play\n[2]High Scores\n[3]Leave\n: ");
        scanf("%i", &op);
        switch(op){
            case 1:
                printf("\nName: ");
                scanf("%s",&(one.name));
                fflush(stdin);
                one.score_value = play();
                file_write(arq,&one);
                system("cls");
                read_last(arq);
                system("pause");
                break;
            case 2:
                high_score(arq, one);
                printf("there is no high score yet :P");
                system("pause");
                break;
            case 3:
                return 0;
        }
    }while(op != 3);
}

void file_write(char arq[], player *one){
    FILE *score = fopen(arq,"ab");
    if (score){
        fwrite(one, sizeof(player),1, score);
        fclose(score);
    }
    else
        printf("There is @!#$");
}
//printf("\n%s Score: %i\n",two.name,two.score_value); 
int read_last(char arq[]){
    player two;
    FILE *score = fopen(arq,"rb");
    if(score){
        while(!(feof(score))){
            if(!(fread(&two,sizeof(player),1,score)))
                printf("\n%s Score: %i\n",two.name,two.score_value);    
        }
        fclose(score);
    }
    else
        printf("There is @!#$");
    return two.id;
}

void idk(player **two,int i){
    if((*two=(player *)realloc(*two,i*sizeof(player)))==NULL)
        printf("There is @!#$");
}

void high_score(char arq[], player one){
    player two;
    FILE *score = fopen(arq,"rb");
    if(score){
        while(!(feof(score))){
            if((fread(&two,sizeof(player),1,score)))
                printf("\n%s Score: %i\n",two.name,two.score_value);    
        }
        fclose(score);
    }
    else
        printf("There is @!#$");
    /*player two[one.id+1];
    int high_ids[one.id], highest_score=0, i=0;
    FILE *score = fopen(arq,"rb");
    if(score){
        while(!(feof(score))){
            if((fread(&two[i],sizeof(player),1,score))){
                if(highest_score==0){
                    highest_score=two[i].score_value;
                    high_ids[i]=two[i].id;
                    printf("mis");
                }
                else if(highest_score < two[i].score_value){
                    highest_score=two[i].score_value;
                    high_ids[i]=two[i].id;
                    printf("mis");   
                }
                i++;
            }
            
        

        }
        fclose(score);
    }
    else
        printf("There is @!#$");
    player *two;
    int high_ids[one.id], highest_score=0, i=0;

    FILE *score = fopen(arq,"rb");
    if(score){
        while(!(feof(score))){
            if(fread(&two,sizeof(player),1,score)){
                printf("%i",two->id);
                idk(&two,i+1);
                i++;
            }              
        }
        fclose(score);
    }
    else
        printf("There is @!#$");*/
}
