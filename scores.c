#include <cs50.h>
#include <stdio.h>

//////////////////// With Function
const int N = 3;
float average(int array[]);

int main(void)
{

    int score1 = 72;
    int score2 = 73;
    int score3 = 33;

    int
    printf("Average: %i\n", (score1 + score2 + score3) / 3);
    59

    float
    printf("Average: %f\n", (score1 + score2 + score3) / 3.0);
    59.3333

    float way two
    printf("Average: %f\n", (score1 + score2 + score3) / (float) 3);
    59.3333


    //////////////////// Array


    int scores[3];
    scores[0] = 72;
    scores[1] = 73;
    scores[3] = 33;

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);



    //////////////////// Dynamic Array


    int scores[3];
    scores[0] = get_int("Score: ");
    scores[1] = get_int("Score: ");
    scores[2] = get_int("Score: ");

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);



    //////////////////// Loop Array


    int scores[3];
    for( int i = 0; i < 3; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", (scores[0] + scores[1] + scores[2]) / 3.0);


    //////////////////// With Function
    int scores[N];
    for (int i = 0; i < N; i++)
    {
        scores[i] = get_int("Score: ");
    }

    printf("Average: %f\n", average(scores));
}

float average(int array[])
{
    int sum = 0;
    for (int i = 0; i < N; i++)
    {
        sum += array[i];
    }
    return sum / (float) N;
}