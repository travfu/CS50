// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage - correct number of arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize_factor infile outfile\n");
        return 1;
    }

    // ensure proper usage - resize factor is a positive integer between 0-100
    if (atoi(argv[1]) <= 0 || atoi(argv[1]) > 100)
    {
        fprintf(stderr, "Error: invalid resize_factor\n");
        return 1;
    }

    // remember filenames
    int resize_factor = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // storage for outfile's headers
    BITMAPFILEHEADER bf_out = bf;
    BITMAPINFOHEADER bi_out = bi;

    // modify members of header to accompany resizing (1)
    bi_out.biWidth *= resize_factor;
    bi_out.biHeight *= resize_factor;

    // determine padding (bytes) for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine padding (bytes) for outfile scanlines
    int padding_out = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // modify members of header to accompany resizing (2)
    bi_out.biSizeImage = bi_out.biWidth * abs(bi_out.biHeight) * sizeof(RGBTRIPLE) + padding_out * abs(bi_out.biHeight);
    bf_out.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi_out.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0; i < abs(bi.biHeight); i++)
    {
        // copy scanline to outfile n times
        for (int j = 0; j < resize_factor; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage for each 'pixel'
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n (resize_factor) times
                for (int l = 0; l < resize_factor; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // write padding, if appropriate
            for (int m = 0; m < padding_out; m++)
            {
                fputc(0x00, outptr);
            }

            // fseek to beginning of scanline in infile
            if (j < resize_factor - 1)
            {
                fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
            else
            {
                fseek(inptr, padding, SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
