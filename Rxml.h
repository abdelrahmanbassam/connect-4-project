#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"



typedef struct{
    char name[20];
    char symbol;
    short int score;
}player;

typedef struct
{
  char gamename[30];
  short int game_rows, game_colns;
  short int select_cols[50*50];
  short int total_moves, high_scores, mode, level;
  player first, second;
}Game_info;

extern Game_info current_game;

struct tool{
    time_t gameTime;
    short int rows, cols, total_moves, nofUndo, high_scores, mode, level;
    short int available_cols[50], select_cols[50*50], undo_moves[50*50][2];  //rembeber to make select_cols an array not a pointer to save it
    char board[50][50];
    char game_name[20];
    player *first, *second;
};


void swapstruct(player *ar1,player *ar2)
{
player temp = *ar1;
*ar1=*ar2;
*ar2=temp;
}

//bubble sort struct
void bubble_struct(player *arrayHighscore,int NumOplayers)
{

 for (int i = 0; i <NumOplayers-1; i++)
 {
    for (int j = 0; j<NumOplayers-1-i; j++)
    {
        if(arrayHighscore[j].score<arrayHighscore[j+1].score)
        swapstruct(&arrayHighscore[j],&arrayHighscore[j+1]);
    }
 }
}

//return 1 if both are equals and 0 otw
int CompareToLower(char str1[],char str2[])
{
 if (strlen(str1)!=strlen(str2))
 return 0;

 for(int i =0;str1[i];i++)
 if(tolower(str1[i])!=tolower(str2[i]))
 return 0;

return 1;
}

//print highscore list in menu
void MENU_HIGHSCORE( struct tool * game)
{
    player printHscore[1000];
    int size_of_AvH=0,rnk=1,desiredHS=game->high_scores;//desired=parametar taken from XML file

    FILE *Sorterd_file,*backup_key;
 if((Sorterd_file=fopen("highscores.bin","rb"))==NULL)
   {
    //return menu and creat a new file
     printf(RED"can't find the file! creating New one \n");
      backup_key=fopen("highscores.bin","wb");
      fclose(backup_key);
      main_menu(game);
      return 0;
   }

  while(fread(&printHscore[size_of_AvH],sizeof(player),1,Sorterd_file)==1)
    size_of_AvH++;

    if(size_of_AvH==0)
    {
        printf(RED"THERE IS NO HIGHSCORES YET!\n");
        main_menu(game);
        return 0;
    }

   // print high score list format
   if(size_of_AvH<desiredHS)
   {
   printf(RED"there are only %d available\n" ,size_of_AvH);
   desiredHS=size_of_AvH;
   }
   printf(BLUE"RANK  NAME             symbol  SCORE\n\n");
   for(int i=0;i<desiredHS;i++)
   {
    printf(GREEN"%-5d%-20s%1c%8d \n",rnk,printHscore[i].name,printHscore[i].symbol,printHscore[i].score);
     if(printHscore[i].score!=printHscore[i+1].score)
      rnk++;
   }

 fclose(Sorterd_file);
}

//add after ending the game and show player rank
void END_sortandstorge(player * winner)
{
 printf(GREEN"%s's score : %d\n",winner->name,winner->score);

 player player1 = *winner;

 int check=0,NumOplayers=0;
 player arrayHighscore[1000];
 FILE *highScadd,*backup_key;
 //assign the highscores into array to know the numberofplayers and to order them according to score
 highScadd=fopen("highscores.bin","a+b");




   while(fread(&arrayHighscore[NumOplayers],sizeof(player),1,highScadd)==1)
   {
     if(CompareToLower(player1.name,arrayHighscore[NumOplayers].name))
     {
       if(arrayHighscore[NumOplayers].score<=player1.score)
         arrayHighscore[NumOplayers]=player1;
         check=1;
     }
    NumOplayers++;
  }
   if(check==0)
   {
   fwrite(&player1,sizeof(player),1,highScadd);
   arrayHighscore[NumOplayers]=player1;
   NumOplayers++;
  }
   bubble_struct(arrayHighscore,NumOplayers);

 //look for rank for player1
 for(int i=0;i<NumOplayers;i++)
 {
 //printf("%s %c %d\n ",arrayHighscore[i].name,arrayHighscore[i].symbol,arrayHighscore[i].score);
 if(CompareToLower(player1.name,arrayHighscore[i].name))
 printf(GREEN"%s's RANK:%d\n",player1.name,i+1);
 }

 fclose(highScadd);

 //save sorted array into file
 FILE *savesorted;
 savesorted=fopen("highscores.bin","wb");
 for (int i= 0; i <NumOplayers ; i++)
    fwrite(&arrayHighscore[i],sizeof(player),1,savesorted);


 fclose(savesorted);


 }

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


