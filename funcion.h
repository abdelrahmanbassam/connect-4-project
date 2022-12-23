#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char name[100];
    char symbol;
    int score;
    int numOfMove;
}player;

typedef struct{
    int hight;
    int width;
    int highScores;
}config;

void scan_game(int rows, int cols, char game[][cols])
{
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
            printf("|%c", game[i][j]);
        printf("|\n");
        for(int k=0; k<cols; k++)
            printf("--");
        printf("-\n");
    }
}

void creat_game(int rows, int cols, char game[][cols], int available_cols[], int select_cols[], int undo_moves[][2])
{
    for(int i=0; i<rows; i++)
        for(int j=0; j<cols; j++)
            game[i][j] = ' ';
    for(int i=0; i<cols; i++)
            available_cols[i] = rows;
    for(int i=0; i<(rows*cols); i++)
    {
        select_cols[i] = 0;
        for(int j=0; j<2; j++)
            undo_moves[i][j] = 0;
    }
}

void start_game(int rows, int cols, char game[][cols])
{
}

void inGame_menu(int rows, int cols, char game[][cols], int undo_moves[][2], int available_cols[], int select_cols[], int *nofUndo, int *totMove, player *playerTurn, player *other)
{
    int select_menu;
    printf("Enter -1 for in Game menu\n");
    scanf("%d", &select_menu);
    if(select_menu != -1){
        make_move(rows, cols, game, available_cols, select_cols, totMove, select_menu, playerTurn);
        playerTurn->score += count_score(rows, cols, game, available_cols, select_cols, *totMove, playerTurn);
        for(int i=0; i<*nofUndo; i++)
            for(int j=0; j<2; j++)
                undo_moves[i][j] = 0;
        *nofUndo = 0;
    }else{
        printf("Enter \n1 for a move \n2 for undo \n3 for redo \n4 for save \n5 for quit\n");
        scanf("%d", &select_menu);
        switch(select_menu)
        {
        case 1 :
            make_move(rows, cols, game, available_cols, select_cols, totMove, select_menu, playerTurn);
            playerTurn->score += count_score(rows, cols, game, available_cols, select_cols, *totMove, playerTurn);
            for(int i=0; i<*nofUndo; i++)
                for(int j=0; j<2; j++)
                    undo_moves[i][j] = 0;
            *nofUndo = 0;
            break;
        case 2 :
            if(*totMove <= 0)  return inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, nofUndo, totMove, playerTurn, other);
            other->score -= count_score(rows, cols, game, available_cols, select_cols, *totMove, other);
            undo(rows, cols, game, nofUndo, totMove, select_cols, available_cols, undo_moves);
            break;
        case 3 :
            if(*nofUndo <= 0)   return inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, nofUndo, totMove, playerTurn, other);
            redo(rows, cols, game, nofUndo, totMove, select_cols, available_cols, undo_moves, playerTurn, other);
            playerTurn->score += count_score(rows, cols, game, available_cols, select_cols, *totMove, playerTurn);
            break;
        case 4 :
            //save
        case 5 :
            //quit
            break;
        default :
            break;
        }
    }
}

void make_move(int rows, int cols, char game[][cols], int available_cols[], int select_cols[], int *totMove, int nofcol, player playerTurn)
{
    if(nofcol < 1 || nofcol > cols || available_cols[nofcol-1] == 0){
        printf("please, Enter a vaild nof col..\n");
        scanf("%d", &nofcol);
        return make_move(rows, cols, game, available_cols, select_cols, totMove, nofcol, playerTurn);
    }else{
        game[available_cols[nofcol-1]-1][nofcol-1] = playerTurn.symbol;
        available_cols[nofcol-1]--;
        select_cols[*totMove] = nofcol;
        playerTurn.numOfMove++, *totMove+=1;
    }
    return 0;
}


void undo(int rows, int cols, char game[][cols], int *nofUndo, int *totMove, int select_cols[], int available_cols[], int undo_moves[][2])
{
    int des_row, des_col;
    des_col = select_cols[*totMove-1] - 1;
    des_row = available_cols[des_col] ;
    game[des_row][des_col] = ' ';
    undo_moves[*nofUndo][0] = des_row;
    undo_moves[*nofUndo][1] = des_col;
    select_cols[*totMove-1] = 0;            // -> minus values by 1 && increas nofUndo by 1
    available_cols[des_col]++;
    *totMove-=1, *nofUndo+=1;
    return 0;
}

void redo(int rows, int cols, char game[][cols], int *nofUndo, int *totMove, int select_cols[], int available_cols[], int undo_moves[][2], player *playerTurn)
{
    int des_row, des_col;
    des_row = undo_moves[*nofUndo-1][0];
    des_col = undo_moves[*nofUndo-1][1];
    game[des_row][des_col] = playerTurn->symbol;
    undo_moves[*nofUndo-1][0] = 0;
    undo_moves[*nofUndo-1][1] = 0;
    *totMove+=1, *nofUndo-=1;
    select_cols[*totMove-1] = des_col+1;
    available_cols[des_col]--;
}

int count_score(int rows, int cols, char game[][cols], int available_cols[], int select_cols[], int totMoves, player playerTurn)
{
    int counter=0, score=0;
    int des_col = select_cols[totMoves-1] - 1;
    int des_row = available_cols[des_col];
   //horizental
    for(int i=-3; i<=3; i++)
    {
        if(playerTurn.symbol == game[des_row][des_col + i]) counter++;
        else{
            if(counter >= 4) score += (counter-4)+1;
            counter=0;
        }
    }
    if(counter >= 4) score += (counter-4)+1;
    counter=0;
    //vertical
    for(int i=0; i<=3; i++)
    {
        if(playerTurn.symbol == game[des_row + i][des_col]) counter++;
        else{
            if(counter >= 4) score += (counter-4)+1;
            counter=0;
        }
    }
    if(counter >= 4) score += (counter-4)+1;
    counter=0;
    //main diagonal
    for(int i=-3; i<=3; i++)
    {
        if(playerTurn.symbol == game[des_row + i][des_col + i]) counter++;
        else{
            if(counter >= 4) score += (counter-4)+1;
            counter=0;
        }
    }
    if(counter >= 4) score += (counter-4)+1;
    counter=0;
    //back diagonal
     for(int i=-3; i<=3; i++)
    {
        if(playerTurn.symbol == game[des_row - i][des_col + i]) counter++;
        else{
            if(counter >= 4) score += (counter-4)+1;
            counter=0;
        }
    }
    if(counter >= 4) score += (counter-4)+1;

    return score;
}