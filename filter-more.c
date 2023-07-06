#include "helpers.h"
#include <cs50.h>
#include <stdio.h>
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // each pixel
    for (int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            int avg = round((image[row][col].rgbtRed + image[row][col].rgbtGreen + image[row][col].rgbtBlue) / 3.0);
            image[row][col].rgbtBlue = image[row][col].rgbtGreen = image[row][col].rgbtRed = avg;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // pixel swap in row => row = width / 2
        for(int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width-j-1];
            image[i][width - j - 1] = temp;
        }


    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // variable
    float counter;
    double totalR, totalG, totalB;
    RGBTRIPLE temp[height][width];


    for(int row=0; row < height; row++)
    {
        for(int column=0; column<width; column++)
        {
            totalR = 0;
            totalG = 0;
            totalB = 0;
            // how many red, green , blue exist?
            counter = 0;
            // each pixel => neighbor
             for (int neighborRow=-1; neighborRow < 2; neighborRow++)
            {
                // row=-1 to find first row in 3x3 grid
                for (int neighborCol =-1; neighborCol < 2; neighborCol++)
                {
                    //       col-1   j  col+1
                    // row+1 | -1 |    | +1 |
                    // i     |    |  0 |    |
                    // row-1 |    |    |    |

                    // Check for exist cell and skip if it isn't
                    int a = row + neighborRow;
                    int b = column + neighborCol;
                    if (a < height && b < width && a >= 0 && b>=0)
                    {
                    totalR += image[a][b].rgbtRed;
                    totalG += image[a][b].rgbtGreen;
                    totalB += image[a][b].rgbtBlue;
                    counter++;
                   }
                }
           }
                    totalR = round(totalR / counter);
                    totalG = round(totalG / counter);
                    totalB = round(totalB / counter);
                    // Add the blur effect to the original image
                    temp[row][column].rgbtRed = totalR;
                    temp[row][column].rgbtGreen = totalG;
                    temp[row][column].rgbtBlue = totalB;
        }
    }


    for(int i=0; i < height; i++)
        {
            for(int j=0; j<width; j++)
            {
                image[i][j] = temp[i][j];
            }
        }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for(int i =0; i < height;i++)
    {
        for(int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // we need gx and gy
    // | |0| |      | | | |      |-1|0 |+1|      |-1|-2|-1|
    // | |0| |  or  |0|0|0|  Gx  |-2|0 |+2|  Gy  |0 |0 |0 | => G = |Gx| + |Gy|
    // | |0| |      | | | |      |-1|0 |+1|      |+1|+2|+1|
    int gX[3][3] = {{-1,0,1},{-2,0,2}, {-1,0,1}};
    int gY[3][3] = {{-1,-2,-1},{0,0,0}, {1,2,1}};



    for(int i =0; i < height;i++)
    {
        for(int j = 0; j < width; j++)
        {
            // each pixel

            int redX = 0;
            int greenX = 0;
            int blueX = 0;

            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            // neighbouring pixels
             for(int x =0; x < 3;x++)
            {
              for(int y =0; y < 3; y++)
                 {
                    // check valid pixels =>
                    // current X (image[i - 1 + x]) <0 or current Y (image[j - 1 + y]) <0
                    // or current X (image[i - 1 + x]) < (height -1) or current Y (image[j - 1 + y]) < (width -1)
                  if( i - 1 + x < 0 || i - 1 + x > height -1 || j - 1 + y < 0 ||  j - 1 + y > width -1)
                  {
                    continue;
                  }


                    // img = i=0/ j=0
                    //        -1    0   +1                           0  1  2
                    //    -1 | N1 | N2 |    |                    0 |-1|0 |+1|      |-1|-2|-1|
                    //     0 |    | img|    | => i=0 / j=0 => Gx 1 |-2|0 |+2|  Gy  |0 |0 |0 | => x=0 / y=0
                    //    +1 | N6 |    |    |                    2 |-1|0 |+1|      |+1|+2|+1|
                    // N1 => i = i-1/ j= j-1
                    // N2 => i = i -1 + x (x=1) => i   j = j -1 + y
                    // N6 => i = i - 1 + x (x=2)


                    redX += image[i - 1 + x][j - 1 + y].rgbtRed * gX[x][y];
                    greenX += image[i - 1 + x][j - 1 + y].rgbtGreen * gX[x][y];
                    blueX += image[i - 1 + x][j - 1 + y].rgbtBlue * gX[x][y];
                    redY += image[i - 1 + x][j - 1 + y].rgbtRed * gY[x][y];
                    greenY += image[i - 1 + x][j - 1 + y].rgbtGreen * gY[x][y];
                    blueY += image[i - 1 + x][j - 1 + y].rgbtBlue * gY[x][y];


                 }
            }

            // g = √gX^2 + gY^2
            int red = round(sqrt((redX * redX) + (redY * redY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));

            // it shouldn't be more than 255
            if(red > 255)
            {
                red = 255;
            }
            if(green > 255)
            {
                green = 255;
            }
            if(blue > 255)
            {
                blue = 255;
            }

            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;

        }
    }

    for(int i =0; i < height;i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
    return;
}
