#include <stdio.h>
#include <stdlib.h>
#include "function.h"

int main()
{
    int totMoves=0, nofUndo=0;
    int hight, width;
    player first, second;
    first.symbol = 'X', second.symbol = 'O';
    first.numOfMove = 0; second.numOfMove = 0;
    first.score = 0, second.score = 0;
    scanf("%d %d", &width, &hight);
    int rows=hight, cols=width;
    int available_cols[cols], select_cols[rows*cols], undo_moves[rows*cols][2];
    char game[rows][cols];
    creat_game(rows, cols, game, available_cols, select_cols, undo_moves);

    while(totMoves < (rows*cols))
    {
        if(totMoves%2 == 0){
            inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, &nofUndo, &totMoves, &first, &second);
        }else{
            inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, &nofUndo, &totMoves, &second, &first);
        }
            scan_game(rows, cols, game);
            printf("totMoves = %d\nfirst score = %d ,second score = %d\n", totMoves, first.score, second.score);
    }
    return 0;
}