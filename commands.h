#include <stdio.h>
#include <stdlib.h>

void cShow(int x, int y, char **board, int **checkBoard, int *active)
{
    if(board[x][y] == '@')
    {
        *active = 0;
        printf("\nYou're Dead! \nA buffalo jumped on your head! G4M3 0V3R!");
    }
    else
    {
        checkBoard[x][y] = 1;
    }
}

void cMark(int x, int y, int **checkBoard)
{
    if(checkBoard[x][y] == 0)
    {
        checkBoard[x][y] = 2;
    }
    else
    {
        printf("\n%d,%d is already opened or marked. Try other coordinates.\n", x,y);
    }
}

void cExit(int *active)
{
    *active = 0;
    printf("\nEnding the game.. Better luck next time :(");
}

void cHelp(int x, int y, int *hx, int *hy, char **board, int **checkBoard)
{
    do
    {
        *hx = rand() % x;
        *hy = rand() % y;
    }while(board[*hx][*hy] == '@' || checkBoard[*hx][*hy] != 0);
    (*hx)++;
    (*hy)++;
}

void cWisdom(int mx, int my, char **board, int **checkBoard, int *rx, int *ry)
{
    int i, j;

    for(i = 0;i < mx;i++)
    {
        for(j = 0;j < my;j++)
        {
            if(board[i][j] == '.')
            {
                *rx = i + 1;
                *ry = j + 1;
                break;
            } 
        }
    }
}