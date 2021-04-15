#include <stdio.h>
#include <stdlib.h>

void cShow(int x, int y, char **board, int **checkBoard, int *active)
{
    checkBoard[x][y] = 1;
    if(board[x][y] == '@')
    {
        *active = 0;
        printf("\nYou're Dead! \nA buffalo jumped on your head! G4M3 0V3R!");
    }
}

void cMark(int x, int y, int **checkBoard)
{
    checkBoard[x][y] = 2;
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