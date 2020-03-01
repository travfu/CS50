// Pset1 - credit
// design a program to prompt user for a credit card number then report whether it is American Express, Visa, Mastercard, or invalid.

// 1 - prompt user
// 2 - checksum
// 3 - count number of digits
// 4 - if and else conditions to filter for VISA, AMEX, or MASTERCARD

#include <cs50.h> // get_long_long
#include <stdio.h>

int main(void)
{
    // 1.0 Prompt user for a credit card number (cc)
    long long cc = get_long_long("Number: ");

    // 2.0 Checksum
    // 2.1 Define new variables
    long long cc1 = cc;                      // copy cc so it remains unchanged as cc1 will be updated
    int checksum = 0;                        // starting value of checksum

    // 2.2 while() loop to perform checksum arithmetic
    while (cc1 > 0)
    {
        int a = cc1 % 10;                    // get first digit (to be added to checksum, +checksum)
        cc1 = cc1 / 10;

        int b = cc1 % 10 * 2;                // get second-to-last digit and mulitply by 2 (may result in 2 digits)
        int c = b % 10;                      // get last digit of a (+checksum)
        int d = b / 10 % 10;                 // get first digit of a (+checksum)

        checksum = checksum + a + c + d;
        cc1 = cc1 / 10;

    }

    // 3.0 Count number of digits using while loop
    long long cc2 = cc;                      // same principle as cc1
    int digit = 0;                           // digit counter

    while (cc2 > 0)
    {
        cc2 = cc2 / 10;
        digit++;
    }

    // 4.0 VISA, AMEX, or MASTERCARD?
    if (checksum % 10 == 0)                  // Select for numbers that pass checksum
    {
        // Select for numbers with digits 13, 15, OR 16 then sort further
        if (digit == 13)                     // Select for 13-digit number
        {
            if (cc / 1000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digit == 15)               // Select for 15-digit number
        {
            if (cc / 10000000000000 == 34 || cc / 10000000000000 == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (digit == 16)              // Select for 16-digit number
        {
            int mc = cc / 100000000000000;
            if (mc == 51 || mc == 52 || mc == 53 || mc == 54 || mc == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (cc / 1000000000000000 == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");          // If number is not 13, 15, or 16 digits-long, INVALID
        }
    }
    else
    {
        printf("INVALID\n");             // If it doesn't pass checksum, INVALID
    }

}