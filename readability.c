#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int letter = count_letters(text);
    int word = count_words(text);
    int sentence = count_sentences(text);

    // average
    float l = ((float)letter / (float)word)*100;
    float s = ((float)sentence / (float)word)*100;


    // result
    int grade =  round(0.0588 * l - 0.296 * s - 15.8);
    if (grade >= 16)
    {
         printf("Grade 16+\n");
    } else if (grade < 1)
    {
         printf("Before Grade 1\n");
    } else
    {
    printf("Grade %i\n", grade);
    // printf("Grade %i %f %f %i %i %i\n", grade, l, s, letter, word,sentence);
    }

}
// letter
    int count_letters(string text)
    {
        int letter = 0;
        for (int i = 0, len=strlen(text); i < len; i++)
        {
            if (isalpha(text[i]))
            {
                letter++;
            }
        }
            return letter;


    }
    // word
    int count_words(string text)
    {
      int word = 1;
      for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            word++;
        }
    }

    return word;
    }

    //sentence
 int count_sentences(string text)
{
        int sentence = 0;
        //  \0 = null end of the sentence

        for (int i = 0; text[i] != '\0'; i++)
        {
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                 sentence++;
            }
        }

    return sentence;
}