#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

bool balanced (int array[], int n)
{
    int sum1 = 0;
    int sum2 = 0;


    if( n % 2 == 0)
    {
        for(int i = 0; i < (n/2) ; i++)
        {
            sum1 = sum1 + array[i];
        }
        for(int i = (n/2); i < (n); i++ )
        {
            sum2 = sum2 + array[i];
        }
        if(sum1 == sum2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        for(int i = 0; i < ((n - 1) /2) ; i++)
        {
             sum1 = sum1 + array[i];
        }
        for(int i = (((n - 1) /2) + 1) ; i < n  ; i++)
        {
            sum2 = sum2 + array[i];
        }
        if(sum1 == sum2)
        {
            return true;
        }
        else
        {
            return false;
        }

    }
}

int main(void)
{
    int b[5] = {1, 3, 4, 2, 2};
    int length = 5;
    if (balanced (b, length))
    {
        printf("cool\n");
    }
    else
    {
        printf("lame\n");
    }
    return 0;
}


