#define _XOPEN_SOURCE // crypt function dependancies
#include <unistd.h> // crypt function dependancies#include <cs50.h>
#include <crypt.h>

#include <stdio.h>
#include <cs50.h>
#include <string.h>

bool crack(char *user_input, char *guess, char *salt);

int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Invalid Arguements\n");
        return 1;
    }
    //printf("Success\n");
    //Storing the inputted Hash for later use within the program
    char *user_input = argv[1];

    //Storing the Alphabet to loop and check the passwords
    //Changed the Alphabet using data provided by:
    // https://en.wikipedia.org/wiki/Letter_frequency
    // This sped up the
    //char alpha[] = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    char alpha[] = "\0eEaArRiIoOtTnNsSlLcCuUdDpPmMhHgGbBfFyYwWkKvVxXzZjJqQ";
    //Storing the Salt at the beginning of the Hash for use in Crypt()
    char salt[2];
    //printf("salt:");
    for (int i = 0; i < 2; i++)
    {
        salt[i] = user_input[i];
        //printf("%c", salt[i]);
    }
    printf("\n");


    //Gets the length of the alphabet char array
    int alpha_len = (sizeof alpha / sizeof alpha[0]) - 1;
    //printf("%i\n", alpha_len);

    char guess[6] = "\0\0\0\0\0\0";
    int counter = 0;
    for (int fifth = 0; fifth < alpha_len; fifth++)
    {
        for (int fourth = 0; fourth < alpha_len; fourth++)
        {
            for (int third = 0; third < alpha_len; third++)
            {
                for (int second = 0; second < alpha_len; second++)
                {
                    for (int first = 1; first < alpha_len; first++)
                    {
                        guess[0] = alpha[first];  //1
                        guess[1] = alpha[second]; //2
                        guess[2] = alpha[third];  //3
                        guess[3] = alpha[fourth]; //4
                        guess[4] = alpha[fifth];  //5
                        counter++;
                        if (crack(user_input, guess, salt))
                        {
                            printf("Password is: %s\n", guess);
                            //printf("Iterations: %i\n", counter);
                            return 0;
                        }
                    }
                }
            }
        }
    }

    printf("Password not found.\n");
    return 2;
}

bool crack(char *user_input, char *guess, char *salt)
{
    char *encrypted_guess = crypt(guess, salt);
    //printf("%s\n", guess);
    if (strcmp(encrypted_guess, user_input) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
