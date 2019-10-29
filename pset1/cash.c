#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;
    float f;
    int coins = 0;

    //Sets a loop to continuiously check for a valid float
    do
    {
        f = get_float("Changed owed: ");
    }
    while (f <= 0);

    //Rounds up and converts "dollars" into "cents"
    int cents = round(f * 100);
    while (cents >= quarter)
    {
        coins += cents / quarter;
        cents = (cents % quarter);
    }
    while (cents >= dime)
    {
        coins += cents / dime;
        cents = (cents % dime);
    }

    while (cents >= nickel)
    {
        coins += cents / nickel;
        cents = (cents % nickel);
    }

    while (cents >= penny)
    {
        coins += cents / penny;
        cents = (cents % penny);
    }
    printf("%i\n", coins);

}