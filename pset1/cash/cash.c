#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    //variable to store user's cash to change
    float Original = 0

    //values of coins
    float quarter = 25
    float dime = 10
    float nickel = 5
    float penny = 1

    //counter stores number of coins
    int counter = 0;

    //prompt user for cash
    printf("Change owed:\n");

    //checks if change is greater than 0
    do
    {
        Original = get_float();
        if (Original < 0)
        {
            printf("Try again \n");
        }
    }
    while (Original < 0);

    //converts change to whole number
    float C = Orignial * 100;
    Conv = int(round(changeConv))


//breaks amount into different coins using minimum possible
    do
    {
        if (changeConv >= 25)
        {
            changeConv = changeConv - quarter;
            counter = counter + 1;

        }
        else if (changeConv < 25 & changeConv >= 10 )
        {
            changeConv = changeConv - dime;
            counter = counter + 1;
        }
        else if (changeConv < 10 & changeConv >= 5 )
        {
            changeConv = changeConv - nickel;
            counter = counter + 1;
        }
        else if (changeConv < 5 & changeConv > 0 )
        {
            changeConv = changeConv - penny;
            counter = counter + 1;
        }
    }
    while (changeConv != 0 );

    printf("%i\n", counter);

}




