#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#include "commands.h"

#define minxy 4

int main()
{
    srand(time(NULL));
    int x, y, dif, i, j, active = 1, level = 1, countb, ux, uy;
    char prefix[100];
    float a;

    printf("\n************************************");
    printf("\n*      Welcome to Buffalo Game     *");
    printf("\n*      a minesweeper like game     *");
    printf("\n*      Good luck and Have Fun!     *");
    printf("\n************************************");
    printf("\n\nThe game starts :\n");
    printf("\nPlease enter the dimensions of the table you want to play BUT ( x, y > %d )..", minxy);

    do
    {
        printf("\nx = ");
        scanf("%d", &x);
        if(x < minxy)
        {
            printf("\nThe value of x must be greater than the minimum which is %d or equal, try again.", minxy);
        }
    }while(x < minxy);

    do
    {
        printf("y = ");
        scanf("%d", &y);
        if(y < minxy)
        {
            printf("\nThe value of y must be greater than the minimum which is %d or equal, try again.", minxy);
        }
    }while(y < minxy);

    printf("\nGreat! The table will be %dx%d !\n", x, y);
    printf("\nNow Enter the number of the difficulty you want to play : ");
    printf("\n1) Easy\n2) Medium\n3) Hard\n4) Impossible\nDifficulty : ");
    scanf("%d", &dif);

    char **board;
    int **checkBoard;
    
    // Alocate dynamicly memory for the table board
    board = (char **) malloc (x * sizeof(char *));
    checkBoard = (int **) malloc (x * sizeof(int *));

    for(i = 0; i < x; i++)
    {
        board[i] = (char *) malloc (y * sizeof(char));
        checkBoard[i] = (int *) malloc (y * sizeof(int));
    }

    // if memory cannot be allocated
    if(board == NULL || checkBoard == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }
    
    fStart(x, y, board, checkBoard);
    fBuffalo(x, y, dif, board, &countb);
    fBells(x, y, board);
    printBoard(x, y, board, checkBoard);

    printf("\nLevel : %d", level);
    printf("\nDifficulty : ");
    switch(dif)
    {
        case 1:
        {
            printf("Easy");
            break;
        }
        case 2:
        {
            printf("Medium");
            break;
        }
        case 3:
        {
            printf("Hard");
            break;
        }
        case 4:
        {
            printf("Impossible");
            break;
        }
    }
    printf("\nUncovered buffaloes : %d", countb);
    printf("\nMake your move : ");
    scanf(" %[^\n]s", prefix); // prefix [0] == cmd, prefix[2] == x, prefix[4] == y
    
    if(prefix[0] == 's')
    {
        ux = ((int) prefix[2]) - '/';
        uy = ((int) prefix[4]) - '/';
        cShow(ux,uy,checkBoard);
        if(board[ux][uy] == '@')
        {
            active = 0;
            printBoard(x, y, board, checkBoard);
            printf("\nYou're Dead! \nA buffalo jumped on your head! G4M3 0V3R!");
        }
    }



    /* For test, printing tables elements
    for(i = 0; i < x;i++)
    {
        for(j = 0;j < y;j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }*/

    // free memory
    for(i = 0; i < y; i++)
    {
        free(board[i]);
    }
    free(board);

    return 0;
}