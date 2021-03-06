#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "func.h"
#include "commands.h"
#define minxy 4

int main()
{
    srand(time(NULL));
    int x, y, dif, i, j, active = 1, level = 1, countb, countmarked = 0, buffnumber, ux, uy, rx, ry, win = 0,firstbuff = 0, hx = -1,hy = -1, isWis = 0;
    char prefix[8];
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

    int maxlevelx = x + 3, maxlevely = y + 3;

    printf("\nGreat! The table will be %dx%d ! There are 3 levels, are you good enough to pass?\n", x, y);
    printf("To get the available commands please type 'c'\n");
    printf("\nNow Enter the number of the difficulty you want to play : ");
    printf("\n1) Beginner\n2) Intermediate\n3) Expert\n4) Professional\nDifficulty : ");
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

    for(i = 0; i < x;i++)
    {
        for(j = 0;j < y;j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    while(active)
    {
        buffnumber = countb - countmarked; // buff number on print

        printBoard(x, y, board, checkBoard);
        printf("\nLevel : %d", level);
        printf("\nDifficulty : ");
        switch(dif)
        {
            case 1:
            {
                printf("Beginner");
                break;
            }
            case 2:
            {
                printf("Intermediate");
                break;
            }
            case 3:
            {
                printf("Expert");
                break;
            }
            case 4:
            {
                printf("Professional");
                break;
            }
        }
        printf("\nUncovered buffaloes : %d", buffnumber);
        if(isWis == 1)
        {
            printf("\nThe best place to stand is %d, %d", rx, ry);
            isWis = 0;
        }
        if(hx != -1 && hy != -1)
        {
            printf("\nTry to stand at %d,%d", hx, hy);
            hx = -1;
            hy = -1;
        }
        printf("\nMake your move : ");
        scanf(" %[^\n]s", prefix); // prefix [0] == cmd, prefix[2] == x, prefix[4] == y
        
        if(prefix[0] == 's' || prefix[0] == 'S')
        {
            calcXY(&ux,&uy,prefix);
            if(board[ux][uy] == '@' && firstbuff == 0)
            {
                firstbuff++;
            }
            while(board[ux][uy] == '@' && firstbuff == 1) // check if first is buffalo
            {
                fStart(x, y, board, checkBoard);
                fBuffalo(x, y, dif, board, &countb);
                fBells(x, y, board);
            }
            if(checkBoard[ux][uy] == 0)
            {
                if(board[ux][uy] == '.')
                {
                    floodFill(ux,uy,x,y,board,checkBoard);
                }
                else
                {
                    cShow(ux,uy,board,checkBoard,&active);
                }
                if(firstbuff < 2)
                {
                    firstbuff++;
                }
                else
                {
                    firstbuff = 0;
                }
            }
            else
            {
                printf("\n%d,%d is already opened", ux+1,uy+1);
            }
        }
        else if(prefix[0] == 'b' || prefix[0] == 'B')
        {
            calcXY(&ux,&uy,prefix);
            cMark(ux,uy,checkBoard);
            countmarked++;
        }
        else if(prefix[0] == 'x' || prefix[0] == 'X')
        {
            cExit(&active);
        }
        else if(prefix[0] == 'h' || prefix[0] == 'H')
        {
            cHelp(x,y,&hx,&hy,board,checkBoard);
        }
        else if(prefix[0] == 'w' || prefix[0] == 'W')
        {
            cWisdom(x, y, board, checkBoard, &rx, &ry);
            isWis = 1;
        }
        else if(prefix[0] == 'c' || prefix[0] == 'C')
        {
            printf("\nAvailable commands : \n1) 's' to open coordinates\n2) 'b' to mark buffaloes\n3) 'x' to exit the game\n4) 'h' to get coordinates without buffalo\n5) 'w' to get the BEST coordinates");
        }
        else
        {
            printf("\n\nThere isn't a command starting with '%c'\n\n", prefix[0]);
        }

        win = checkWin(x, y, board, checkBoard);

        if(win == 1)
        {
            if(x < maxlevelx && y < maxlevely)
            {
                printf("\n\n\nCongratulations!! You passed the level! Are you ready for a harder one?");

                for(i = 0; i < x; i++)
                {
                    free(board[i]);
                    free(checkBoard[i]);
                }
                free(board);
                free(checkBoard);

                level++;
                x++;
                y++;
                
                board = (char **) malloc (x * sizeof(char *));
                checkBoard = (int **) malloc (x * sizeof(int *));

                for(i = 0; i < x; i++)
                {
                    board[i] = (char *) malloc (y * sizeof(char));
                    checkBoard[i] = (int *) malloc (y * sizeof(int));
                }

                if(board == NULL || checkBoard == NULL)                     
                {
                    printf("Error! memory not allocated.");
                    exit(0);
                }
            
                fStart(x, y, board, checkBoard);
                fBuffalo(x, y, dif, board, &countb);
                fBells(x, y, board);
            }
            else
            {
                active = 0;
                printf("\n\n\nGame over! you finished the max level.");
            }
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
    for(i = 0; i < x; i++)
    {
        free(board[i]);
        free(checkBoard[i]);
    }
    free(board);
    free(checkBoard);

    return 0;
}
