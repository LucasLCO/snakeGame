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
void aloca(int **p,int tam);
void arq_line(int line, char arq[]);

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
                //printf("there is no high score yet :P\n");
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
        printf("\nThere is @!#$\n");
}
//printf("\n%s Score: %i\n",two.name,two.score_value); 
int read_last(char arq[]){
    player two;
    FILE *score = fopen(arq,"rb");
    if(score){
        while(!(feof(score))){
            if(!(fread(&two,sizeof(player),1,score)))
                printf("\n%s Score: %i\n\n\n",two.name,two.score_value);    
        }
        fclose(score);
    }
    else
        printf("\nThere is @!#$\n");
    return two.id;
}

void aloca(int **p,int tam){
    if((*p=(int*)realloc(*p,tam*sizeof(int)))==NULL)
        printf("\nThere is @!#$\n");
}

void arq_line(int line, char arq[]){
    player two;
    FILE* score = fopen(arq,"rb");
    if(score){
            fseek(score,line*sizeof(player),SEEK_CUR);
            if((fread(&two,sizeof(player),1,score))){
                printf("\n%s Score: %i\n\n\n",two.name,two.score_value);    
            }
        fclose(score);
    }
    else
        printf("\nThere is @!#$\n");
}

void high_score(char arq[], player one){
    player two;
    FILE *score = fopen(arq,"rb");
    int ids[(one.id+1)], *aux=NULL, highest_score=0, highest_score_id,i=0,j=0;
    if(score){
        while(!(feof(score))){
            if((fread(&two,sizeof(player),1,score))){
                if(two.score_value>highest_score){
                    highest_score=two.score_value;
                    ids[i]=two.id;
                    i++;
                }
            }
        }    
        fclose(score);
        for(i=0;i<(one.id+1);i++)
          arq_line(ids[i],arq);
    }
    else
        printf("There is @!#$");
}
