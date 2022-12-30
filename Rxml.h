#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//#include "finction.h"
typedef struct
{
 char gamegrid[50][50];
  int game_rows;
  int game_colns;
  char gamename[30];
}Game_info;

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
void MENU_HIGHSCORE()
{
    player printHscore[1000];
    int size_of_AvH=0,rank=1,desiredHS=HighscoreG;//desired=parametar taken from XML file
    FILE *Sorterd_file;
 if((Sorterd_file=fopen("highscores.bin","rb"))==NULL)
   {
    printf(RED"can't find the file!\n");//return menu or creat a new file
   }
 else
 {
  while(fread(&printHscore[size_of_AvH],sizeof(player),1,Sorterd_file)==1)
    size_of_AvH++;

   // print high score list format
   if(size_of_AvH<desiredHS)
   {
   printf(RED"there are only %d available\n" ,size_of_AvH);
   desiredHS=size_of_AvH;
   }
   printf(BLUE"RANK  NAME             symbol  Game_Dim _H*W     SCORE\n\n");
   for(int i=0;i<desiredHS;i++)
   {
    printf("%-5d%-20s%-7c%4d*%-10d%6d \n",rank,printHscore[i].name,printHscore[i].symbol,printHscore[i].gameheight,printHscore[i].gamewidth,printHscore[i].score);
     if(printHscore[i].score!=printHscore[i+1].score)
      rank++;
   }
 }
 fclose(Sorterd_file);
}

//add after ending the game and show player rank
void END_sortandstorge(player player1)
{
 printf(GREEN"%s's score : %d\n",player1.name,player1.score);

 int check=0,NumOplayers=0;
 player arrayHighscore[1000];
 FILE *highScadd;
 //assign the highscores into array to know the numberofplayers and to order them according to score
 if((highScadd=fopen("highscores.bin","a+b"))==NULL)
   printf(RED"can't find the file!\n");
 else
 {
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


void Rxml()
{
  static int NumOfaouls=0;
  int FirstConi,Lastconvi;
  Highscore=0;height=0;width=0;//set intial values of global to 0;


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
  printf("Enter the file correct path:\n");
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
      height=-1;break;
     }
    } 
    height=height*10+(newarray[i]-'0');
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
      width=-1;break;
     }
    } 
    width=width*10+(newarray[i]-'0');
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
      Highscore=-1;break;
     }
    } 
    Highscore=Highscore*10+(newarray[i]-'0');
  }

 //check of all values 
 //need to put constraints according to mourad's max limit grid
 if(FirstConi==-1||Lastconvi==-1|| width==-1 || height==-1 || Highscore==-1 || Fheight==-1 || Lheight==-1||Fwidth==-1||Lwidth==-1||Fscore==-1|| Lscore==-1)
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
    printf("you failed 3 times!! all set to default height=7 width=9 tophighscore=10\n");
    height=7;width=9;Highscore=10;
    }
 }
 fclose(xml);
}



void save(Game_info newgame)
{
   

 FILE *keysave;
 Game_info Games_Array[3];
 int ii=0,val;
 char slotnumber[5];

 if((keysave=fopen("savedgames.bin","r+b"))==NULL) 
 {
  printf("can't find the file!\n");exit(1); //creat a new one if it fails
 }

  
    for(int i=0;i<3;i++)
    {
     if(!fread(&Games_Array[i],sizeof(Game_info),1,keysave))
       strcpy(Games_Array[i].gamename,"EMPTY");
    }

    rewind(keysave);

  while(fread(&Games_Array[ii++],sizeof(Game_info),1,keysave));
   
   
  
   printf("Enter game name\n");
    gets(newgame.gamename);
  
     
  printf("available games : \n");
  printf("  Game number        GAME NAME\n");
 for(int i=0;i<3;i++)
 {
  printf("     (%1d)%20s\n",i+1,Games_Array[i].gamename);
 }
 printf("Select a slot to save in\n");
  while(1)
 {
    gets(slotnumber);//need maintance if user input char program will crash
    val=atoi(slotnumber);
    if((val>0)&&(val<4))
      break;
 printf("ENTER a valid number\n");
 } 
  Games_Array[val-1]=newgame;
 rewind(keysave);

 for (int i = 0; i < 3; i++)
   fwrite(&Games_Array[i],sizeof(Game_info),1,keysave);
 
 
 

 fclose(keysave);
} 

 
 
 Game_info load(Game_info *New_info)
{ 
   FILE *keyload;
   Game_info load_array[3];
   int size_of_load=0,val;
  
 if((keyload=fopen("savedgames.bin","rb"))==NULL)
 {
  printf("can't find the file!\n");
  exit(1);//go to menu //or creat a new file
 }
 
    while(fread(&load_array[size_of_load],sizeof(Game_info),1,keyload))
      size_of_load++;


 
   if(size_of_load==0)
    printf("NO SAVED GAMES YET\n");//go to menu //or creat a new file
 
   printf("available games : \n");
   printf("  Game number        GAME NAME\n");

      for(int i=0;i<3;i++)
      {
      printf("     (%1d)%20s\n",i+1,load_array[i].gamename);
      }
  char gamenumber[5];
       printf("Enter the number of game you want\n");
    while(1)
     {

       gets(gamenumber);
       val=atoi(gamenumber);
       if((val>0)&&(val<=3)&&(strcmp(load_array[val-1].gamename,"EMPTY")))
       break;
      printf("ENTER a valid number\n");
     }

  return load_array[val-1];
 
  
} 