#include <stdio.h>
#include <stdlib.h>

void fStart(int x, int y, char **board, int **checkBoard) // initializing every element of board & checkBoard with 0
{
    int i, j;

    // Fill by default the number 0 to every element of the table
    for(i = 0; i < x;i++)
    {
        for(j = 0;j < y;j++)
        {
            board[i][j] = '0';
            checkBoard[i][j] = 0;
        }
    }
}

void fBuffalo(int x, int y, int dif, char **board, int *countb) // initializing buffaloes
{
    int i, k, l;
    float chanceBuff, nBuffaloes;
    switch(dif)
    {
        case 1:
        {
            chanceBuff = (float)1/8;
            break;
        }
        case 2:
        {
            chanceBuff = (float)1/7;
            break;
        }
        case 3:
        {
            chanceBuff = (float)1/6;
            break;
        }
        case 4:
        {
            chanceBuff = (float)1/5;
            break;
        }
    }
    nBuffaloes = (x * y) * chanceBuff; // Getting buffalo crowd
    *countb = (int) nBuffaloes;

    // Putting buffaloes in random elements of the table
    for(i = 0;i < *countb;i++)
    {
        do
        {
            k = rand() % x;
            l = rand() % y;
        }while(board[k][l] == '@');
        board[k][l] = '@';
    }
}

void fBells(int x, int y, char **board)
{
    int i,j,count,k,l;

    for(i = 0;i < x;i++)
    {
        for(j = 0;j < y;j++)
        {
            count = 0;
            if(board[i][j] != '@')
            {
                for(k = i - 1;k <= i + 1;k++)
                {
                    for(l = j - 1;l <= j + 1;l++)
                    {
                        if((k >= 0 && k < x) && (l >= 0 && l < y))
                        {
                            if(board[k][l] == '@')
                            {
                                count++;
                            }
                        }
                    }
                }
                board[i][j] += count;
                if(board[i][j]=='0')
                {
                    board[i][j]='.';
                }
            }
        }
    }
}

void printBoard(int x, int y, char **board, int **checkBoard)
{
    int i,j,k,count = 0;

    printf("\n    ");

    for(i = 0;i < x;i++)
    {
        if(i == 0)
        {
            for(k = 0;k < y;k++)
            {
                printf("%2d ", k + 1);
            }
            printf("\n");
            for(k = 0;k < y * 2 + (y * 2);k++)
            {
                printf("-");
            }
        }

        printf("\n");

        for(j = 0;j < y;j++)
        {
           if(j == 0)
           {
               printf("%2d | ", i + 1);
           }
           if(checkBoard[i][j] == 0)
           {
               printf("#  ");
           }
           else if(checkBoard[i][j] == 1)
           {
                printf("%c  ",board[i][j]);
           }
           else
           {
               printf("*  ");
           }
        }
        count++;
        printf("\n");
    }
}

void calcXY(int *x, int *y,char *prefix) // getting prefix values for xy and converts them to int
{
    if(prefix[3] == ',')
    {
        *x = ((int)prefix[2] - '0');
        if(prefix[5] == '\0')
        {
            *y = ((int)prefix[4] - '0');
        }
        else if(prefix[6] == '\0')
        {
            *y = (((int)prefix[4] - '0') * 10) + ((int)prefix[5] - '0');
        }
    }
    else if(prefix[4] == ',')
    {
        *x = (((int)prefix[2] - '0') * 10) + ((int)prefix[3] - '0');
        if(prefix[6] == '\0')
        {
            *y = ((int)prefix[5] - '0');
        }
        else if(prefix[7] == '\0')
        {
            *y = (((int)prefix[5] - '0') * 10) + ((int)prefix[6] - '0');
        }
    }
    else
    {
        printf("\nSyntax error, please follow --> ( prefix x,y ) or ( prefix )");
    }
    (*x)--;
    (*y)--;
}

int checkWin(int x, int y, char **board, int **checkBoard) // if opened == all - buffalos then player wins
{
    int i,j,count = 0,countb = 0;


    for(i = 0;i < x;i++)
    {
        for(j = 0;j < y;j++)
        {
            if(board[i][j] == '@')
            {
                countb++;
            }
            if(checkBoard[i][j] == 1)
            {
                count++;
            }
        }
    }
    if(count == (x * y - countb))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}