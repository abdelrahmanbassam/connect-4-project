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


void inGame_menu(int rows, int cols, char game[][cols], int undo_moves[][2], int available_cols[], int select_cols[], int *nofUndo, int *totMove, player playerTurn)
{
    int select_menu;
    printf("Enter \n1 for a move \n2 for undo \n3 for redo \n4 for save \n5 for quit\n");
    scanf("%d", &select_menu);
    switch(select_menu)
    {
    case 1 :
        move_player(rows, cols, game, available_cols, select_cols, totMove, playerTurn);
        for(int i=0; i<*nofUndo; i++)
            for(int j=0; j<2; j++)
                undo_moves[i][j] = 0;
        *nofUndo = 0;
        break;
    case 2 :
        if(*totMove <= 0)  return inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, nofUndo, totMove, playerTurn);
        undo(rows, cols, game, nofUndo, totMove, select_cols, available_cols, undo_moves);
        break;
    case 3 :
        if(*nofUndo <= 0)   return inGame_menu(rows, cols, game, undo_moves, available_cols, select_cols, nofUndo, totMove, playerTurn);
        redo(rows, cols, game, nofUndo, totMove, select_cols, available_cols, undo_moves, playerTurn
             );
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


int CountScore(int rows, int cols,player playerTurn,char game[rows][cols])
{
    playerTurn.score=0;
    int counter=0,x,y;

//count score Horizontally
    for(int i=0;i<rows;i++,counter=0)
    {
      for(int j=0;j<=cols;j++)
      {
        //if we don't want to look outside the game[][]->if(J==cols)J--
       if((game[i][j]==playerTurn.symbol))counter++;
        else
        {
        if(counter>=4)playerTurn.score+=(counter-3);
        counter =0;
        }
      }
    }
//count score  vertically
     for(int j=0;j<cols;j++,counter=0)
    {
      for(int i=0;i<=rows;i++)
      {
        //if we don't want to look outside the game[][]->if(i==rows)i--
       if((game[i][j]==playerTurn.symbol))counter++;
        else
        {
        if(counter>=4)playerTurn.score+=(counter-3);
        counter =0;
        }
      }
    }

 //count score diagonally
    for (int i = 0; i <rows; i++,counter=0)
    {x=i;
        for (int j=0; j <cols; j++,counter=0)
        {y=j;
            while(y<=cols&&x<=rows)
            {
                //if we don't want to look outside the game[][]->if(x==rows||y==cols)->x--;y--;
              if(game[x][y]==playerTurn.symbol)counter++;
              else
              {
              if(counter>=4)playerTurn.score+=(counter-3);
              counter=0;
              }
              x++;y++;
            }
            x=i;
            if (i>0)break;
        }
    }



 //count score diagonal backward
    for (int i = 0; i <rows; i++,counter=0)
    {x=i;
        for (int j=(cols-1);j>=0;j--,counter=0)
        {y=j;
            while(y>=-1&&x<=rows)
            {
                 //if we don't want to look outside the game[][]->if(x==rows||y==-1)->x--;y++
              if(game[x][y]==playerTurn.symbol)counter++;
              else
              {
              if(counter>=4)playerTurn.score+=(counter-3);
              counter=0;
              }
              x++;y--;
            }
            x=i;
            if (i>0)break;
        }
    }
    return playerTurn.score;
}

void move_player(int rows, int cols, char game[][cols], int available_cols[], int select_cols[], int *totMove, player playerTurn)
{
    int nofcol;
    printf("select the number of col\n");
    scanf("%d", &nofcol);
    game[available_cols[nofcol-1]-1][nofcol-1] = playerTurn.symbol;
    available_cols[nofcol-1]--;
    scan_game(rows, cols, game);
    select_cols[*totMove] = nofcol;
    playerTurn.numOfMove++, *totMove+=1;
    return 0;
}


void undo(int rows, int cols, char game[][cols], int *nofUndo, int *totMove, int select_cols[], int available_cols[], int undo_moves[][2])
{
    int des_row, des_col;
    des_col = select_cols[*totMove-1] - 1;
    des_row = available_cols[des_col] ;
    game[des_row][des_col] = ' ';
    scan_game(rows, cols, game);
    undo_moves[*nofUndo][0] = des_row;
    undo_moves[*nofUndo][1] = des_col;
    select_cols[*totMove-1] = 0;            // -> minus values by 1 && increas nofUndo by 1
    available_cols[des_col]++;
    *totMove-=1, *nofUndo+=1;
    return 0;
}

void redo(int rows, int cols, char game[][cols], int *nofUndo, int *totMove, int select_cols[], int available_cols[], int undo_moves[][2], player playerTurn)
{
    int des_row, des_col;
    char symbol;
    if(*totMove%2 == 0) symbol = playerTurn.symbol;
    else symbol = playerTurn.symbol;
    des_row = undo_moves[*nofUndo-1][0];
    des_col = undo_moves[*nofUndo-1][1];
    game[des_row][des_col] = symbol;
    scan_game(rows, cols, game);
    *totMove+=1, *nofUndo-=1;
    select_cols[*totMove-1] = des_col;
    available_cols[des_col]--;
}
