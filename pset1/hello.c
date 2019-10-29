#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string name = get_string("What's your name: ");
    if(strlen(name) == 0)
    {
        printf("Hello, World!\n");
    }
    else
    {
        printf("Hello, %s\n", name);
    }

}
