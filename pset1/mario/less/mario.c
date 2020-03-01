// pset1: Mario (less)
// create a program, utilising printf(), that prints out a half-pyramid of a user-defined height, displayed as #
// e.g.
//     #
//    ##
//   ###
//  ####
// #####

// Specifications: integer between 1 and 8

#include <cs50.h> // for get_int()
#include <stdio.h>

int main(void)
{
    // do-while loop
    int h;
    do
    {
        // prompt once for integer h
        h = get_int("Height: ");
    }
    // reprompt if h is not between 1 and 8
    while (h < 1 || h > 8);

    // define y, which will be used, as a separate decreasing counter with an initial value h, to determine number of spaces
    int y = h;

    // print pyramid using for loop
    // define number of lines (pyramid height) based on h
    for (int i = 0; i < h; i++)
    {
        // print spaces
        for (int a = 1; a < y; a++)
        {
            printf(" ");
        }
        //after exiting loop (or effectively, one pyramid row), decrease value of y by 1
        y--;

        // print hashtags
        for (int b = 0; b < i + 1; b++)
        {
            printf("#");
        }

        // next line
        printf("\n");
    }

}