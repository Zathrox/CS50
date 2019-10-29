#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[1];
    char *outfile = "0.jpeg";

    // open input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    /*FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    } */

    //char filename[7];

    char filename[8];

    // Sets the blocksize (depends on the filesystem)
    int blockSize = 512;

    // allocates space for buffer on heap
    unsigned char *buffer = malloc(blockSize);
    //unsigned char buffer[512] ;

    FILE *img = NULL;

    int counter = 0;

    bool newjpeg = false;


    while (fread(buffer, blockSize, 1, inptr) == 1)
    {
        // read infile's data 512 bytes a time and stores in buffer
        //fread(&buffer, 512, 1, inptr);
        printf("buffer0 %x\n", (unsigned char)buffer[0]);
        printf("buffer1 %x\n", (unsigned char)buffer[1]);
        printf("buffer2 %x\n", (unsigned char)buffer[2]);
        printf("buffer3 %x\n", (unsigned char)buffer[3]);

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            //if (img != NULL)
            //{
            //    fclose(img);
            //}
            //sprintf(filename, "%03i.jpg", counter);
            //img = fopen(filename, "w");

            newjpeg = true;

        }

        // Write blocksize to file
        //if (img != NULL)
        //{
        //    fwrite(buffer, blockSize, 1, img);
        //}




        if (newjpeg == true)
        {
            if (img != NULL)
            {
                fclose(img);
            }

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", filename);
                return 3;
            }
            counter++;
            newjpeg = false;

        }


        if (img != NULL)
        {
            fwrite(buffer, 512, 1, img);
        }

    }

    //if (img != NULL)
    //{
    //    fclose(img);
    //}

    free(buffer);
    fclose(inptr);


    /*
    printf("%s\n", outfile);

    unsigned char buffer[512];

    // read infile's
    fread(&buffer, 512, 1, inptr);

    while(fread(buffer, 512, 1, inptr) == 1)
    {
        fwrite(buffer, 512, 1, outptr);
    }

    sprintf(filename, "%03i.jpg", 75);
    FILE *img = fopen(filename, "w");
    printf("buffer0 %c\n", buffer[0]);

    // Checks the first 4 bits of the buffer correspond to that of a JPEG
    if (buffer[0] == 0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        (buffer[3] & 0xf0) == 0xe0)
    {
        //sprintf(filename, "%03i.jpg", 2);
        //FILE *img = fopen(filename, "w");
    } */

    //fclose(inptr);
    //fclose(outptr);
    //fclose(img);
    return 0;
}
