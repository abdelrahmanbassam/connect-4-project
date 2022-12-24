#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "function.h"
// global values for height,Highscore,width,numberof fails
int heightG,HighscoreG,widthG,NumOfaouls=0;


int main()
{
    system("color 00");
    time_t gameTime = time(NULL);
    int totMoves=0, nofUndo=0;
    int hight, width;
    player first, second;
    first.symbol = 'X', second.symbol = 'O';
    first.numOfMove = 0; second.numOfMove = 0;
    first.score = 0, second.score = 0;
    Rxml();
    width=widthG;hight=heightG;
    printf(MAGENTA "GAME  HEIGHT IS %d GAME WIDTH IS %d \n ",hight,width);
    printf(YELLOW);
    int rows=hight, cols=width;
    int available_cols[cols], select_cols[rows*cols], undo_moves[rows*cols][2];
    char game[rows][cols];
    creat_game(rows, cols, game, available_cols, select_cols, undo_moves);

    while(totMoves < (rows*cols))
    {
        if(totMoves%2 == 0){
            printf(CYAN "1ST PLAYER TURN\n");
            inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, &nofUndo, &totMoves, &first, &second);
        }else{
            printf(RED "2ND PLAYER TURN\n");
            inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, &nofUndo, &totMoves, &second, &first);
        }
            scan_game(rows, cols, game);
            printf(MAGENTA "Time = %d:%d ,Number of Moves = %d\n", (time(NULL)-gameTime)/60, (time(NULL)-gameTime)%60, totMoves);
            printf(CYAN "SCORE OF 1ST PLAYER = %d,  " RED "SCORE OF 2ND PLAYER = %d\n" RESET, first.score, second.score);
    }
    return 0;
}
