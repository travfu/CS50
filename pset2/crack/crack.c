// Pset 2: Crack
// Implement a program that cracks passwords encrypted using a "one-way hash function"

#define _XOPEN_SOURCE      // crypt()

#include <cs50.h>          // string
#include <stdio.h>
#include <string.h>
#include <unistd.h>        // crypt()

int main(int argc, string argv[])
{
    // 1.0a Select for valid hashed password input
    if (argc == 2)
    {
        // 2.0 Extract salt from hash input
        string hash = argv[1];
        char b[3] = {hash[0], hash[1], '\0'};  // extract first two characters from hash input and store in array
        string salt = b;                       // combine first two characters from hash input into a string

        // 3.0 generate random plaintext to feed into crypt()
        // 3.1 declare alphabet and empty array to store random plaintext
        char alphabet[] = {"\0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
        char p[6] = {'\0', '\0', '\0', '\0', '\0', '\0'};

        // 3.2 counter for 5th letter
        for (int letter_five = 0; letter_five < 53; letter_five++)  // 52 is the length of variable alphabet including the initial '\0'
        {
            // 3.3 counter for 4th letter
            for (int letter_four = 0; letter_four < 53; letter_four++)
            {
                // 3.4 counter for 3rd letter
                for (int letter_three = 0; letter_three < 53; letter_three++)
                {
                    // 3.5 counter for 2nd letter
                    for (int letter_two = 0; letter_two < 53; letter_two++)
                    {
                        // 3.6 counter for 1st letter
                        for (int letter_one = 1; letter_one < 53; letter_one++)
                        {
                            p[0] = alphabet[letter_one];
                            p[1] = alphabet[letter_two];
                            p[2] = alphabet[letter_three];
                            p[3] = alphabet[letter_four];
                            p[4] = alphabet[letter_five];

                            if (strcmp(hash, crypt(p, salt)) == 0)
                            {
                                printf("%s\n", p);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        printf("hash: %s\n", hash);
        return 0;
    }
    // 1.0b If invalid input, print error message and return 1
    else
    {
        printf("error: input valid hashed password\n");
        return 1;
    }
}