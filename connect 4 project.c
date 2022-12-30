#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "C:\Users\mourad mahgoub\OneDrive\Desktop\c _ tottrials\connect4.2\finctions2.h"
//#include "Rxml2.h"

// global values for height,Highscore,width,numberof fails
int heightG,HighscoreG,widthG,NumOfaouls=0;

int main()
{
    struct tool game;
    player first, second;
    int hight, width;

    short int available_cols[100], select_cols[100*100];
   game.available_cols = available_cols;
   game.select_cols = select_cols;
   //game.undo_moves = undo_moves;

   game.first = &first, game.second = &second;
    //board game;
    scanf("%d %d", &game.rows, &game.cols);
    strcpy(first.name, "FIRST"), strcpy(second.name, "SECOND");
    first.symbol = 'X', second.symbol = 'O';
    system("color 00");
   // time_t gameTime = time(NULL);
    //first.numOfMove = 0; second.numOfMove = 0;
    first.score = 0, second.score = 0;
    game.total_moves =0;
    //Rxml();
    //game.cols=widthG, game.rows=heightG;
    //printf(MAGENTA "GAME  HEIGHT IS %d GAME WIDTH IS %d \n ",hight,width);
    printf(YELLOW);
    creat_game(&game);
    main_menu(&game);

    //MENU_HIGHSCORE();

    return 0;
}