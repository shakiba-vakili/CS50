#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO
    string message = get_string("Message: ");
    // test: H


    // conver to ascii
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        char c = message[i];
        // text H = 72
        // conver to binary
        // H = 0 and 1
        // now H = 00010010 => should H = 01001000
        for (int j = BITS_IN_BYTE -1; j >= 0; j--)
        {
            // >> = shifting to right
            int bit = (c >> j) & 1;

        print_bulb(bit);
        }

    printf("\n");
    }

}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
