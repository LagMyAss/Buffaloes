#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"

#define minxy 4

int main()
{
    srand(time(NULL));
    int x, y, dif, i, j;
    float a;

    printf("The game starts :");
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
        printf("\ny = ");
        scanf("%d", &y);
        if(y < minxy)
        {
            printf("\nThe value of y must be greater than the minimum which is %d or equal, try again.", minxy);
        }
    }while(y < minxy);

    printf("\nGreat! The table will be %dx%d !\n", x, y);
    printf("\nNow Enter the number of the difficulty : ");
    printf("\n1) Easy\n2) Medium\n3) Hard\n4) Impossible\nDifficulty : ");
    scanf("%d", &dif);

    char **board;
    int **checkBoard;
    
    // Alocate dynamicly memory for the table board
    board = (char **) malloc (y * sizeof(char *));
    checkBoard = (int **) malloc (y * sizeof(int *));

    for(i = 0; i < x; i++)
    {
        board[i] = (char *) malloc (x * sizeof(char));
        checkBoard[i] = (int *) malloc (x * sizeof(int));
    }

    // if memory cannot be allocated
    if(board == NULL || checkBoard == NULL)                     
    {
        printf("Error! memory not allocated.");
        exit(0);
    }

    fStart(x, y, board, checkBoard);
    fBuffalo(x, y, dif, board);
    fBells(x, y, board);

    

    // free memory
    for(i = 0; i < y; i++)
    {
        free(board[i]);
    }
    free(board);

    return 0;
}