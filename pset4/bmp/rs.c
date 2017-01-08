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
    int n = atoi(argv[1]);
    
    // ensure program limits
    if(n < 1 || n > 100)
    {
        printf("Out of boundary!");
        return 1;
    }
    
    // ensure proper usage
    // ./resize 3 input output
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 2;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bf_res;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bf_res = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bi_res;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bi_res = bi;
    
    printf("bf.bfType = %x\n", bf.bfType);
    printf("bf.bfOffBits = %x\n", bf.bfOffBits);
    printf("bi.biSize = %x\n", bi.biSize);
    printf("bi.biBitCount = %x\n", bi.biBitCount);
    printf("bi.biCompression = %x\n\n", bi.biCompression);
    
    printf("bf_res.bfType = %x\n", bf_res.bfType);
    printf("bf_res.bfOffBits = %x\n", bf_res.bfOffBits);
    printf("bi_res.biSize = %x\n", bi_res.biSize);
    printf("bi_res.biBitCount = %x\n", bi_res.biBitCount);
    printf("bi_res.biCompression = %x\n\n", bi_res.biCompression);
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    // determine padding for scanlines
   
    
    bi_res.biWidth = bi.biWidth * n;
    bi_res.biHeight = bi.biHeight * n;
    int new_padding =  (4 - (abs(bi_res.biWidth) * sizeof(RGBTRIPLE)) % 4) % 4;
    int old_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    printf("padding : %d\n", new_padding);
    printf("padding : %d\n\n", old_padding);
    
    bi_res.biSizeImage = (bi_res.biWidth * sizeof(RGBTRIPLE) + new_padding) * abs(bi_res.biHeight);
    bf_res.bfSize = sizeof(bi_res) + sizeof(bf_res) + bi_res.biSizeImage;
    
    printf("bi.biWidth = %d\n", bi_res.biWidth);
    printf("bi.biHeight = %d\n", bi_res.biHeight);
    printf("bi.biSizeImage = %d\n", bi_res.biSizeImage);
    printf("bi.bfSize = %d\n", bf_res.bfSize);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_res, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_res, sizeof(BITMAPINFOHEADER), 1, outptr);

    // int setting = bi.biWidth * sizeof(RGBTRIPLE) + old_padding;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
       for(int j = 0; j < bi.biWidth; j++)
       {
           RGBTRIPLE triple;
           
           fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
           
           for(int h = i * n; h < i * n + n; h++)
           {
               for(int r = j * n; r < j * n + n; r++)
               {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);        
               }
           }
        }
        
        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);
        
        // then add it back (to demonstrate how)
        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
        }
        
        // fseek(inptr, -setting, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
