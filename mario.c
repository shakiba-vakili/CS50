#include <cs50.h>
#include <stdio.h>

int main(void)
{
int Height;
    do {
       Height = get_int("Height: ");
    }
    while (Height < 1|| Height > 8);
    /*for (int i = 1; i <= Height; i++)
    {
       for (int j = 1; j <= i;j++)
       {
         printf("#");
       }
      printf("\n");
    }*/
  for (int i = 1; i <= Height; i++)
    {
       for (int j = 1; j <= Height;j++)
       {
         if (j <= Height - i)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }       }

      printf("\n");
    }

}