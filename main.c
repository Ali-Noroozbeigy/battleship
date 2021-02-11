#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include <string.h>


/*
structure that saves all information
about each block
*/
struct Information{
  char state;
  bool isShip;
  bool isReserved; //for border of each ship
};
typedef struct Information Info;

/*
structure that saves ships coordinates
in linked list to check if it is destroyed or not
*/
struct shipsList{

   char direction;//H for horizontal V for vertical
   int firstRow;
   char firstC;
   int len;
   struct shipsList *next;

};

struct shipsList *head1=NULL;
struct shipsList *head2=NULL;

//creates nodes of each player's ships
void createNode (char dir,int row,char column,int len,char player)
{
 struct shipsList *ptr=(struct shipsList *)malloc(sizeof(struct shipsList));
 ptr->direction=dir;
 ptr->firstRow=row;
 ptr->firstC=column;
 ptr->len=len;
 if (player=='1')
 {
   ptr->next=head1;
   head1=ptr;
 }
 else
 {
   ptr->next=head2;
   head2=ptr;
 }
}


/* blocks of game*/
Info player1[10][10];
Info player2[10][10];

/*name of players and points*/
char player1Name[50]={'\0'},player2Name[50]={'\0'};

int points1=0,points2=0;

/*
make all the blocks empty before
choosing a block for ship
*/
void makeEmpty (void)
{
    for (int i=0;i<10;i++)
      {
        for (int j=0;j<10;j++)
        {
          player1[i][j].state=' ';
          player2[i][j].state=' ';
        }
      }
    for (int i=0;i<10;i++)
      {
        for (int j=0;j<10;j++)
        {
          player1[i][j].isShip=false;
          player1[i][j].isReserved=false;
          player2[i][j].isShip=false;
          player2[i][j].isReserved=false;
        }
      }
}


// creates board of game
void createBoard(char player)
{
   for (char c='A';c<='J';c++)
        printf("     %c",c);
    printf("\n");
    for (int i=0;i<10;i++)
     { printf("    ");
       for (int j=0;j<60;j++)
            printf("-");
       printf("\n");
       for (int j=0;j<3;j++)
         {
           if (j==1)
            {
              if (i==9)
                    printf(" %d",i+1);
              else
                printf("  %d",i+1);
            }
           else
              printf("   ");
           for (int k=0;k<=10;k++)
             {
               if (j==1 && k!=10)
                 {
                   if (player=='1')
                     printf("|  %c  ",player1[i][k].state);
                   else
                     printf("|  %c  ",player2[i][k].state);
                 }
               else
                 {
                   printf("|     ");
                 }
             }
           printf("\n");
         }
     }
    printf("    ");
    for (int i=0;i<60;i++)
        printf("-");
    printf("\n");
}

