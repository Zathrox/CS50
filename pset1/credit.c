#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int count_digit(long long cc);
int get_starting_no(long long cc, int digits);
bool checkLuhn(long cc_number);

int main(void)
{
    //Repeats forever until an acceptable, positive number is entered
    long long cc_number;
    do
    {
        cc_number = get_long("Insert Credit Card Number: ");
    }
    while (cc_number <= 0);

    //Calls and intialises digits, which counts and stores the number of digits
    //provided by cc_number
    int digits = count_digit(cc_number);
    //Calls and initialises cardBegin, this gets the starting card number
    //provided by cc_number and checks with digits how much math too do
    int cardBegin = get_starting_no(cc_number, digits);
    //printf("Digits: %i\n", digits);
    //printf("Starting Number: %i\n", cardBegin);
    if (digits == 15)
    {
        if (cardBegin == 34 || cardBegin == 37)
        {
            //call AMEX CheckSum
            bool valid = checkLuhn(cc_number);
            if (valid)
            {
                printf("AMEX\n");
            }
            else
            {
                //call Invalid
                printf("INVALID\n");
            }

        }
        else
        {
            //call Invalid
            printf("INVALID\n");
        }

    }
    else if (digits == 13 || digits == 16)
    {
        if (digits == 16 && cardBegin / 10 == 4)
        {
            //call VISA CheckSum
            bool valid = checkLuhn(cc_number);
            if (valid)
            {
                printf("VISA\n");
            }
            else
            {
                //call Invalid
                printf("INVALID\n");
            }

        }
        else if (cardBegin == 4)
        {
            //call VISA CheckSum
            bool valid = checkLuhn(cc_number);
            if (valid)
            {
                printf("VISA\n");
            }
            else
            {
                //call Invalid
                printf("INVALID\n");
            }
        }
        else if (cardBegin == 51 || cardBegin == 52 || cardBegin == 53 || cardBegin == 54 || cardBegin == 55)
        {
            //call MASTERCARD CheckSum
            bool valid = checkLuhn(cc_number);
            if (valid)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                //call Invalid
                printf("INVALID\n");
            }

        }
        else
        {
            //call Invalid
            printf("INVALID\n");
        }

    }
    else
    {
        //call Invalid
        printf("INVALID\n");
    }
}

bool checkLuhn(long cc_number)
{

    int digit1 = (((cc_number % 100) / 10) * 2);
    int digit2 = (((cc_number % 10000) / 1000) * 2);
    int digit3 = (((cc_number % 1000000) / 100000) * 2);
    int digit4 = (((cc_number % 100000000) / 10000000) * 2);
    int digit5 = (((cc_number % 10000000000) / 1000000000) * 2);
    int digit6 = (((cc_number % 1000000000000) / 100000000000) * 2);
    int digit7 = (((cc_number % 100000000000000) / 10000000000000) * 2);
    int digit8 = (((cc_number % 10000000000000000) / 1000000000000000) * 2);

    //Adding all the products digits together as part of the CheckSum
    int checkSum = (digit1 / 10 + digit1 % 10);
    checkSum = (checkSum + digit2 / 10 + digit2 % 10);
    checkSum = (checkSum + digit3 / 10 + digit3 % 10);
    checkSum = (checkSum + (digit4 / 10 + digit4 % 10));
    checkSum = (checkSum + digit5 / 10 + digit5 % 10);
    checkSum = (checkSum + digit6 / 10 + digit6 % 10);
    checkSum = (checkSum + digit7 / 10 + digit7 % 10);
    checkSum = (checkSum + digit8 / 10 + digit8 % 10);

    int digit9 = (cc_number % 10);
    int digit10 = ((cc_number % 1000) / 100);
    int digit11 = ((cc_number % 100000) / 10000);
    int digit12 = ((cc_number % 10000000) / 1000000);
    int digit13 = ((cc_number % 1000000000) / 100000000);
    int digit14 = ((cc_number % 100000000000) / 10000000000);
    int digit15 = ((cc_number % 10000000000000) / 1000000000000);
    int digit16 = ((cc_number % 1000000000000000) / 100000000000000);
    int total = (digit9 + digit10 + digit11 + digit12 + digit13
                 + digit14 + digit15 + digit16 + checkSum);
    total = total % 10;
    if (total == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int count_digit(long long cc)
{
    int i = 0;
    while (cc > 0)
    {
        cc = cc / 10;
        i++;
    }
    return (i);
}

int get_starting_no(long long cc, int digits)
{
    //digits - 2
    int starting_no;
    if (digits == 15)
    {
        starting_no = (cc / 10000000000000);
    }
    else if (digits == 16)
    {
        starting_no = (cc / 100000000000000);
    }
    else if (digits == 13)
    {
        starting_no = (cc / 1000000000000);
    }
    else
    {
        starting_no = 0;
    }
    return (starting_no);
}