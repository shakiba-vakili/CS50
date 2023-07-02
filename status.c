#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Missing command-line srgument\n");
    }
    else
    {
        printf("hello, %s\n", argv[1]);
    }

    /*
    make status
    ./status
    Missing command-line srgument
    ./status shv
    hello, shv
    */
}