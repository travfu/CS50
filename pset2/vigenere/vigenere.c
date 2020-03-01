// Pset2: Vigenere
// Implement program that encrypts messages using Vigenère’s cipher

#include <cs50.h>           // get_string
#include <stdio.h>
#include <string.h>         // strlen()
#include <ctype.h>          // isalpha, islower, isupper

int iskeyalpha();

int main(int argc, string argv[])
{
    // 1.1 Select for valid alphabetical cipher key and only 1 command-line argument
    if (argc == 2 && iskeyalpha(argv[1], strlen(argv[1])))
    {
        // 2.0 Prompt user for plaintext
        string txt = get_string("plaintext: ");

        // 3.0 Vigenere cipher algorithm
        // 3.1 convert key to indexed numbers and store in an array
        string key = argv[1];
        int key_len = strlen(key);
        int k[key_len];

        for (int i = 0; i < key_len; i++)
        {
            if (isupper(key[i]))
            {
                k[i] = key[i] % 65;
            }
            if (islower(key[i]))
            {
                k[i] = key[i] % 97;
            }
        }
        // 3.2 initiate for loop to replace plaintext with ciphertext
        for (int i = 0, j = 0; i < strlen(txt); i++)
        {
            // 3.3 select for alphabetical letters
            if (isalpha(txt[i]))
            {
                if (isupper(txt[i]))
                {
                    // 3.4a replace uppercase plaintext with uppercase ciphertext
                    txt[i] = (txt[i] + k[j % key_len] - 65) % 26 + 65;
                    j++;
                }
                else if (islower(txt[i]))
                {
                    // 3.4b replace lowercase plaintext with lowercase ciphertext
                    txt[i] = (txt[i] + k[j % key_len] - 97) % 26 + 97;
                    j++;
                }
            }
        }
        // 4.0 print ciphertext
        printf("ciphertext: %s\n", txt);
        return 0;
    }

    // 1.2 return error if cipher key input is invalid
    else
    {
        printf("error: enter an alphabetical cipher key\n");
        return 1;
    }
}

// function to check if all characters within cipher key are alphabetical
// Abcd passes check
// Ab23 fails check
int iskeyalpha(string a, int b)            // input a: cipher key (argv[1]) b: strlen(cipher key)
{
    int j = 0;
    for (int i = 0; i < b; i++)            // for loop to count number of alphabet letters and add to tally, j
    {
        if (isalpha(a[i]))
        {
            j++;
        }
    }
    if (j == b)                            // if key contains only alphabetical characters, it is valid - return 1
    {
        return 1;
    }
    else                                   // if key contains non-alphabetical characters, it is invalid - return 0
    {
        return 0;
    }
}