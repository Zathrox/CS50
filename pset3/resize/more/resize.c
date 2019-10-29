// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: size infile outfile\n");
        return 1;
    }

    float resize = atof(argv[1]);
    if (resize <= 0.0f || resize >= 100.0f)
    {
        printf("Usage: size infile outfile\n");
        printf("Usage: size must be a float value between 1 and 100\n");
        return 2;
    }

    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_out;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_out = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_out;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_out = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // Stores the new width+height * the value given by user
    bi_out.biWidth = floor(bi.biWidth * resize);
    bi_out.biHeight = floor(bi.biHeight * resize);

    // determine old padding for original scanlines
    int oldPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


    bi_out.biSizeImage = ((sizeof(RGBTRIPLE) * bi_out.biWidth) + newPadding) * abs(bi_out.biHeight);
    bf_out.bfSize = bi_out.biSizeImage + sizeof(bf_out) + sizeof(bi_out);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);


    // Debugging print lines
    printf("old width: %d\n", bi.biWidth);
    printf("new width: %d\n", bi_out.biWidth);
    printf("old height: %d\n", bi.biHeight);
    printf("new height: %d\n", bi_out.biHeight);
    printf("old padding: %d\n", oldPadding);
    printf("new padding: %d\n", newPadding);
    printf("size in bytes of a triple: %lu\n", sizeof(RGBTRIPLE));
    printf("size of file in bytes: %i\n", bf.bfSize);




    if (resize >= 1.0f)
    {
        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // temporary storage
            RGBTRIPLE triple;

            //Iterate over infile's scanlines n-1 times
            for (int j = 0; j < resize; j++)
            {
                // iterate over pixels in scanline
                for (int k = 0; k < bi.biWidth; k++)
                {

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // Iterates overs pixels n times the value provided
                    for (int l = 0; l < resize; l++)
                    {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }

                }

                // Calculates and adds in the new padding if needed
                for (int m = 0; m < newPadding; m++)
                {
                    fputc(0x00, outptr);
                }

                if (j < resize - 1)
                {
                    // Send infile cursor back to beginning of row
                    fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
                }

            }

            // skip over old padding, if any
            fseek(inptr, oldPadding, SEEK_CUR);

        }
    }
    else if (resize < 1.0f)
    {
        // Divide 1 by factor, this gives me an iterative number to jump/slip with
        float f = 1 / resize;
        // Due to the nature of floats, I use floor, to round down to the nearest number incase of odd values eg. 1.33
        int roundf = floor(f);
        printf("Divided Float: %f\n", f);
        printf("RoundF: %i\n", roundf);

        // iterate over the infile's scanline += roundf, so 0 = 2, 2 = 4, 4 = 6, effectively skipping scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i += roundf)
        {
            // iterates over the infiles pixels
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // If modulo remainder is 0, write pixel, if not, skip pixel
                printf("Modulo: %i", j % roundf);
                if (j % roundf == 0)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }
            // skip over old padding, if any
            fseek(inptr, oldPadding, SEEK_CUR);

            // Calculates and adds in the new padding if needed
            for (int m = 0; m < newPadding; m++)
            {
                fputc(0x00, outptr);
            }

            // Moves the cursor to the start of the next line
            fseek(inptr, ((bi.biWidth * sizeof(RGBTRIPLE)) + oldPadding) * (roundf - 1), SEEK_CUR);
        }
        printf("Value is lower than 1.0f\n");
    }



    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
