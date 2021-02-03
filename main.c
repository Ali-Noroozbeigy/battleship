#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>


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
    printf("   ");
    for (int i=0;i<60;i++)
        printf("-");
    printf("\n");
}

/*
gets the coordinates of ships
and shows the preview of each player's ship
*/
void putShips(char player)
{
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
      printf("player %c enter first and last coordinate(n X m Y) ",player);
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
                  createNode('H',firstRow-1,firstC-65,len,'1');
                  if (firstRow>=2)
                    player1[firstRow-2][j-65].isReserved=true;
                  if (firstRow<=9)
                    player1[firstRow][j-65].isReserved=true;
                 }
                else
                 {
                  player2[firstRow-1][j-65].state='o';
                  player2[firstRow-1][j-65].isShip=true;
                  createNode('H',firstRow-1,firstC-65,len,'2');
                  if (firstRow>=2)
                    player2[firstRow-2][j-65].isReserved=true;
                  if (firstRow<=9)
                    player2[firstRow][j-65].isReserved=true;
                 }
              }

             if (firstC-65>=1)
               {
                 for (int j=0;j<3;j++)
                   {
                    if (player=='1')
                     player1[firstRow-2+j][firstC-65-1].isReserved=true;
                    else
                     player2[firstRow-2+j][firstC-65-1].isReserved=true;
                   }
               }
             if (secondC-65<=8)
               {
                 for (int j=0;j<3;j++)
                   {
                    if (player=='1')
                     player1[firstRow-2+j][secondC-65+1].isReserved=true;
                    else
                     player2[firstRow-2+j][secondC-65+1].isReserved=true;
                   }
               }

             i++;
          }
       }
      else if (firstC==secondC)
       {
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
                  createNode('V',firstRow-1,firstC-65,len,'1');
                  if (firstC-65>=1)
                    player1[j-1][firstC-65-1].isReserved=true;
                  if (firstC-65<=8)
                    player1[j-1][firstC-65+1].isReserved=true;
                 }
                else
                 {
                  player2[j-1][firstC-65].state='o';
                  player2[j-1][firstC-65].isShip=true;
                  createNode('V',firstRow-1,firstC-65,len,'2');
                  if (firstC-65>=1)
                    player2[j-1][firstC-65-1].isReserved=true;
                  if (firstC-65<=8)
                    player2[j-1][firstC-65+1].isReserved=true;
                 }
              }

             if (firstRow-1>=1)
               {
                 for (int j=0;j<3;j++)
                   {
                     if (player=='1')
                       {
                         player1[firstRow-2][firstC-65-1+j].isReserved=true;
                       }
                     else
                       {
                         player2[firstRow-2][firstC-65-1+j].isReserved=true;
                       }
                   }
               }
             if (secondRow-1<=8)
               {
                 for (int j=0;j<3;j++)
                   {
                     if (player=='1')
                       {
                         player1[firstRow-1+1][firstC-65-1+j].isReserved=true;
                       }
                     else
                       {
                         player2[firstRow-1+1][firstC-65-1+j].isReserved=true;
                       }
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

int main()
{
    makeEmpty();
    putShips('1');
    return 0;
}
