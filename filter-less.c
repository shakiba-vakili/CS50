#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //    j j j
    // i | | | |
    // i | | | |
    // i | | | |
    // each row of img
    for (int i = 0; i < height; i++)
    {
        // each pixel of img
        for (int j = 0; j < width; j++)
        {
            // Make dark and light gray
            //  As long as red, blue, and green are equal, they will be gray
            //  it should be round
            int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = avg;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // each pixel of img
        for (int j = 0; j < width; j++)
        {
            // sepia formola
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // prevent to be more than 255 cuz max hex is 255
            // they should be in diffrent if block cuz each them can be true
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Change pixel color to sepia color
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // just each row
    for (int i = 0; i < height; i++)
    {
        //    j j j
        // i | | | |
        // i | | | |
        // i | | | |
        // Loop through the first half of columns(j) in each row
        for (int j = 0; j < width / 2; j++)
        {
            //  A|B|C|D|E|F|G => left = A|B|C => right = E|F|G
            // i = 1; j=1, width=7
            // temp = B image[1][1]; B = image[1][7-1-1] (F spot); F = temp => f =image[1][1]
            // Store the left column in a temporary variable;
            RGBTRIPLE temp = image[i][j];
            // Move the right column in the left spot
            image[i][j] = image[i][width - j - 1];
            // Move the left column in the right spot
            image[i][width - j - 1] = temp;
        }
    }

    return;
}
// 1 find each pixel
// 2 find that pixel neighbor
// 3 calculate avg
// 4 apply avg to pixel

void blur(int height, int width, RGBTRIPLE image[height][width])

{
    /* temporary variable => cuz when we are not done with
       finding neighbor value applying the color in the pixel
       may ruin the pic so we are going to keep it into variable
    */
    RGBTRIPLE temp[height][width];
    // variable
    float counter;
    double totalR, totalG, totalB;


    // 1 find each pixel => i=row; j=col
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            totalR = 0;
            totalG = 0;
            totalB = 0;
            // how many red, green , blue exist?
            counter = 0;

            // 2 find that pixel neighbor
            // grid 3x3
            // |-| | |    | | | |    | | | |
            // | |*| | or | | |*| or | | | |
            // |-| | |    | | | |    |*| | |


            // When the desired pixel is found. To find the neighbors, col-1 , col+1 & row-1, row+1
            // this loops will finding neighbor

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
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;

}






