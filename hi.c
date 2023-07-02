#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
    string s = "HI!";
    string t = "BYE!";

    // whole string
    printf("%s\n", s);
    printf("%s\n", t);

    // first char of string
    printf("%s\n", s[0]);

    //if you use %i insted of %s answe is going to be integer


   // array in array
   string words[2];

   words[0] = "HI!";
   words[1] = "BYE!";

   printf("%c%c%c\n",words[0][0],words[0][1],words[0][2]);
   printf("%s\n",words[1]);


}