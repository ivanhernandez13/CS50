/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
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
        printf("Usage: ./copy n infile outfile\n");
        return 1;
    }

    // remember filenames
    
    int factor = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    // checks for valid factor
    if (factor < 1 || factor > 100)
    {
        printf("inavlid factor");
        return 5;
    }
    
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
    
    
	
	//remember original width and height for fseek later
	int oWidth = bi.biWidth;
    int oHeight = bi.biHeight;
    //scale image size, width, and height by factor
    bi.biWidth *= factor;
    bi.biHeight *= factor;
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int opadding =  (4 - (oWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    
    // scale file size by factor
    bf.bfSize = (bi.biSizeImage) + 54;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    

    // iterate over infile's scanlines	//writes height
    for (int i = 0, biHeight = abs(oHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline	//repeats row
        for (int m = 0; m < factor; m++)
        {
        	//return to beggining of row by "factor" times to rewrite same row (also skips padding)
        	fseek(inptr, 54 + ((oWidth * 3 + opadding) * i), SEEK_SET);
        	//iterate over every horrizontal pixel
		    for (int j = 0; j < oWidth; j++)
		    {
		        // temporary storage
		        RGBTRIPLE triple;

		        // read RGB triple from infile
		        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

		        // write RGB triple to outfile	//rewrite every pixel "factor" times
		        for (int l = 0; l < factor; l++)
		        {
		            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
		        }				
			}
			for (int k = 0; k < padding; k++)
			{
			    fputc(0x00, outptr);
			}		
		 }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
