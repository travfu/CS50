#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Validate for one command-line argument
    if (argc != 2)
    {
        fprintf(stderr, "Usage: filename.raw\n");
        return 1;
    }

    // remember filename
    char *infile = argv[1];

    // open infile
    FILE *input = fopen(infile, "r");
    if (input == NULL)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 2;
    }

    // Determine number of blocks in input file
    fseek(input, 0, SEEK_END);               // go to end of file
    int input_size = ftell(input);           // and what is its position?
    fseek(input, 0, SEEK_SET);
    int total_blocks = input_size / BLOCK_SIZE;

    // variables for jpeg file naming
    char filename[8];
    int filecount = 0;
    FILE *output = NULL;

    // buffer for 512byte blocks
    unsigned char block[BLOCK_SIZE];


    for (int i = 0; i < total_blocks; i++)
    {
        // read a block from memory card
        fread(&block, 1, sizeof(block), input);

        // if JPEG Header is present in block, then...
        if (block[0] == 0xFF && block[1] == 0xD8 && block[2] == 0xFF)
        {
            // if output file is already open, close it
            if (output != NULL)
            {
                fclose(output);
                output = NULL;
            }

            // if no output file is opened, create a new one (with incrementing filename)
            if (output == NULL)
            {
                sprintf(filename, "%03i.jpg", filecount);
                filecount++;

                output = fopen(filename, "w");
            }

            // write from block buffer to output file
            fwrite(&block, 1, sizeof(block), output);
        }

        // if JPEG Header is absent, then...
        else if (output != NULL)
        {
            // write from block buffer to existing output file
            fwrite(&block, 1, sizeof(block), output);
        }
    }

    fclose(input);
    fclose(output);
}