#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    // use strlen in string.h

 string s = get_string("Befor: ");
    printf("After: ");
    for (int i = 0; i < strlen(s); i++){

        if (s[i] >= 'a' && s[i] <= 'z')
        {
            printf("%C", s[i] - 32);
        }
        else
        {
            printf("%C", s[i]);
        }
    }
    printf("\n");



// use lower case in ctype.h

string s = get_string("Befor: ");
    printf("After: ");
    for (int i = 0; i < strlen(s); i++){

        if (islower(s[i]))
        {
            printf("%C", toupper(s[i]));
        }
        else
        {
            printf("%C", s[i]);
        }
    }
    printf("\n");



// better design
string s = get_string("Befor: ");
    printf("After: ");
    for (int i = 0, n = strlen(s); i < n; i++){
    printf("%C", toupper(s[i]));
    }
    printf("\n");

}