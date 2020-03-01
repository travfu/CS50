// Pset1 - cash
// A program that prompts users for a value in dollars
// and returns a value that represents the minimal amount of coins this dollar value can be reached

#include <math.h> // round()
#include <cs50.h> // get_float
#include <stdio.h>

int main(void)
{
    // 1 - prompt user for value in dollars (d)
    float d;
    do
    {
        d = get_float("Change owed: ");
    }
    while (d < 0); // reprompt if value is negative

    // 2 - convert dollars to cents (c)
    int c = round(d * 100);

    // 3 - algorithm to determine least amount of coins

    // 3 - 1 25c quarter (q)
    int q = c / 25;
    int x = c - q * 25;

    // 3 - 2 10c dime (m)
    int m = (x / 10);
    x = x - m * 10;

    // 3 - 3 5c nickel (n)
    int n = (x / 5);
    x = x - n * 5;

    // 3 - 4 1c penny (p)
    int p = (x / 1);
    x = x - p;

    // 4 total (t) the number of each coin and print this value as minimal number of coins
    int t = q + m + n + p;
    printf("%i\n", t);
}