/*
gets the coordinates of ships
and shows the preview of each player's map
*/
void putShips(char player)
{
    system("cls");
    int numShips[4]={4,3,2,1};//number of ships
    int firstRow,secondRow;
    char firstC,secondC;
    int i=0;
    int len=12;
    bool invalid=false;
    while(i!=10)
    {
      invalid=false;
      createBoard(player);
      printf("(5 : %d) , (3 : %d) , (2 : %d) , (1 : %d)\n\n"
             ,numShips[3],numShips[2],numShips[1],numShips[0]);
      printf("%s enter first and last coordinate(n X m Y) ",(player=='1')?player1Name:player2Name);
      scanf("%d %c %d %c",&firstRow,&firstC,&secondRow,&secondC);
      if (firstRow>10 || secondRow>10 || firstC>'J' || secondC>'J'||
          firstRow<0 || secondRow<0 || firstC<'A' || secondC<'A')
          {
            printf("invalid input\n");
            delay(1000);
            system("cls");
            continue;
          }
      if (firstRow==secondRow)
       {
        if (firstC>secondC)
          {
            printf("reverse your input!");
            delay(2000);
            continue;
          }
        len=secondC-firstC+1;
        if (len<=5 && len!=4)
          {
            if (player=='1')
             {
                for (int j=firstC;j<=secondC;j++)
                  {
                    if (player1[firstRow-1][j-65].state=='o'
                        || player1[firstRow-1][j-65].isReserved==true)
                       invalid=true;
                  }
                if (invalid)
                {
                  printf("you can't put ship here!\n");
                  delay(1500);
                  system("cls");
                  continue;
                }
             }
            else if (player=='2')
              {
                for (int j=firstC;j<=secondC;j++)
                  {
                    if (player2[firstRow-1][j-65].state=='o'
                        || player2[firstRow-1][j-65].isReserved==true)
                       invalid=true;
                  }
                if (invalid)
                {
                 printf("you can't put ship here!\n");
                 delay(1500);
                 system("cls");
                 continue;
                }
              }
            if (len==5)
              {
               if (numShips[3]!=0)
                numShips[3]--;
               else
               {
                printf("you have placed all of your ships with this size!\n");
                delay(2000);
                system("cls");
                continue;
               }
              }
            else
             {
              if (numShips[len-1]!=0)
                numShips[len-1]--;
              else
              {
                printf("you have placed all of your ships with this size!\n");
                delay(2000);
                system("cls");
                continue;
              }
             }
            for (int j=firstC;j<=secondC;j++)
              {
                if (player=='1')
                 {
                  player1[firstRow-1][j-65].state='o';
                  player1[firstRow-1][j-65].isShip=true;
                  if (firstRow>=2)
                    player1[firstRow-2][j-65].isReserved=true;
                  if (firstRow<=9)
                    player1[firstRow][j-65].isReserved=true;
                 }
                else
                 {
                  player2[firstRow-1][j-65].state='o';
                  player2[firstRow-1][j-65].isShip=true;
                  if (firstRow>=2)
                    player2[firstRow-2][j-65].isReserved=true;
                  if (firstRow<=9)
                    player2[firstRow][j-65].isReserved=true;
                 }
              }
             if(player=='1')
                createNode('H',firstRow-1,firstC-65,len,'1');
             else
                createNode('H',firstRow-1,firstC-65,len,'2');

             if (firstC-65>=1)
               {
                  if (player=='1')
                    {
                      if (firstRow-1>=1)
                         player1[firstRow-2][firstC-65-1].isReserved=true;
                      if (firstRow-1<=8)
                         player1[firstRow][firstC-65-1].isReserved=true;
                      player1[firstRow-1][firstC-65-1].isReserved=true;
                    }
                  else
                    {
                      if (firstRow-1>=1)
                         player2[firstRow-2][firstC-65-1].isReserved=true;
                      if (firstRow-1<=8)
                         player2[firstRow][firstC-65-1].isReserved=true;
                      player2[firstRow-1][firstC-65-1].isReserved=true;
                    }
               }
             if (secondC-65<=8)
               {
                  if (player=='1')
                    {
                      if (firstRow-1>=1)
                        player1[firstRow-2][secondC-65+1].isReserved=true;
                      if (firstRow-1<=8)
                        player1[firstRow][secondC-65+1].isReserved=true;
                      player1[firstRow-1][secondC-65+1].isReserved=true;
                    }
                  else
                    {
                      if (firstRow-1>=1)
                        player2[firstRow-2][secondC-65+1].isReserved=true;
                      if (firstRow-1<=8)
                        player2[firstRow][secondC-65+1].isReserved=true;
                      player2[firstRow-1][secondC-65+1].isReserved=true;
                    }
               }

             i++;
          }
       }
      else if (firstC==secondC)
       {
        if(firstRow>secondRow)
          {
            printf("reverse your input!");
            delay(2000);
            continue;
          }
        len=secondRow-firstRow+1;
        if (len<=5 && len!=4)
          {
            if (player=='1')
             {
                for (int j=firstRow;j<=secondRow;j++)
                  {
                    if (player1[j-1][firstC-65].state=='o'
                        || player1[j-1][firstC-65].isReserved==true)
                       invalid=true;
                  }
                if (invalid)
                {
                 printf("you can't put ship here!\n");
                 delay(1500);
                 system("cls");
                 continue;
                }
             }
            else if (player=='2')
              {
                for (int j=firstRow;j<=secondRow;j++)
                  {
                    if (player2[j-1][firstC-65].state=='o'
                        || player2[j-1][firstC-65].isReserved==true)
                       invalid=true;
                  }
                if (invalid)
                {
                  printf("you can't put ship here!\n");
                  delay(1500);
                  system("cls");
                  continue;
                }
              }
            if (len==5)
              {
                if (numShips[3]!=0)
                  numShips[3]--;
                else
                {
                  printf("you have placed all of your ships with this size!\n");
                  delay(2000);
                  system("cls");
                  continue;
                }
              }
            else
              {
                if (numShips[len-1]!=0)
                  numShips[len-1]--;
                else
                {
                  printf("you have placed all of your ships with this size!\n");
                  delay(2000);
                  system("cls");
                  continue;
                }
              }
            for (int j=firstRow;j<=secondRow;j++)
              {
                if (player=='1')
                 {
                  player1[j-1][firstC-65].state='o';
                  player1[j-1][firstC-65].isShip=true;
                  if (firstC-65>=1)
                    player1[j-1][firstC-65-1].isReserved=true;
                  if (firstC-65<=8)
                    player1[j-1][firstC-65+1].isReserved=true;
                 }
                else
                 {
                  player2[j-1][firstC-65].state='o';
                  player2[j-1][firstC-65].isShip=true;
                  if (firstC-65>=1)
                    player2[j-1][firstC-65-1].isReserved=true;
                  if (firstC-65<=8)
                    player2[j-1][firstC-65+1].isReserved=true;
                 }
              }

             if(player=='1')
                createNode('V',firstRow-1,firstC-65,len,'1');
             else
                createNode('V',firstRow-1,firstC-65,len,'2');

             if (firstRow-1>=1)
               {
                 if (player=='1')
                    {
                      if(firstC-65>=1)
                        player1[firstRow-2][firstC-1].isReserved=true;
                      if(firstC-65<=8)
                        player1[firstRow-2][firstC+1].isReserved=true;
                      player1[firstRow-2][firstC].isReserved=true;
                    }
                 else
                    {
                      if(firstC-65>=1)
                        player2[firstRow-2][firstC-1].isReserved=true;
                      if(firstC-65<=8)
                        player2[firstRow-2][firstC+1].isReserved=true;
                      player2[firstRow-2][firstC].isReserved=true;
                    }
               }
             if (secondRow-1<=8)
               {
                 if (player=='1')
                    {
                       if (firstC-65>=1)
                         player1[secondRow-1+1][firstC-65-1].isReserved=true;
                       if (firstC-65<=8)
                         player1[secondRow-1+1][firstC-65+1].isReserved=true;
                       player1[secondRow-1+1][firstC-65].isReserved=true;
                    }
                 else
                    {
                       if (firstC-65>=1)
                         player2[secondRow-1+1][firstC-65-1].isReserved=true;
                       if (firstC-65<=8)
                         player2[secondRow-1+1][firstC-65+1].isReserved=true;
                       player2[secondRow-1+1][firstC-65].isReserved=true;
                    }
               }

             i++;
          }
       }
    else
    {
      printf("invalid!");
      delay(1000);
    }
    system("cls");
  }
 createBoard(player);
 delay(2000);
 system("cls");
}

/*
after showing the preview, hides the states of blocks
but doesn't change isShip and isReserved
*/
void hide (void)
{
    for (int i=0;i<10;i++)
     {
       for (int j=0;j<10;j++)
       {
         player1[i][j].state=' ';
         player2[i][j].state=' ';
       }
     }
}


/*
if linked lists become empty
*/
bool gameOver(void)
{
    if (head1==NULL || head2==NULL)
    {
      return true;
    }
    else
    {
      return false;
    }
}

/*
deletes list of a ship that is completely
destroyed from linked list
*/
void deleteList (struct shipsList *ptr,char player)
{
  if (player=='1')
    {
      //if it is first node
      if (ptr==head1)
        {
          head1=head1->next;
        }
      else
        {
          struct shipsList *p=head1;
          while(p->next!=ptr)
            {
              p=p->next;
            }
          p->next=ptr->next;
        }
    }
  else
    {
      //if it is first node
      if (ptr==head2)
        {
          head2=head2->next;
        }
      else
        {
          struct shipsList *p=head2;
          while(p->next!=ptr)
            {
              p=p->next;
            }
          p->next=ptr->next;
        }
    }
}

