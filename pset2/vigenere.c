#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define UPPERCASE 65
#define LOWERCASE 97
#define ALPHABET 26

char enciphering(char ciphertext, int key);
int shift(char c);

int main(int argc, string argv[])
{
    // Get the key from the user
    string cipher_key;
    if (argc != 2)
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: ./vigenere keyword\n");
            return 1;
        }
    }
    printf("Successful Keyword\n");
    //Once a successful keyword is passed, store in cipher_key
    cipher_key = argv[1];

    //Initializing a blank string for use within the program
    //Loops indefinately until text is inputted
    string ptxt;
    do
    {
        //Prompts the user for plaintext
        ptxt = get_string("plaintext: ");
    }
    while (strlen(ptxt) == 0);

    printf("ciphertext: ");

    //Stores the lenght of the key in a variable for later use
    int key_len = strlen(cipher_key);
    int key;
    for (int i = 0, j = 0; i < strlen(ptxt); i++)
    {
        //Checks if the the text is Alphabet or not and return O if it
        //isn't, effectively skipping it
        if (isalpha(ptxt[i]))
        {
            //If it is Alphabet, shift characters based on Vigenere Cipher
            //over the Modulo value, infinately looping the key over the
            //lenght of the plaintext
            key = shift(argv[1][j % key_len]);
            j++;
        }
        else
        {
            key = 0;
        }
        printf("%c", enciphering(ptxt[i], key));

    }
    printf("\n");
}

int shift(char c)
{
    //Takes Value C - Starting Value of Uppercase ASCII
    if (isupper(c))
    {
        return c - UPPERCASE;
    }
    //Takes Value C - Starting Value of Lowercase ASCII
    else
    {
        return c - LOWERCASE;
    }
}

char enciphering(char ptxt, int k)
{
    //c[i] = (p[i] + arg[i]) % 26
    //This checks if it is a Captial
    if (isupper(ptxt))
    {
        //Calculates the value + k and any remainder left
        return ((ptxt - UPPERCASE) + k) % ALPHABET + UPPERCASE;
    }
    else if (islower(ptxt))
    {
        return ((ptxt - LOWERCASE) + k) % ALPHABET + LOWERCASE;
    }
    else
    {
        return ptxt;
    }
}
