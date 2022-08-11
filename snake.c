#include <stdio.h>
#include <windows.h>
#include "loading.h"

#define WIDTH 80
#define HEIGHT 30

#define idx(c, r) (c + WIDTH * r)

struct snake{
    int size;
    int body[WIDTH*HEIGHT];
    int headx;int heady;
    int direction;
    int foodx;
    int foody;
}snk;

void init_snake(struct snake *snake){
    snake ->headx =WIDTH/2;
    snake ->heady =HEIGHT/2;
    snake->direction = 3;
}
void gen_food(struct snake *snake){
    snake ->foodx = rand() % WIDTH;
    snake ->foody = rand() % HEIGHT;
}
void snake(CHAR_INFO consoleBuffer[]){
    int gameover = 1;
    if (snk.size == 0){
        gen_food(&snk);
        snk.size+=2;
    }
    if(GetAsyncKeyState(VK_UP)) {
				snk.direction = 0;
			} else if(GetAsyncKeyState(VK_DOWN)) {
				snk.direction = 1;
			} else if(GetAsyncKeyState(VK_LEFT)) {
				snk.direction = 2;
			} else if(GetAsyncKeyState(VK_RIGHT)) {
				snk.direction = 3;
			}
    int direc = snk.direction;
        snk.body[0] = idx(snk.headx,snk.heady);
    for(int i = snk.size-1; i > 0; i--){
        snk.body[i] = snk.body[i-1]; 
    } 
    switch(direc){
        case 0:
            --snk.heady;
            Sleep(10);
            break;
        case 1:
            ++snk.heady;
            Sleep(10);
            break;
        case 2:
            --snk.headx;
            break;
        case 3:
            ++snk.headx;
            break;
    }
    //Colors  itoa
    for(int x = 0; x < WIDTH; x++){
        for(int y = 0; y < HEIGHT; y++){
            for(int cont = snk.size-1;cont>=0;cont--)
                consoleBuffer[snk.body[cont]] = (CHAR_INFO) {.Char.AsciiChar = ' ', .Attributes = BACKGROUND_GRAY}; 
            if(idx(x,y) == idx(snk.headx,snk.heady))
                pixel(x,y,BACKGROUND_WHITE,consoleBuffer);
            else if(idx(x,y) == idx(snk.foodx,snk.foody))
                pixel(x,y,BACKGROUND_RED,consoleBuffer);
            else
                pixel(x,y,0,consoleBuffer);
        }
    }
    //Food colision
    if (snk.headx == snk.foodx && snk.heady == snk.foody){
        snk.size++;
        gen_food(&snk);
    }
    //Game Over colisions
    for(int cont = snk.size-1;cont>=0;cont--){
        if(idx(snk.headx,snk.heady) == snk.body[cont])
            gameover = 0;
    }

    if(snk.headx > WIDTH || snk.headx < 0 || snk.heady > HEIGHT || snk.heady < 0)
        gameover = 0;
    
    if(!gameover){
        Sleep(1000);
        exit(0);
    }
}

int main(){
    CONSOLE_SCREEN_BUFFER_INFO csbi;

	/* Console window */
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE); // https://cplusplus.com/forum/beginner/68765/

	SMALL_RECT windowSize = {0, 0,  WIDTH - 1, HEIGHT - 1};
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize); // https://csc.csudh.edu/mmccullough/asm/help/source/win32lib/setconsolewindowinfo.htm

	COORD bufferSize = {WIDTH, HEIGHT};
	SetConsoleScreenBufferSize(wHnd, bufferSize); // https://csc.csudh.edu/mmccullough/asm/help/source/win32lib/setconsolescreenbuffersize.htm
//https://benryves.com/tutorials/winconsole/2
	CHAR_INFO consoleBuffer[WIDTH * HEIGHT];
	COORD charBufSize = {WIDTH, HEIGHT};
	COORD characterPos = {0, 0};
	SMALL_RECT writeArea = {0, 0, WIDTH - 1, HEIGHT - 1};
	SetConsoleTitle(TEXT("SNAKE"));
    loading();
    setbcolor(0,consoleBuffer);
    init_snake(&snk);
    for(;;){
        //snake(consoleBuffer);
        snake(consoleBuffer);
        WriteConsoleOutputA(wHnd, consoleBuffer, charBufSize, characterPos, &writeArea);
        Sleep(25);
    }
}