/*
checks if all blocks of a ship
are destroyed or not
*/
void checkCompleteExplosion (char player)
{
  struct shipsList *ptr=NULL;
  bool allCrashed;
  if (player=='1')
   {
     ptr=head1;
     while(ptr!=NULL)
       {
         allCrashed=true;
         if (ptr->direction=='H')
           {
             for(int i=0;i<ptr->len;i++)
               {
                 if(player1[ptr->firstRow][(ptr->firstC)+i].state!='E')
                   {
                     allCrashed=false;
                     break;
                   }
               }
             if(allCrashed)
               {
                 //change the state
                 for (int i=0;i<ptr->len;i++)
                   {
                     player1[ptr->firstRow][(ptr->firstC)+i].state='C';
                   }
                 points2+=(25/(ptr->len));
                 //show reserved blocks
                 if (ptr->firstRow>0)
                   {
                     for (int i=0;i<ptr->len;i++)
                       {
                         player1[(ptr->firstRow)-1][(ptr->firstC)+i].state='W';
                       }
                   }
                if(ptr->firstRow<9)
                   {
                    for (int i=0;i<ptr->len;i++)
                       {
                         player1[(ptr->firstRow)+1][(ptr->firstC)+i].state='W';
                       }
                   }
                if (ptr->firstC>0)
                  {
                    if (ptr->firstRow>0)
                        player1[(ptr->firstRow)-1][(ptr->firstC)-1].state='W';
                    if (ptr->firstRow<9)
                        player1[(ptr->firstRow)+1][(ptr->firstC)-1].state='W';
                    player1[(ptr->firstRow)][(ptr->firstC)-1].state='W';
                  }
                if ((ptr->firstC)+(ptr->len)-1<9)
                  {
                    if (ptr->firstRow>0)
                        player1[(ptr->firstRow)-1][(ptr->firstC)+(ptr->len)].state='W';
                    if (ptr->firstRow<9)
                        player1[(ptr->firstRow)+1][(ptr->firstC)+(ptr->len)].state='W';
                    player1[(ptr->firstRow)][(ptr->firstC)+(ptr->len)].state='W';
                  }
                deleteList(ptr,'1');
                break;
               }
           }

         else
         {
           for (int i=0;i<ptr->len;i++)
             {
               if (player1[(ptr->firstRow)+i][ptr->firstC].state!='E')
                 {
                   allCrashed=false;
                   break;
                 }
             }
           if (allCrashed)
             {
               for (int i=0;i<ptr->len;i++)
                 {
                   player1[(ptr->firstRow)+i][ptr->firstC].state='C';
                 }
               points2+=(25/(ptr->len));
               //show reserved blocks
               if (ptr->firstC>0)
                 {
                   for (int i=0;i<ptr->len;i++)
                     {
                       player1[(ptr->firstRow)+i][(ptr->firstC)-1].state='W';
                     }
                 }
               if(ptr->firstC<9)
                 {
                   for(int i=0;i<ptr->len;i++)
                     {
                       player1[(ptr->firstRow)+i][(ptr->firstC)+1].state='W';
                     }
                 }
               if(ptr->firstRow>0)
                 {
                   if (ptr->firstC>0)
                    player1[(ptr->firstRow)-1][(ptr->firstC)-1].state='W';
                   if (ptr->firstC<9)
                    player1[(ptr->firstRow)-1][(ptr->firstC)+1].state='W';
                   player1[(ptr->firstRow)-1][(ptr->firstC)].state='W';
                 }
               if ((ptr->firstRow)+(ptr->len)-1<9)
                 {
                   if(ptr->firstC>0)
                    player1[(ptr->firstRow)+(ptr->len)][(ptr->firstC)-1].state='W';
                   if(ptr->firstC<9)
                    player1[(ptr->firstRow)+(ptr->len)][(ptr->firstC)+1].state='W';
                   player1[(ptr->firstRow)+(ptr->len)][(ptr->firstC)].state='W';
                 }
               deleteList(ptr,'1');
               break;
             }
         }
        ptr=ptr->next;
       }
   }
  else
    {
     ptr=head2;
     while(ptr!=NULL)
       {
         allCrashed=true;
         if (ptr->direction=='H')
           {
             for(int i=0;i<ptr->len;i++)
               {
                 if(player2[ptr->firstRow][(ptr->firstC)+i].state!='E')
                   {
                     allCrashed=false;
                     break;
                   }
               }
             if(allCrashed)
               {
                 //change the state
                 for (int i=0;i<ptr->len;i++)
                   {
                     player2[ptr->firstRow][(ptr->firstC)+i].state='C';
                   }
                 points1+=(25/(ptr->len));
                 //show reserved blocks
                 if (ptr->firstRow>0)
                   {
                     for (int i=0;i<ptr->len;i++)
                       {
                         player2[(ptr->firstRow)-1][(ptr->firstC)+i].state='W';
                       }
                   }
                if(ptr->firstRow<9)
                   {
                    for (int i=0;i<ptr->len;i++)
                       {
                         player2[(ptr->firstRow)+1][(ptr->firstC)+i].state='W';
                       }
                   }
                if (ptr->firstC>0)
                  {
                    if (ptr->firstRow>0)
                        player2[(ptr->firstRow)-1][(ptr->firstC)-1].state='W';
                    if (ptr->firstRow<9)
                         player2[(ptr->firstRow)+1][(ptr->firstC)-1].state='W';
                     player2[(ptr->firstRow)][(ptr->firstC)-1].state='W';
                  }
                if ((ptr->firstC)+(ptr->len)-1<9)
                  {
                    if(ptr->firstRow>0)
                         player2[(ptr->firstRow)-1][(ptr->firstC)+(ptr->len)].state='W';
                    if(ptr->firstRow<9)
                         player2[(ptr->firstRow)+1][(ptr->firstC)+(ptr->len)].state='W';
                    player2[(ptr->firstRow)][(ptr->firstC)+(ptr->len)].state='W';
                  }
                deleteList(ptr,'2');
                break;
               }
           }

         else
         {
           for (int i=0;i<ptr->len;i++)
             {
               if (player2[(ptr->firstRow)+i][ptr->firstC].state!='E')
                 {
                   allCrashed=false;
                   break;
                 }
             }
           if (allCrashed)
             {
               for (int i=0;i<ptr->len;i++)
                 {
                   player2[(ptr->firstRow)+i][ptr->firstC].state='C';
                 }
               points1+=(25/(ptr->len));
               //show reserved blocks
               if (ptr->firstC>0)
                 {
                   for (int i=0;i<ptr->len;i++)
                     {
                       player2[(ptr->firstRow)+i][(ptr->firstC)-1].state='W';
                     }
                 }
               if(ptr->firstC<9)
                 {
                   for(int i=0;i<ptr->len;i++)
                     {
                       player2[(ptr->firstRow)+i][(ptr->firstC)+1].state='W';
                     }
                 }
               if(ptr->firstRow>0)
                 {
                   if(ptr->firstC>0)
                    player2[(ptr->firstRow)-1][(ptr->firstC)-1].state='W';
                   if(ptr->firstC<9)
                    player2[(ptr->firstRow)-1][(ptr->firstC)+1].state='W';
                   player2[(ptr->firstRow)-1][(ptr->firstC)].state='W';
                 }
               if ((ptr->firstRow)+(ptr->len)-1<9)
                 {
                   if(ptr->firstC>0)
                    player2[(ptr->firstRow)+(ptr->len)][(ptr->firstC)-1].state='W';
                   if(ptr->firstC<9)
                    player2[(ptr->firstRow)+(ptr->len)][(ptr->firstC)+1].state='W';
                   player2[(ptr->firstRow)+(ptr->len)][(ptr->firstC)].state='W';
                 }
               deleteList(ptr,'2');
               break;
             }
         }
        ptr=ptr->next;
       }
    }
}

