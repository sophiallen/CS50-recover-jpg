/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    //remember resize factor
    int n = atoi(argv[1]);
    
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
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;  
      
        
    //declare new struct to hold modified file header 
    BITMAPFILEHEADER bf2 = bf;     
    
    BITMAPINFOHEADER bi2 = bi;
    
    //modify infoheader
    bi2.biHeight = bi.biHeight*n;
    bi2.biWidth = bi.biWidth*n;
    int padding2 = (4-(bi2.biWidth*sizeof(RGBTRIPLE))%4)%4;
    bi2.biSizeImage = abs((((padding2/bi2.biHeight)+bi2.biWidth)*bi2.biHeight)*3);
     
    //modify the file header
    bf2.bfSize = abs((((padding2/bi2.biHeight)+bi2.biWidth)*bi2.biHeight)*3)+54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf2, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi2, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int line = 0, biHeight = abs(bi.biHeight); line < biHeight; line++)
    {
        for (int rduplicate = 0; rduplicate < n; rduplicate++)
        {
            // iterate over pixels in scanline
            for (int pixel = 0; pixel < bi.biWidth; pixel++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times.
                for (int pduplicate = 0; pduplicate < n; pduplicate++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            
            if (rduplicate < n-1)
            {
                fseek(inptr, -(bi.biWidth-padding), SEEK_CUR);
            }
            
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
        }

        // then add it back
        for (int k = 0; k < padding2; k++)
        {
            fputc(0x00, outptr);
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
