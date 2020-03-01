// pset1: Mario
// create a program, utilising printf(), that prints out a pyramid of a user-defined height, displayed as #
// e.g.
//     #  #
//    ##  ##
//   ###  ###
//  ####  ####
// #####  #####

// Specifications: accepts integer between 0 and 8

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
    // reprompt if h is not between 0 and 8
    while (h < 1 || h > 8);

    // define y, which will be used, as a separate decreasing counter with an initial value h, to determine number of spaces
    int y = h;

    // print pyramid using for loop
    // define number of lines (pyramid height) based on h
    for (int i = 0; i < h; i++)
    {
        // this block of code codes for one row of the pyramid
        // print spaces
        for (int a = 1; a < y; a++)
        {
            printf(" ");
        }
        //after exiting loop (or almost effectively, one pyramid row), decrease value of y by 1
        y--;

        // print hashtags (left)
        for (int b = 0; b < i + 1; b++)
        {
            printf("#");
        }

        // 2 space gap
        printf("  ");

        // print hashtag (right)
        for (int c = 0; c < i + 1; c++)
        {
            printf("#");
        }

        // next line
        printf("\n");
    }

}