// Pset2: Caesar
// Implement program that encrypts messages using Caesar's ciper
// idea is that the ciper (k), a non-negative integer, added to a message will return the cipher text

#include <cs50.h>           // get_string
#include <stdio.h>
#include <stdlib.h>         // atoi
#include <string.h>         // strlen()
#include <ctype.h>          // isalpha, islower, isupper

#define index_upper 65      // + to convert ASCII to indexed alphabet, - to conver indexed alphabet to ASCII
#define index_lower 97      // "        "
#define alpha_n 26          // number of alphabet letters

int main(int argc, string argv[])
{
    // if more than one command-line argument is typed, print error message and return main value of 1
    if (argc >= 3)
    {
        printf("error: please input a single secret key\n");
        return 1;
    }
    else if (argc < 2)
    {
        printf("error: please enter secret key\n");
        return 1;
    }
    else
    {
        // store user-input plaintext as string
        string txt = get_string("plaintext: ");

        // convert k from string to int for cipher algorithm
        int k = atoi(argv[1]);

        // for loop to scan for alphabetical characters and replace with ciphered text
        for (int i = 0; i < strlen(txt); i++)
        {
            char p = txt[i];
            if (isalpha(p))
            {
                if (isupper(p))
                {
                    // cipher algorithm + replace i-th position of text
                    txt[i] = (p + k - index_upper) % alpha_n + index_upper;
                }
                else if (islower(p))
                {
                    // cipher algorithm + replace i-th position of text
                    txt[i] = (p + k - index_lower) % alpha_n + index_lower;
                }
            }
        }
        // print ciphertext output
        printf("ciphertext: %s\n", txt);

        return 0;

    }
}

