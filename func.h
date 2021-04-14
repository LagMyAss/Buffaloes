#include <stdio.h>
#include <stdlib.h>

void fStart(int x, int y, char **board) // initializing every element with 0
{
    int i, j;

    // Fill by default the number 0 to every element of the table
    for(i = 0; i < x;i++)
    {
        for(j = 0;j < y;j++)
        {
            board[i][j] = '0';
        }
    }
}

void fBuffalo(int x, int y, int dif, char **board) // initializing buffaloes
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

    // Putting buffaloes in random elements of the table
    for(i = 0;i < (int) nBuffaloes;i++)
    {
        do
        {
            k = rand() % x;
            l = rand() % y;
        }while(board[k][l] == '*');
        board[k][l] = '*';
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
            if(board[i][j] != '*')
            {
                for(k = i - 1;k <= i + 1;k++)
                {
                    for(l = j - 1;l <= j + 1;l++)
                    {
                        if((k >= 0 && k < x) && (l >= 0 && l < y))
                        {
                            if(board[k][l] == '*')
                            {
                                count++;
                            }
                        }
                    }
                }
                board[i][j] += count;
            }
        }
    }
}