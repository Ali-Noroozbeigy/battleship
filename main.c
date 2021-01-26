#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>


/*
structure that saves all information
about each block
*/
struct Information{
  char state;
  bool isShip;
};
typedef struct Information Info;


/* blocks of game*/
Info blocks[10][10];

/*
make all the blocks empty before
choosing a block for ship
*/
void makeEmpty (void)
{
    for (int i=0;i<10;i++)
      {
        for (int j=0;j<10;j++)
            blocks[i][j].state=' ';
      }
    for (int i=0;i<10;i++)
      {
        for (int j=0;j<10;j++)
          blocks[i][j].isShip=false;
      }
}


// creates board of game
void createBoard(void)
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
                   printf("|  %c  ",blocks[i][k].state);
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

int main()
{

    makeEmpty();
    createBoard();
    return 0;
}