void Rxml(struct tool * game)
{
  static int NumOfaouls=0;
  int FirstConi,Lastconvi;
  game->rows=0;game->cols=0; game->high_scores=0;//set intial values of global to 0;


 char c;//char to read file and put into array
   char AllChars[10000]={'0'};//AllChars represents the all domain which contains all Configurations
                              //set the initial values to 0 to avoid garbage values//we can use maxmimum 200 or higher

 int len=0; //represents the length of used values
 //open file and read all chars and put it into AllChars
 FILE *xml ;
 char filepath[500];
 if(NumOfaouls==0)
   strcpy(filepath,"readXML.xml");
 else
 {
  printf(GREEN"Enter the file correct path:\n");
  gets(filepath);
 }

 //read all chars and put it into AllChars
 if((xml=fopen(filepath,"r"))!=NULL)
 {
   while((c=fgetc(xml))!=EOF)
    {
       AllChars[len++]=c;
    }
 }

 FirstConi=Checkoccur("<Configurations>",AllChars);
 Lastconvi=Checkoccur("</Configurations>",AllChars);
 int newi=(FirstConi+16),Finali=(Lastconvi);//16 is the number of chars in <Configurations>

 //creat a new array contains every thing between <Configurations> and </Configurations>
  char newarray[50000]={'0'};
  int len2=(Lastconvi-FirstConi-16);

 for(int i=0;i<len2;i++)
   newarray[i]=AllChars[i+newi];

 int Fheight=Checkoccur("<Height>",newarray);
 int Lheight=Checkoccur("</Height>",newarray);
 int Fwidth=Checkoccur("<Width>",newarray);
 int Lwidth=Checkoccur("</Width>",newarray);
 int Fscore=Checkoccur("<Highscores>",newarray);
 int Lscore=Checkoccur("</Highscores>",newarray);

 //get height from Xml //needs minimaization by &&isspace
  for(int i=(Fheight+8);i<Lheight;i++)
  {
    if(!isdigit(newarray[i]))
    {
     if((isspace(newarray[i])))
     {
       continue;
     }
     else
     {
      game->rows=-1;break;
     }
    }
    game->rows=game->rows*10+(newarray[i]-'0');
  }
  //get width from Xml
  for(int i=(Fwidth+7);i<Lwidth;i++)
  {
    if(!isdigit(newarray[i]))
    {
     if((isspace(newarray[i])))
     {
       continue;
     }
     else
     {
      game->cols=-1;break;
     }
    }
    game->cols=game->cols*10+(newarray[i]-'0');
  }
  //get highscore from xml
  for(int i=(Fscore+12);i<Lscore;i++)
  {
   if(!isdigit(newarray[i]))
    {
     if((isspace(newarray[i])))
     {
       continue;
     }
     else
     {
      game->high_scores=-1;break;
     }
    }
    game->high_scores=game->high_scores*10+(newarray[i]-'0');
  }

 //check of all values
 //need to put constraints according to mourad's max limit grid
 if(FirstConi==-1||Lastconvi==-1|| game->cols==-1 || game->rows==-1 || game->high_scores==-1 || Fheight==-1 || Lheight==-1||Fwidth==-1||Lwidth==-1||Fscore==-1|| Lscore==-1)
 {
    printf(RED"something goes wrong!\n");
    if(NumOfaouls<3)
    {
     NumOfaouls++;
     fclose(xml);
      Rxml(game);
    }
    else
    {
    printf(RED"you failed 3 times!! all set to default height=7 width=9 tophighscore=10\n");
    game->rows=7;game->cols=9;game->high_scores=10;
    }
 }
 fclose(xml);
}

