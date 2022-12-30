#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "finction.h"

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
 printf(RED"can't find the file!\n");
 else
 {
  while(fread(&printHscore[size_of_AvH],sizeof(player),1,Sorterd_file)==1)
  size_of_AvH++;

   // print high score list format
   if(size_of_AvH<desiredHS)
   {
   printf(RED"there are only %d available\n" ,size_of_AvH);desiredHS=size_of_AvH;
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
