#include <stdio.h>
#include <stdlib.h>

void scan_game(int rows, int cols, char game[][cols]);
void creat_game(int rows, int cols, char game[][cols]);

int main()
{
    int hight, width;
    scanf("%d %d", &width, &hight);
    int rows=2*hight+1, cols=2*width+1;
    char game[rows][cols];
    creat_game(rows, cols, game);
    scan_game(rows, cols, game);


}

void scan_game(int rows, int cols, char game[][cols])
{
    //int rows=2*hight+1, cols=2*width+1;
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

void creat_game(int rows, int cols, char game[][cols])
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
    return 0;
}

void start_game(int rows, int cols, char game[][cols])
{





}

