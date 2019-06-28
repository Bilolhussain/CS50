// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //save the resize factor n
    int n = atoi(argv[1]);
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    if (n < 1 || n > 100)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 4;
    }


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
    //create new file header equal to previously stored file header
    BITMAPFILEHEADER newbf;
    newbf = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    //create new info header equal to previously stored info header
    BITMAPINFOHEADER newbi;
    newbi = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    //width and height for new file
    newbi.biHeight = bi.biHeight * n;
    newbi.biWidth = bi.biWidth * n;


    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //new padding to be added in size of new file
    int newpadding = (4 - (newbi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //calculate size of image in the file
    newbi.biSizeImage = ((sizeof(RGBTRIPLE) * newbi.biWidth) + newpadding) * abs(newbi.biHeight);

    //calculate size of file
    newbf.bfSize = 54 + newbi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&newbf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&newbi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //Multiply n with each line
        for (int row = 0; row < n; row++ )
        {
            // iterate over pixels in scanline
            for (int m = 0; m < bi.biWidth; m++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //pixel counter ensures pixels in output file are n times the orignial
                int pixelcount = 0;

                //Iterate over each pixel n number of times and write it in output file
                while (pixelcount < n)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                    //increment pixelcount
                    pixelcount = pixelcount + 1;
                }
            }
            // add padding
            int k = 0;

            while (k < newpadding)
            {
                fputc(0x00, outptr);
                k = k + 1;
            }

            //Go back to start of line
            if (row < (n-1))
            {
                fseek(inptr, -(int)bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }
        }
        //Skip over padding if any
        fseek(inptr, padding, SEEK_CUR);
    }
    //close infile
    fclose(inptr);
    // close outfile
    fclose(outptr);
    //success
    return 0;
}
