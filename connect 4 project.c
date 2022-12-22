#include <stdio.h>
#include <stdlib.h>
#include "funcion.h"

int main()
{
    int totMove=0, nofUndo=0;
    int hight, width;
    player first, second;
    first.symbol='X', second.symbol='O';
    first.numOfMove=0; second.numOfMove=0;
    scanf("%d %d", &width, &hight);
    int rows=hight, cols=width;
    int available_cols[cols], select_cols[rows*cols], undo_moves[rows*cols][2];
    char game[rows][cols];
    creat_game(rows, cols, game, available_cols, select_cols, undo_moves);

    while(totMove < (rows*cols))
    {
        if(totMove%2 == 0) inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, &nofUndo, &totMove, first);
        else inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, &nofUndo, &totMove, second);
    }


 printf("%d ",CountScore(rows,cols,first,game));
 printf("%d ",CountScore(rows,cols,second,game));


}