/*
saves game if user input ( -1 S )
in game play
*/
void save(char turn)
{
  FILE *fptr=fopen("lastGame.bin","rb");
  // perhaps it is first time for saving!
  if(fptr!=NULL)
    {
      char buf1[200];
      char buf2[50];
      fread(&buf1,sizeof(char),50,fptr);
      fread(&buf2,sizeof(char),50,fptr);
      fclose(fptr);
      strcat(buf1," vs ");
      strcat(buf1,buf2);
      FILE *f=fopen("listOfGames.txt","a");
      fprintf(f,"%s\n",buf1);
      fclose(f);
      strcat(buf1,".bin");
      rename("lastGame.bin",buf1);
    }
     fptr=fopen("lastGame.bin","wb");
     fwrite(player1Name,sizeof(char),50,fptr);
     fwrite(player2Name,sizeof(char),50,fptr);
     fwrite(&turn,sizeof(char),1,fptr);
     for(int i=0;i<10;i++)
       {
         for(int j=0;j<10;j++)
           {
             fwrite(&player1[i][j].isShip,sizeof(bool),1,fptr);
             fwrite(&player1[i][j].state,sizeof(char),1,fptr);
             fwrite(&player2[i][j].isShip,sizeof(bool),1,fptr);
             fwrite(&player2[i][j].state,sizeof(char),1,fptr);
           }
       }
     fwrite(&points1,sizeof(int),1,fptr);
     fwrite(&points2,sizeof(int),1,fptr);
     int listlen=0;
     struct shipsList *p=head1;
     while(p!=NULL)
       {
         listlen++;
         p=p->next;
       }
     fwrite(&listlen,sizeof(int),1,fptr);
     p=head1;
     while(p!=NULL)
       {
        fwrite(&(p->direction),sizeof(char),1,fptr);
        fwrite(&(p->firstRow),sizeof(int),1,fptr);
        fwrite(&(p->firstC),sizeof(char),1,fptr);
        fwrite(&(p->len),sizeof(int),1,fptr);
        p=p->next;
       }
     listlen=0;
     p=head2;
     while(p!=NULL)
       {
         listlen++;
         p=p->next;
       }
     fwrite(&listlen,sizeof(int),1,fptr);
     p=head2;
     while(p!=NULL)
       {
        fwrite(&(p->direction),sizeof(char),1,fptr);
        fwrite(&(p->firstRow),sizeof(int),1,fptr);
        fwrite(&(p->firstC),sizeof(char),1,fptr);
        fwrite(&(p->len),sizeof(int),1,fptr);
        p=p->next;
       }
     fclose(fptr);
     system("cls");
     printf("game has been saved successfully!\n");
     delay(2000);
     exit(1);
}

/*
use missile by inputing (-2 M)
*/
bool missile(char player)
{
 system("cls");
 createBoard(player=='1'?'2':'1');
 char choice;
 bool firstE=false;//when reach first E state
 printf("enter the row or column you want to attack (n / X) ");
 fflush(stdin);
 scanf("%c",&choice);
 fflush(stdin);
 if (!(choice>='1' && choice<='9') && !(choice>='A' && choice<='J'))
   {
     do{
       printf("invalid input!");
       delay(1500);
       system("cls");
       createBoard(player=='1'?'2':'1');
       printf("enter the row or column you want to attack (n / X) ");
       scanf("%c",&choice);
       fflush(stdin);
     }while(!(choice>='A' && choice<='j') && !(choice>='1' && choice<='9'));
   }
  if (choice>='A' && choice<='J')
    {
      if (player=='1')
      {
        for (int i=0;i<10;i++)
          {
            system("cls");
            createBoard('2');
            delay(1500);
            if(firstE)
                return firstE;
            if (player2[i][choice-65].state==' ')
              {
                if(player2[i][choice-65].isShip==true)
                  {
                    player2[i][choice-65].state='E';
                    points1++;
                    firstE=true;
                  }
                else
                  {
                    player2[i][choice-65].state='W';
                  }
              }
          }
        createBoard('2');
        delay(1500);
        return firstE;
      }
     else
      {
        for (int i=0;i<10;i++)
          {
            system("cls");
            createBoard('1');
            delay(1500);
            if(firstE)
                return firstE;
            if (player1[i][choice-65].state==' ')
              {
                if(player1[i][choice-65].isShip==true)
                  {
                    player1[i][choice-65].state='E';
                    points2++;
                    firstE=true;
                  }
                else
                  {
                    player1[i][choice-65].state='W';
                  }
              }
          }
        createBoard('1');
        delay(1500);
        return firstE;
      }
    }
  else
  {
    if (player=='1')
      {
        for(int i=0;i<10;i++)
          {
            system("cls");
            createBoard('2');
            delay(1500);
            if(firstE)
                return firstE;
            if (player2[choice-49][i].state==' ')
              {
                if (player2[choice-49][i].isShip==true)
                  {
                    player2[choice-49][i].state='E';
                    points1++;
                    firstE=true;
                  }
                else
                  {
                    player2[choice-49][i].state='W';
                  }
              }
          }
        createBoard('2');
        delay(1500);
        return firstE;
      }
    else
      {
        for(int i=0;i<10;i++)
          {
            system("cls");
            createBoard('1');
            delay(1500);
            if(firstE)
                return firstE;
            if (player1[choice-49][i].state==' ')
              {
                if (player1[choice-49][i].isShip==true)
                  {
                    player1[choice-49][i].state='E';
                    points2++;
                    firstE=true;
                  }
                else
                  {
                    player1[choice-49][i].state='W';
                  }
              }
          }
        createBoard('1');
        delay(1500);
        return firstE;
      }

  }
}



