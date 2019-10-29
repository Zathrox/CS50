#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char encryption(char ptext, int k);

int main(int argc, string argv[])
{
    // Checks that exactly two arguements are inputted
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //Iterates over the commandline arguement
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        //Checking if it is a digit or alphabet character
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 2;
        }
    }

    //Converts the string into an INT
    int k = atoi(argv[1]);
    // check if the integer is non-negative
    if (k < 0)
    {
        printf("Usage: ./caesar key\n");
        return 3;
    }

    //Prompts the user for plaintext
    string ptxt = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0, n = strlen(ptxt); i < n; i++)
    {
        printf("%c", encryption(ptxt[i], k));
    }
    printf("\n");

}

char encryption(char ptxt, int k)
{
    //c[i] = (p[i] + arg) % 26
    //This checks if it is a Captial
    if (isupper(ptxt))
    {
        return ((ptxt - 65) + k) % 26 + 65;
    }
    else if (islower(ptxt))
    {
        return ((ptxt - 97) + k) % 26 + 97;
    }
    else
    {
        return ptxt;
    }
}
