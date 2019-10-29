#include <cs50.h>
#include <stdio.h>

int printPillar1(int i);
int printPillar2(int i);
int printGap(int i);
int printNudge(int i);

int main(void)
{
    int height = get_int("How tall do you want your Pyramid?\n");
    //printf("Height: %i\n", height);
    if (height < 1 || height > 8)
    {
        main();
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            printNudge(height - i);
            printPillar1(i);
            printGap(i);
            printPillar2(i);
        }
    }
}

int printGap(int i)
{
    printf("  ");
    return i;
}

int printNudge(int i)
{
    for (int j = i; j > 0; j--)
    {
        if (j > 1)
        {
            printf(" ");
        }
    }
    return i;
}

int printPillar1(int i)
{
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
    return i;
}

int printPillar2(int i)
{
    for (int j = 0; j <= i; j++)
    {
        printf("#");
    }
    printf("\n");
    return i;
}