void take_current_game(struct tool game)
{
    current_game.first = *(game.first);
    current_game.second = *(game.second);
    //current_game->gamename = game->game_name;
    current_game.game_rows = game.rows;
    current_game.game_colns = game.cols;
    current_game.high_scores = game.high_scores;
    current_game.level = game.level;
    current_game.mode = game.mode;
    current_game.total_moves = game.total_moves;
    for(int i=0; i<game.total_moves; i++)
        current_game.select_cols[i] = game.select_cols[i];
}

void load_old_game(struct tool * game, Game_info old_game)
{
    strcpy(game->first->name, old_game.first.name);
    strcpy(game->second->name, old_game.second.name);
    game->first->symbol = old_game.first.symbol;
    game->second->symbol = old_game.second.symbol;
    game->first->score = old_game.first.score;
    game->second->score = old_game.second.score;
    //current_game->gamename = game->game_name;
    game->rows = old_game.game_rows;
    game->cols = old_game.game_colns;
    game->high_scores = old_game.high_scores;
    game->level = old_game.level;
    game->mode = old_game.mode;
    game->total_moves = old_game.total_moves;
    for(int i=0; i<old_game.total_moves; i++)
        game->select_cols[i] = old_game.select_cols[i];
}



void save()
{

 FILE *save,*backup_key;
 Game_info Games_Array[30];
 int size_of_games=0;
 save=fopen("savedgames.bin","a+b");





  while(fread(&Games_Array[size_of_games],sizeof(Game_info),1,save)==1)
  size_of_games++;



   printf(BLUE"ENTER NAME OF GAME \n ");
   scanf("%s",&current_game.gamename);

   fwrite(&current_game,sizeof(Game_info),1,save);
   Games_Array[size_of_games]=current_game;
   size_of_games++;

 //sort saved games array
 for(int i=0;i<size_of_games;i++)
  Games_Array[i%3]=Games_Array[i];
 fclose(save);

 //write sorted games into file
 FILE *write_sort_save;
 write_sort_save=(fopen("savedgames.bin","wb"));
 for (int i= 0; i <size_of_games ; i++)
    fwrite(&Games_Array[i],sizeof(Game_info),1,write_sort_save);

  fclose(write_sort_save);
}



 void load(struct tool *game)
 {

  FILE *loadx,*backup_key;
 Game_info load_array[3];
 int size_of_load=0,val;
 char gamenumber[5];
 if((loadx=fopen("savedgames.bin","rb"))==NULL)
 {
     printf(RED"can't find the file! creating New one \n");
       backup_key=fopen("savedgames.bin","wb");
      fclose(backup_key);
      main_menu(game);
      return 0;
 }


 while(fread(&load_array[size_of_load],sizeof(Game_info),1,loadx))
 {
    size_of_load++;
    if(size_of_load==3)break;
 }


 if(size_of_load==0)
 {
    printf(RED"NO SAVED GAMES YET\n");
    main_menu(game);
    return 0;
 }
 else
 {
   printf(GREEN"available games : \n");
printf(BLUE"  Game number        GAME NAME\n");
 for(int i=0;i<size_of_load;i++)
 printf("     (%1d)%20s\n",i+1,load_array[i].gamename);
  }
 printf(BLUE"Enter the number of game you want\n");
 while(1)
{
    gets(gamenumber);
    val=atoi(gamenumber);
    if((val>0)&&(val<=size_of_load))//need maintance if user input char program will crash
    break;
 printf(RED"ENTER a valid number\n");
 }
  load_old_game(game,load_array[val-1]);
}
