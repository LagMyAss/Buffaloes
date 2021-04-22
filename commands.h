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
    printf("\nEnding the game..");
}

void cHelp()
{
    
}

void cWisdom()
{

}