/*
main function in game!!
*/
void gamePlay(void)
{
  int row;
  char column;
  static char player='1';
  system("cls");
  createBoard((player=='1')?'2':'1');
  printf("%s : %d\t%s : %d\n",player1Name,points1,player2Name,points2);
  printf("%s choose the target (n X) ",(player=='1')?player1Name:player2Name);
  scanf("%d %c",&row,&column);
  if (row==-1 && column=='S')
    save((player=='1'?'1':'2'));
  if (row==-2 && column=='M')
    {
      if ((player=='1' && points1<100) || (player=='2' && points2<100))
        {
          printf("you don't have enough point to use missile!");
          delay(2000);
          return;
        }
      if (player=='1')
            points1-=100;
      else
            points2-=100;
      bool missilleCrashed=missile(player);
      if (!missilleCrashed)
        {
          player=player=='1'?'2':'1';
        }
      return;
    }
  if (player=='1')
    {
      if(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
         || row<1 || column<'A')
        {
          do{
            printf("you can't choose this!");
            delay(1000);
            system("cls");
            createBoard('2');
            printf("%s choose the target (n X) ",(player=='1')?player1Name:player2Name);
            scanf("%d %c",&row,&column);
          }while(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
                 || row<1 || column<'A');
        }
      if (player2[row-1][column-65].isShip)
        {
          player2[row-1][column-65].state='E';
          points1++;
          checkCompleteExplosion('2');
          system("cls");
          createBoard('2');
          delay(3000);
        }
     else
        {
          player2[row-1][column-65].state='W';
          system("cls");
          createBoard('2');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
  else
    {
      if(player1[row-1][column-65].state!=' ' || row>10 || column>'J'
         || row<1 || column<'A')
        {
          do{
            printf("you can't choose this!");
            delay(1000);
            system("cls");
            createBoard((player=='1')?'2':'1');
            printf("%s choose the target (n X) ",(player=='1')?player1Name:player2Name);
            scanf("%d %c",&row,&column);
          }while(player1[row-1][column-65].state!=' ' || row>10 || column>'J'
                 || row<1 || column<'A');
        }
      if (player1[row-1][column-65].isShip)
        {
          player1[row-1][column-65].state='E';
          points2++;
          checkCompleteExplosion('1');
          system("cls");
          createBoard('1');
          delay(3000);
        }
     else
        {
          player1[row-1][column-65].state='W';
          system("cls");
          createBoard('1');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
}

/*
add new users to the file
*/
int newUser(char *nu)
{
  char buf[50];
  int temp;
  bool exist=false;
  FILE *fptr=fopen("users.txt","r");
  //checks if player exist or not
  while(fscanf(fptr,"%s %d\n",buf,&temp)!=EOF)
  {
    if (strcmp(buf,nu)==0)
    {
      exist=true;
      break;
    }
  }
  if (exist)
    {
     printf("this player exists in list!\nchoose another one");
     fclose(fptr);
     return 1; //cant be added
    }
  else
    {
     fclose(fptr);
     fptr=fopen("users.txt","a");
     fprintf(fptr,"%s %d\n",nu,0);
     fclose(fptr);
     return 0;
    }
}

/*
show lists of users
*/
void showUsers(char player)
{
  system("cls");
  char buffer[50];
  int coin;
  bool found=false;
  FILE *fptr=fopen("users.txt","r");
  if (fptr==NULL)
  {
    printf("unable to open file...");
    exit(-1);
  }
  fseek(fptr,0,SEEK_END);
  unsigned long long int lenFile=(unsigned long long int)ftell(fptr);
  if (lenFile==0)
  {
    printf("there isn't any player...\n");
    printf("add new user : \n");
    fclose(fptr);
    int x;
    do{
      if (player=='1')
      {
        scanf("%s",player1Name);
        x=newUser(player1Name);
      }
      else
      {
        scanf("%s",player2Name);
        x=newUser(player2Name);
      }
    }while(x==1);
  }
  else
  {
    rewind(fptr);
    while(fscanf(fptr,"%s %d\n",buffer,&coin)!=EOF)
     {
      printf("%s : %d\n",buffer,coin);
     }
    rewind(fptr);
    if (player=='1')
    {
      printf("enter name...");
      scanf("%s",player1Name);
      while(fscanf(fptr,"%s %d\n",buffer,&coin)!=EOF)
        {
          if(strcmp(player1Name,buffer)==0)
            {
              found=true;
              break;
            }
        }
     fclose(fptr);
     if (!found)
       {
         printf("this player doesn't exists\n");
         printf("it will be added as new player!\n");
         delay(2500);
         int x=newUser(player1Name);
       }
    }

   else
    {
      printf("enter name...");
      scanf("%s",player2Name);
      bool found=false;
      while(fscanf(fptr,"%s %d\n",buffer,&coin)!=EOF)
        {
          if(strcmp(player2Name,buffer)==0)
            {
              found=true;
              break;
            }
        }
     if (!found)
       {
         printf("this player doesn't exists\n");
         printf("add this to new players\n");
         int x=newUser(player2Name);
       }
    }
  }
}

/*
to show the menu of choose user
*/
void chooseUser(char player)
{
  system("cls");
  int choice,x;
  if (player=='1')
    {
      do
      {
        system("cls");
        printf("First Player , choose user\n\n");
        printf("1) choose from available users\n");
        printf("2) new user\n");
        scanf("%d",&choice);
      }while(choice!=1 && choice!=2);
    }
  else
    {
      do{
         system("cls");
         printf("Second Player , choose user\n\n");
         printf("1) choose from available users\n");
         printf("2) new user\n");
         scanf("%d",&choice);
      }while(choice!=1 && choice!=2);
    }
  switch (choice)
  {
    case 1:
      showUsers((player=='1')?'1':'2');
      break;
    case 2:
      system("cls");
      if (player=='1')
        {
          printf("enter your name...");
          scanf("%s",player1Name);
          x=newUser(player1Name);
          if(x==1)
            {
              do
              {
                delay(2000);
                system("cls");
                printf("enter your name...");
                scanf("%s",player1Name);
                x=newUser(player1Name);
              }while(x==1);
            }
        }
      else
        {
          printf("enter your name...");
          scanf("%s",player2Name);
          x=newUser(player2Name);
          if(x==1)
            {
              do
              {
                delay(2000);
                system("cls");
                scanf("%s",player2Name);
                x=newUser(player2Name);
              }while(x==1);
            }
        }
      break;
  }
}


/*
after game over saves new coins to its
player in the users file
*/
void coinSaver(int p1coins,int p2coins)
{
  FILE *fptr=fopen("users.txt","r");
  char names[100][50];
  int i=0;
  int otherCoins[100];//coins that each player has before
  while(fscanf(fptr,"%s %d\n",names[i],&otherCoins[i])!=EOF)
    {
      i++;
    }
  fclose(fptr);
  fptr=fopen("users.txt","w");
  for (int j=0;j<i;j++)
  {
    if(strcmp(names[j],player1Name)==0)
      {
        fprintf(fptr,"%s %d\n",player1Name,otherCoins[j]+p1coins);
      }
    else if(strcmp(names[j],player2Name)==0)
      {
        fprintf(fptr,"%s %d\n",player2Name,otherCoins[j]+p2coins);
      }
    else
      {
        fprintf(fptr,"%s %d\n",names[j],otherCoins[j]);
      }
  }
 fclose(fptr);
}

/*
sorting users according to
their points in users.txt
*/
void sortUsers(void)
{
  char names[100][50],tempC[50];
  int points[100];
  int i=0,j,k,temp;
  FILE *fptr=fopen("users.txt","r");
  while(fscanf(fptr,"%s %d\n",names[i],&points[i])!=EOF)
  {
    i++;
  }
  fclose(fptr);
  //bubble sort!
  for(j=0;j<i;j++)
    {
      for(k=j+1;k<i;k++)
        {
          if (points[j]<points[k])
            {
              temp=points[j];
              points[j]=points[k];
              points[k]=temp;
              //swap for string!
              strcpy(tempC,names[j]);
              strcpy(names[j],names[k]);
              strcpy(names[k],tempC);
            }
        }
    }
  fptr=fopen("users.txt","w");
  for(j=0;j<i;j++)
  {
    fprintf(fptr,"%s %d\n",names[j],points[j]);
  }
  fclose(fptr);
}



/*
works should be done after game over
*/
void afterGame(int n)// n : number of players
{
  if(n==2)
  {
    if(head1==NULL)
     {
       printf("%s win!",player2Name);
       int p2=points2;
       int p1=(points1/2);
       coinSaver(p1,p2);
     }
    else
     {
       printf("%s win!",player1Name);
       int p1=points1;
       int p2=(points2/2);
       coinSaver(p1,p2);
     }
  }

 else
 {
     if (head1==NULL)
       {
        printf("Bot win!");
        points1=(points1/2);
       }
     else
       {
        printf("%s win!",player1Name);
       }
     //it's like coinSaver but for single player!
     FILE *fptr=fopen("users.txt","r");
     char names[100][50];int otherCoins[100];
     int i=0;
     while(fscanf(fptr,"%s %d\n",names[i],&otherCoins[i])!=EOF)
       {
         i++;
       }
     fclose(fptr);
     fptr=fopen("users.txt","w");
     for (int j=0;j<i;j++)
       {
         if (strcmp(names[j],player1Name)==0)
           {
             fprintf(fptr,"%s %d\n",player1Name,otherCoins[j]+points1);
           }
         else
           {
             fprintf(fptr,"%s %d\n",names[j],otherCoins[j]);
           }
       }
     fclose(fptr);

 }
 sortUsers();
}

/*
put bot's ships
*/
void putBot(void)
{
  player2Name[0]='B';
  player2Name[1]='o';
  player2Name[2]='t';
  createNode('H',1,1,5,'2');
  for(int i=0;i<5;i++)
  {
    player2[1][1+i].isShip=true;
  }
  createNode('V',4,2,3,'2');
  for(int i=0;i<3;i++)
  {
    player2[4+i][2].isShip=true;
  }
  createNode('H',3,5,3,'2');
  for(int i=0;i<3;i++)
  {
    player2[3][5+i].isShip=true;
  }
  createNode('H',5,4,2,'2');
  for(int i=0;i<2;i++)
  {
    player2[5][4+i].isShip=true;
  }
  createNode('V',4,9,2,'2');
  for(int i=0;i<2;i++)
  {
    player2[4+i][9].isShip=true;
  }
  createNode('V',7,0,2,'2');
  for(int i=0;i<2;i++)
  {
    player2[7+i][0].isShip=true;
  }
  createNode('H',1,8,1,'2');
  player2[1][8].isShip=true;
  createNode('H',7,6,1,'2');
  player2[7][6].isShip=true;
  createNode('H',3,0,1,'2');
  player2[3][0].isShip=true;
  createNode('H',8,9,1,'2');
  player2[8][9].isShip=true;
}



/*
game play with bot
*/
void gamePlayBot(void)
{
  int row;
  char column;
  static char player='1';
  system("cls");
  if (player=='1')
    {
      createBoard('2');
      printf("%s : %d\t%s : %d\n",player1Name,points1,player2Name,points2);
      printf("%s choose the target (n X) ",player1Name);
      scanf("%d %c",&row,&column);
      if (row==-1 && column=='S')
        save('1');
      if (row==-2 && column=='M')
       {
         if ((points1<100))
          {
          printf("you don't have enough point to use missile!");
          delay(2000);
          return;
          }
        points1-=100;
        bool missilleCrashed=missile(player);
        if (!missilleCrashed)
         {
          player=player=='1'?'2':'1';
         }
       return;
    }
      if(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
         || row<1 || column<'A')
        {
          do{
            printf("you can't choose this!");
            delay(1000);
            system("cls");
            createBoard('2');
            printf("%s choose the target (n X) ",player1Name);
            scanf("%d %c",&row,&column);
          }while(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
                 || row<1 || column<'A');
        }
      if (player2[row-1][column-65].isShip)
        {
          player2[row-1][column-65].state='E';
          points1++;
          checkCompleteExplosion('2');
          system("cls");
          createBoard('2');
          delay(3000);
        }
     else
        {
          player2[row-1][column-65].state='W';
          system("cls");
          createBoard('2');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
  else
    {
      srand(time(NULL));
      int r,c;
      createBoard('1');
      printf("Bot is choosing target...");
      delay(1500);
      do
      {
        r=(rand()%10);
        c=(rand()%10);
      }while(((r>9)||(c>9))||(player1[r][c].state!=' '));
      if (player1[r][c].isShip)
        {
          player1[r][c].state='E';
          points2++;
          checkCompleteExplosion('1');
          system("cls");
          createBoard('1');
          delay(3000);
        }
     else
        {
          player1[r][c].state='W';
          system("cls");
          createBoard('1');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
}


/*
game play for multi player mode after loading the
game.difference with gamePlay is the
argument <turn>
*/
void gamePlayS(char turn)
{
  int row;
  char column;
  static bool set=false;
  static char player;
  if(!set)
  {
    player=turn;
    set=true;
  }
  system("cls");
  createBoard((player=='1')?'2':'1');
  printf("%s : %d\t%s : %d\n",player1Name,points1,player2Name,points2);
  printf("%s choose the target (n X) ",(player=='1')?player1Name:player2Name);
  scanf("%d %c",&row,&column);
  if (row==-1 && column=='S')
    save((player=='1'?'1':'2'));
  if (row==-2 && column=='M')
    {
      if ((player=='1' && points1<100) || (player=='2' && points2<100))
        {
          printf("you don't have enough point to use missile!");
          delay(2000);
          return;
        }
      if (player=='1')
            points1-=100;
      else
            points2-=100;
      bool missilleCrashed=missile(player);
      if (!missilleCrashed)
        {
          player=player=='1'?'2':'1';
        }
      return;
    }
  if (player=='1')
    {
      if(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
         || row<1 || column<'A')
        {
          do{
            printf("you can't choose this!");
            delay(1000);
            system("cls");
            createBoard('2');
            printf("%s choose the target (n X) ",(player=='1')?player1Name:player2Name);
            scanf("%d %c",&row,&column);
          }while(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
                 || row<1 || column<'A');
        }
      if (player2[row-1][column-65].isShip)
        {
          player2[row-1][column-65].state='E';
          points1++;
          checkCompleteExplosion('2');
          system("cls");
          createBoard('2');
          delay(3000);
        }
     else
        {
          player2[row-1][column-65].state='W';
          system("cls");
          createBoard('2');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
  else
    {
      if(player1[row-1][column-65].state!=' ' || row>10 || column>'J'
         || row<1 || column<'A')
        {
          do{
            printf("you can't choose this!");
            delay(1000);
            system("cls");
            createBoard((player=='1')?'2':'1');
            printf("%s choose the target (n X) ",(player=='1')?player1Name:player2Name);
            scanf("%d %c",&row,&column);
          }while(player1[row-1][column-65].state!=' ' || row>10 || column>'J'
                 || row<1 || column<'A');
        }
      if (player1[row-1][column-65].isShip)
        {
          player1[row-1][column-65].state='E';
          points2++;
          checkCompleteExplosion('1');
          system("cls");
          createBoard('1');
          delay(3000);
        }
     else
        {
          player1[row-1][column-65].state='W';
          system("cls");
          createBoard('1');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
}

/*
game play for single player mode after loading
the saved game,difference with gamePlayBot
is the argument <turn>
*/
void gamePlayBotS(char turn)
{
  int row;
  char column;
  static bool set=false;
  static char player;
  if(!set)
    {
      player=turn;
      set=true;
    }
  system("cls");
  if (player=='1')
    {
      createBoard('2');
      printf("%s : %d\t%s : %d\n",player1Name,points1,player2Name,points2);
      printf("%s choose the target (n X) ",player1Name);
      scanf("%d %c",&row,&column);
      if (row==-1 && column=='S')
        save('1');
      if (row==-2 && column=='M')
       {
         if ((points1<100))
          {
          printf("you don't have enough point to use missile!");
          delay(2000);
          return;
          }
        points1-=100;
        bool missilleCrashed=missile(player);
        if (!missilleCrashed)
         {
          player=player=='1'?'2':'1';
         }
       return;
    }
      if(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
         || row<1 || column<'A')
        {
          do{
            printf("you can't choose this!");
            delay(1000);
            system("cls");
            createBoard('2');
            printf("%s choose the target (n X) ",player1Name);
            scanf("%d %c",&row,&column);
          }while(player2[row-1][column-65].state!=' ' || row>10 || column>'J'
                 || row<1 || column<'A');
        }
      if (player2[row-1][column-65].isShip)
        {
          player2[row-1][column-65].state='E';
          points1++;
          checkCompleteExplosion('2');
          system("cls");
          createBoard('2');
          delay(3000);
        }
     else
        {
          player2[row-1][column-65].state='W';
          system("cls");
          createBoard('2');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
  else
    {
      srand(time(NULL));
      int r,c;
      createBoard('1');
      printf("Bot is choosing target...");
      delay(1500);
      do
      {
        r=(rand()%10);
        c=(rand()%10);
      }while(((r>9)||(c>9))||(player1[r][c].state!=' '));
      if (player1[r][c].isShip)
        {
          player1[r][c].state='E';
          points2++;
          checkCompleteExplosion('1');
          system("cls");
          createBoard('1');
          delay(3000);
        }
     else
        {
          player1[r][c].state='W';
          system("cls");
          createBoard('1');
          delay(3000);
          player=(player=='1')?'2':'1';
        }
    }
}

/*
load games except last one
*/
char loadGames(char *nameOfFile)
{
  system("cls");
  char turn;
  strcat(nameOfFile,".bin");
  FILE *fptr=fopen(nameOfFile,"rb");
  if (fptr==NULL)
    {
      printf("there isn't any game like this before!\n");
      delay(2000);
      exit(-1);
    }
   fread(player1Name,sizeof(char),50,fptr);
   fread(player2Name,sizeof(char),50,fptr);
   fread(&turn,sizeof(char),1,fptr);
   for (int i=0;i<10;i++)
     {
       for(int j=0;j<10;j++)
         {
           fread(&player1[i][j].isShip,sizeof(bool),1,fptr);
           fread(&player1[i][j].state,sizeof(char),1,fptr);
           fread(&player2[i][j].isShip,sizeof(bool),1,fptr);
           fread(&player2[i][j].state,sizeof(char),1,fptr);
         }
     }
   fread(&points1,sizeof(int),1,fptr);
   fread(&points2,sizeof(int),1,fptr);
   int listlen;
   char dir,c;
   int r,l;
   fread(&listlen,sizeof(int),1,fptr);
   for(int i=0;i<listlen;i++)
    {
       fread(&dir,sizeof(char),1,fptr);
       fread(&r,sizeof(int),1,fptr);
       fread(&c,sizeof(char),1,fptr);
       fread(&l,sizeof(int),1,fptr);
       createNode(dir,r,c,l,'1');
    }
   fread(&listlen,sizeof(int),1,fptr);
   for(int i=0;i<listlen;i++)
    {
       fread(&dir,sizeof(char),1,fptr);
       fread(&r,sizeof(int),1,fptr);
       fread(&c,sizeof(char),1,fptr);
       fread(&l,sizeof(int),1,fptr);
       createNode(dir,r,c,l,'2');
    }
  return turn;
}

/*
shows list of previous game
for user to choose one of them
*/
void showGamesList(void)
{
  system("cls");
  printf("here is list of previous games\n\n");
  FILE *fptr=fopen("listOfGames.txt","r");
  char buf[100];
  char buf2[100];
  char buf3[100];
  while(fscanf(fptr,"%s %s %s\n",buf,buf2,buf3)!=EOF)
    {
      printf("%s %s %s\n",buf,buf2,buf3);
    }
  fclose(fptr);
}



/*
loading last game
*/
char loadLastGame(void)
{
  system("cls");
  char turn;
  FILE *fptr=fopen("lastGame.bin","rb");
  if (fptr==NULL)
    {
      printf("there isn't any game before!\n");
      delay(1500);
      exit(-1);
    }
   fread(player1Name,sizeof(char),50,fptr);
   fread(player2Name,sizeof(char),50,fptr);
   fread(&turn,sizeof(char),1,fptr);
   for (int i=0;i<10;i++)
     {
       for(int j=0;j<10;j++)
         {
           fread(&player1[i][j].isShip,sizeof(bool),1,fptr);
           fread(&player1[i][j].state,sizeof(char),1,fptr);
           fread(&player2[i][j].isShip,sizeof(bool),1,fptr);
           fread(&player2[i][j].state,sizeof(char),1,fptr);
         }
     }
   fread(&points1,sizeof(int),1,fptr);
   fread(&points2,sizeof(int),1,fptr);
   int listlen;
   char dir,c;
   int r,l;
   fread(&listlen,sizeof(int),1,fptr);
   for(int i=0;i<listlen;i++)
    {
       fread(&dir,sizeof(char),1,fptr);
       fread(&r,sizeof(int),1,fptr);
       fread(&c,sizeof(char),1,fptr);
       fread(&l,sizeof(int),1,fptr);
       createNode(dir,r,c,l,'1');
    }
   fread(&listlen,sizeof(int),1,fptr);
   for(int i=0;i<listlen;i++)
    {
       fread(&dir,sizeof(char),1,fptr);
       fread(&r,sizeof(int),1,fptr);
       fread(&c,sizeof(char),1,fptr);
       fread(&l,sizeof(int),1,fptr);
       createNode(dir,r,c,l,'2');
    }
  fclose(fptr);
  return turn;
}

/*
shows score board
*/
void scoreBoard(void)
{
 sortUsers();
 char buf[50];
 int point;
 FILE *fptr=fopen("users.txt","r");
 while(fscanf(fptr,"%s %d\n",buf,&point)!=EOF)
 {
   printf("%s : %d points\n",buf,point);
 }
 fclose(fptr);
}


/*
menu of game
*/
void menu(void)
{
  int choice;
  do{
    do{
     system("cls");
     printf("1) Play with a Friend\n");
     printf("2) Play with bot\n");
     printf("3) Load game\n");
     printf("4) Load last game\n");
     printf("5) Settings\n");
     printf("6) Score Board\n");
     printf("7) Exit\n");
     scanf("%d",&choice);
    }while(choice>7);
  switch (choice)
  {
   case 1:
     makeEmpty();
     chooseUser('1');
     putShips('1');
     chooseUser('2');
     putShips('2');
     hide();
     while(!gameOver())
     {
       gamePlay();
     }
     afterGame(2);
     printf("\n\nyou will be forwarded to main menu in few seconds...");
     delay(4000);
     break;
   case 2:
     makeEmpty();
     chooseUser('1');
     putShips('1');
     putBot();
     hide();
     while(!gameOver())
       {
         gamePlayBot();
       }
     afterGame(1);
     printf("\n\nyou will be forwarded to main menu in few seconds...");
     delay(4000);
     break;
   case 3:
     {
       showGamesList();
       char name[100];
       printf("choose one of them...");
       fflush(stdin);
       gets(name);
       char turn=loadGames(name);
       if (strcmp(player2Name,"Bot")==0)
         {
           while(!gameOver())
             {
               gamePlayBotS(turn);
             }
           afterGame(1);
         }
       else
         {
           while(!gameOver())
             {
               gamePlayS(turn);
             }
           afterGame(2);
         }
       printf("\n\nyou will be forwarded to main menu in few seconds...");
       delay(4000);
       break;
     }
   case 4:
    {
     char turn=loadLastGame();
     printf("the game was between %s and %s",player1Name,player2Name);
     delay(3000);
     if (strcmp(player2Name,"Bot")==0)
       {
         while(!gameOver())
          {
           gamePlayBotS(turn);
          }
         afterGame(1);
       }
     else
       {
         while(!gameOver())
         {
            gamePlayS(turn);
         }
         afterGame(2);
       }
     printf("\n\nyou will be forwarded to main menu in few seconds...");
     delay(4000);
     break;
    }
   case 5:
     system("cls");
     printf("nothing to show yet!!");
     delay(2000);
     break;
   case 6:
     system("cls");
     scoreBoard();
     delay(3000);
     printf("\n\nyou will be forwarded to main menu in few seconds...");
     delay(4000);
     break;
   default:
     break;
  }
  }while(choice!=7);
}

int main()
{
    menu();
    return 0;
}
