/****************************************************************************
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Jaizon Lubaton
 ***************************************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: resize factor infile outfile\n");
        return 1;
    }
    
    // get resize factor
    int factor = atoi(argv[1]);
       
    // ensure n is is a positive int less than or equal to 100
    if (factor > 100 || factor < 1)
    {
        printf("factor must be a positive int less than or equal to 100\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    // create variables for original width and height
    int originalWidth = bi.biWidth;
    int originalHeight = bi.biHeight;
   
    // resize width and height
    bi.biWidth *= factor;
    bi.biHeight *= factor;
       
    // determine padding for scanlines
    int originalPadding =  (4 - (originalWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update image size
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + padding);
    
    // update file size
    bf.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER); 

    // set outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // set outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // dynamic memory allocation in heap to store resized image
    RGBTRIPLE *imgBuffer = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));

    // iterate infile's scanlines
    for (int i = 0, biHeight = abs(originalHeight); i < biHeight; i++)
    {
        int tracker = 0;
        // iterate over pixels in scanline
        for (int j = 0; j < originalWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // feed pixel to buffer n times
            for (int k = 0; k < factor; k++)
            {
                *(imgBuffer + (tracker)) = triple;
                tracker++;
            }
        }
            
        // skip over padding, if any
        fseek(inptr, originalPadding, SEEK_CUR);

        // write RGB triple to outfile
        for (int m = 0; m < factor; m++)
        {
            fwrite((imgBuffer), sizeof(RGBTRIPLE), bi.biWidth, outptr);

            // write padding to outfile
            for (int n = 0; n < padding; n++) 
                fputc(0x00, outptr);
        }        
    }

    // free memory from buffer
    free(imgBuffer);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}