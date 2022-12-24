#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define color
// global values for height,Highscore,width,numberof fails
 extern int heightG,HighscoreG,widthG,NumOfaouls;

 int Checkoccur(char *SUbword,char *word)
{
  int check=-1;
    for(int i =0 ;word[i]!='\0';i++)
        {
         check=1;
            for(int j=0;SUbword[j]!='\0';j++ )
            {
               if(word[i+j]!=SUbword[j])
               {
                  check=-1;
                   break;
               }
            }
            if (check==1) return i;
        }
        return check;
}

void Rxml()
{
  int FirstConi,Lastconvi;



 char c;
 //AllChars represents the all domain which contains all Configurations
 char AllChars[10000]={'0'};//set the initial values to 0 to avoid garbage values//we can use maxmimum 200 or higher
 char hamada[]="</Highscores>";
 int len=0; //represents the length of used values
 //open file and read all chars and put it into AllChars
 FILE *xml ;
 char filepath[500];
 if(NumOfaouls==0)strcpy(filepath,"readXML.xml");
 else{printf("Enter the file correct path:\n");gets(filepath);}
 int x=0;
 if((xml=fopen(filepath,"r"))!=NULL)
 {
   while((c=fgetc(xml))!=EOF)
    {
     if(c !=' ' && c != '\n' && c!='\t' &&c!='\r')
     {
       AllChars[x]=c;
       len++;
       x++;
     }
    }
 }
 
 FirstConi=Checkoccur("<Configurations>",AllChars);
 Lastconvi=Checkoccur("</Configurations>",AllChars);
 int newi=(FirstConi+16),Finali=(Lastconvi);//16 is the number of chars in <Configurations>

 //creat a new array contains every thing between <Configurations> and </Configurations>
 char newarray[200]={'0'};
 int len2=(Lastconvi-FirstConi-16);
 for(int i=0;i<len2;i++)newarray[i]=AllChars[i+newi];

 //for(int i=0;i<len;i++)printf("%c",newarray[i]);
 int Fheight=Checkoccur("<Height>",newarray),h=0;
 int Lheight=Checkoccur("</Height>",newarray);
 int Fwidth=Checkoccur("<Width>",newarray),w=0;
 int Lwidth=Checkoccur("</Width>",newarray);
 int Fscore=Checkoccur("<Highscores>",newarray),s=0;
 int Lscore=Checkoccur("</Highscores>",newarray);
 //get height from Xml
  for(int i=(Fheight+8);i<Lheight;i++)
  {
    if((int)newarray[i]<48||(int)newarray[i]>57){h=-1;break;}
    h=h*10+(newarray[i]-'0');
  }
  //get width from Xml
  for(int i=(Fwidth+7);i<Lwidth;i++)
  {
    if((int)newarray[i]<48||(int)newarray[i]>57){w=-1;break;}
    w=w*10+(newarray[i]-'0');
  }
  //get highscore from xml
  for(int i=(Fscore+12);i<Lscore;i++)
  {
    if((int)newarray[i]<48||(int)newarray[i]>57){s=-1;break;}
    s=s*10+(newarray[i]-'0');
  }
//check of all values
 if(FirstConi==-1||Lastconvi==-1|| w==-1 || h==-1 || s==-1 || Fheight==-1 || Lheight==-1||Fwidth==-1||Lwidth==-1||Fscore==-1|| Lscore==-1)
 {
    printf("something goes wrong!\n");
    if(NumOfaouls<3)
    {
     NumOfaouls++;
     fclose(xml);
      Rxml();
    }
    else 
    {
    printf("you failed 3 times!! what an idiot!.all set to default height=9 width=7 tophighscore=10\n");
    heightG=9;widthG=7;HighscoreG=10;
    }
 }
 else{heightG=h;widthG=w;HighscoreG=s;}

 fclose(xml);
}
typedef struct{
    char name[100];
    char symbol;
    //char color;
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
    for(int i=0; i<cols; i++)
        printf("  %d ", i+1);
    printf("\n");
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<cols; j++)                             //remmeber -> player.color (any player can choose the color he wants)
        {
            printf(GREEN "|");
            if(game[i][j] == 'X') printf(CYAN " %c ", game[i][j]);
            else printf(RED " %c ", game[i][j]);
        }
        printf(GREEN "|\n");
        for(int k=0; k<cols; k++)
            printf("----");
        printf("-\n" RESET);
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

//void start_game(int rows, int cols, char game[][cols])

void inGame_menu(int rows, int cols, char game[][cols], int undo_moves[][2], int available_cols[], int select_cols[], int *nofUndo, int *totMove, player *playerTurn, player *other)
{
    int select_menu;
    printf(YELLOW "Enter the number of col (-1 for in-game menu)\n");
    scanf("%d", &select_menu);
    if(select_menu != -1){
        make_move(rows, cols, game, available_cols, select_cols, totMove, select_menu, playerTurn);
        playerTurn->score += count_score(rows, cols, game, available_cols, select_cols, *totMove, playerTurn);
        for(int i=0; i<*nofUndo; i++)
            for(int j=0; j<2; j++)
                undo_moves[i][j] = 0;
        *nofUndo = 0;
    }else{
        printf(YELLOW "Enter \n1 for a move \n2 for undo \n3 for redo \n4 for save \n5 for quit\n");
        scanf("%d", &select_menu);
        switch(select_menu)
        {
        case 1 :
            printf(YELLOW "Enter the number of col\n");
            scanf("%d", &select_menu);
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
    //if(nofcol == -1) return inGame_menu(rows, cols, game, undo_movees, available_cols, select_cols, nofU)
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
        //if(des_col+i >= 0 && des_col+i < cols)
        while(des_col+i < 0) i++;
        if(des_col+i > cols-1) break;
        if(playerTurn.symbol == game[des_row][des_col + i]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
            }
    }
    if(counter >= 4) score += counter-3;
    counter=0;
    //vertical
    for(int i=0; i<=3; i++)
    {
        if(des_row+i > rows-1) break;
        if(playerTurn.symbol == game[des_row + i][des_col]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
        }
    }
    if(counter >= 4) score += counter-3;
    counter=0;
    //main diagonal
    for(int i=-3; i<=3; i++)
    {
        while(des_row+i < 0 || des_col+i < 0) i++;
        if(des_row+i > rows-1 || des_col+i > cols-1) break;
        if(playerTurn.symbol == game[des_row + i][des_col + i]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
        }
    }
    if(counter >= 4) score += counter-3;
    counter=0;
    //back diagonal
     for(int i=-3; i<=3; i++)
    {
        while(des_row-i > rows-1 || des_col+i < 0) i++;  //-> prop here (alhamdulellah)
        if(des_row-i > rows-1 || des_col+i > cols-1) break;
        if(playerTurn.symbol == game[des_row - i][des_col + i]) counter++;
        else{
            if(counter >= 4) score += counter-3;
            counter=0;
        }
    }
    if(counter >= 4) score += counter-3;

    return score;
}