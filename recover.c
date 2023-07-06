#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

// 1 open memory card
// 2 find jpeg
// 3 open jpeg
// 4 write 512 bytes => find new jpeg
// repeat
int main(int argc, char *argv[])
{
    // check valid command line argument
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE \n");
        return 1;
    }

    // open input file
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL)
    {
        // if inputFile doesn't exist
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // set outfile pointer to NULL
    FILE *outPoniter = NULL;

    // create an array of 512 elements to store 512 bytes from the memory card
    BYTE buffer[512];

    int counterJpeg = 0;

    //string to hold a filename => xxx.jpg\n
    char filename[8]={0};

    // read memory card untill the end of file
    while (fread(buffer, sizeof(BYTE) * 512, 1, inputFile) == 1)
    {
        // check if jpeg is found
        // jpeg start: 0xff 0xd8 0xff
        // jpeg end: 0xe0 0xe1 .... 0xef

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // close outptr if jpeg was found before and written into ###.jpg
            if (outPoniter != NULL)
            {
                fclose(outPoniter);
            }
            sprintf(filename, "%03d.jpg", counterJpeg++);

            // open a new outptr for writing a new found jpeg
            outPoniter = fopen(filename, "w");
        }

        // keep writing to jpeg file if new jpeg is not found
        if (outPoniter != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, outPoniter);
        }
    }

    // close last opened outPoniter
    if (outPoniter != NULL)
    {
        fclose(outPoniter);
    }

    // close input file
    fclose(inputFile);
    return 0;
}