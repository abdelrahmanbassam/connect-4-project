#include <stdio.h>
#include <stdlib.h>
int CountScore(int rows, int colns,char playersymbol,char game[rows][colns])
{

    int playerscore=0;
    int counter=0;

    //count score Horizontally
    for(int i=1;i<rows;i+=2)
    {
     counter=0;
      for(int j=1;j<colns;j+=2)
      {
       if(game[i][j]==playersymbol)
        counter++;
        else
        {
        if(counter>4||counter==4)
        playerscore+=(counter%4+1);
        counter =0;
        }

      }

    }
     return playerscore;

     //count score  vertically
     for(int j=1;j<colns;j+=2)
    {
    counter=0;
      for(int i=1;i<rows;i+=2)
      {
       if(game[i][j]==playersymbol)
        counter++;
        else
        {
        if(counter>4||counter==4)
        playerscore+=(counter%4+1);
        counter=0;
        }
        
      }
    }

    //count score diagonally
    for (int i = 1; i < (rows-3); i+=2)
    {
        counter=0;
        for (int j=1; j < (colns-3); j+=2)
        {
            while(j<(colns))
            {
              counter=0;
              if(game[i][j]==playersymbol)
              counter++;
              else
              {
              if(counter>4||counter==4)
              playerscore+=(counter%4+1);
              counter=0;
              }
              i+=2;j+=2;
            }
        }

    }
    //count score diagonal backward
    for (int i = 1; i < (rows-3); i+=2)
    {
        counter=0;
        for (int j=(colns-1);j>(6); j-=2)
        {
            while(j>0)
            {
              counter=0;
              if(game[i][j]==playersymbol)
              counter++;
              else
              {
              if(counter>4||counter==4)
              playerscore+=(counter%4+1);
              counter=0;
              }
              i+=2;j-=2;
            }
        }

    }
    return playerscore;
}
typedef struct{
    char name[100];
    char symbol;
    int score;
    int numOfMove;
}player;

void scan_game(int rows, int cols, char game[][cols]);
void creat_game(int rows, int cols, char game[][cols], int available_cols[]);

int main()
{
    int score1;
    int hight, width;
    player first, second;
    first.symbol = 'X', second.symbol = 'O';
    scanf("%d %d", &width, &hight);
    int rows=2*hight+1, cols=2*width+1, select_col;
    int available_cols[width];
    char game[rows][cols];
    creat_game(rows, cols, game, available_cols);

    for(int i=0; i<(hight*width); i++)
    {
        if(i%2 == 0) move_player(rows, cols, select_col, game, available_cols, first);
        else move_player(rows, cols, select_col, game, available_cols, second);

    }


 printf("%d",CountScore(rows,cols,'X',game));


}

void scan_game(int rows, int cols, char game[][cols])
{
    //int rows=2*hight+1, cols=2*width+1;
    //printf("number of first player movements = %d", )
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            printf("%c", game[i][j]);
        }
        printf("\n");
    }
    return 0;
}

void creat_game(int rows, int cols, char game[][cols], int available_cols[])
{
    //char game[rows][cols];
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)
        {
            game[i][j] = ' ';
        }
    }

    for(int i=0; i<rows; i++)
    {
        if(i%2 == 0)
        {
            for(int j=0; j<cols; j++)
            {
                game[i][j] = '-';
            }
        }else{
            for(int j=0; j<cols; j++)
            {
                if(j%2 == 0) {game[i][j] = '|';}
                else {game[i][j] = ' ';}
            }
        }
    }
    for(int i=0; i<(cols/2); i++)
    {
        available_cols[i] = 0;
    }
    return 0;
}

void start_game(int rows, int cols, char game[][cols])
{

}

void move_player(int rows, int cols, int select_col, char game[][cols], int available_cols[], player playerTurn)
{
    do{scanf("%d", &select_col);}
    while(select_col < 1 || select_col > cols/2 || available_cols[select_col-1] == (rows/2));
    //if(is_available(rows, cols, select_col, available_cols))
    //{
        game[rows - (2+2*(available_cols[select_col-1]))][(select_col*2)-1] = playerTurn.symbol;
        available_cols[select_col-1]++;
        scan_game(rows, cols, game);
    //}
}

/*int is_available(int rows, int cols, int select_col, int available_cols[])  //-> width = cols/2
{                                                                           //-> hight = rows/2
    if(select_col < 1 || select_col > cols/2 || available_cols[select_col-1] == (rows/2))
    {
        printf("please, enter a valid col\n");
        return 0;
    }
    //if(available_cols[select_col-1] == (rows/2)) return 0;
    return 1;
    */

//test bassam
