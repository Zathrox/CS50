#include <stdio.h>
#include <cs50.h>

int collatz(int n);
int counter = 0;

int main(void)
{
    int n = get_int("Please provide a number: ");

    printf("Steps to get to 1: %i\n", collatz(n));
}

int collatz(int n)
{

    if (n == 1)
    {
        return counter;
    }
    else if (n % 2 == 0)
    {
        counter++;
        return collatz(n/2);
    }
    else
    {
        counter++;
        return collatz((3*n) + 1);
    }
}