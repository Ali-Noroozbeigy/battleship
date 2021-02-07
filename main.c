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

/*name of players and coins*/
char player1Name[50]={'\0'},player2Name[50]={'\0'};
int coin1,coin2;
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
    printf("   ");
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
            printf("player %c choose the target (n X) ",(player=='1')?player1Name:player2Name);
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
            printf("player %c choose the target (n X) ",(player=='1')?player1Name:player2Name);
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
        coin1=0;
      }
      else
      {
        scanf("%s",player2Name);
        x=newUser(player2Name);
        coin2=0;
      }
    }while(x==1);
  }
  else
  {
    rewind(fptr);
    while(fscanf(fptr,"%s %d\n",buffer,&coin)!=EOF)
     {
      printf("%s \n",buffer);
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
              coin1=coin;
              found=true;
              break;
            }
        }
     fclose(fptr);
     if (!found)
       {
         printf("this player doesn't exists\n");
         printf("it will be added as new player!\n");
         int x=newUser(player1Name);
         coin1=0;
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
              coin2=coin;
              found=true;
              break;
            }
        }
     if (!found)
       {
         printf("this player doesn't exists\n");
         printf("add this to new players\n");
         int x=newUser(player2Name);
         coin2=0;
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
                //player1Name={'\0'};
                scanf("%s",player1Name);
                x=newUser(player1Name);
              }while(x==1);
            }
          coin1=0;
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
                //player2Name={'\0'};
                scanf("%s",player2Name);
                x=newUser(player2Name);
              }while(x==1);
            }
          coin2=0;
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
  FILE *fin=fopen("users.txt","r");
  FILE *fout=fopen("temp.txt","w");
  char buf[50];
  int otherCoins;//other player's coins
  while(fscanf(fin,"%s %d\n",buf,&otherCoins)!=EOF)
    {
      if (strcmp(buf,player1Name)==0)
        {
          fprintf(fout,"%s %d\n",player1Name,p1coins);
        }
      else if (strcmp(buf,player2Name)==0)
        {
          fprintf(fout,"%s %d\n",player2Name,p2coins);
        }
      else
        {
          fprintf(fout,"%s %d\n",buf,otherCoins);
        }
    }
  fclose(fin);
  fclose(fout);
  remove("users.txt");
  rename("temp.txt","users.txt");
}

/*
works should be done after game over
*/
void afterGame(void)
{
  if(head1==NULL)
  {
    printf("player 2 win!");
    int p2=points2+coin2;
    int p1=(points1/2)+coin1;
    coinSaver(p1,p2);
  }
  else
  {
    printf("player 1 win!");
    int p1=points1+coin1;
    int p2=(points2/2)+coin2;
    coinSaver(p1,p2);
  }
}



/*
menu of game
*/
void menu(void)
{
  printf("1) Play with a Friend\n");
  printf("2) Play with bot\n");
  printf("3) Load game");
  printf("4) Load last game\n");
  printf("5) Settings\n");
  printf("6) Score Board\n");
  printf("7) Exit\n");
  int choice;
  scanf("%d",&choice);
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
     afterGame();
     break;
  }
}

int main()
{
    menu();
    return 0;
}
