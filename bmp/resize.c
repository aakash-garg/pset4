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
    
    int n = atoi(argv[1]);
    if(n<0 || n>100)
    {
        printf("the factor should be positive and not more than 100");
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
    
    int ori_width= bi.biWidth;
    int ori_height= bi.biHeight;
   
    bi.biWidth= bi.biWidth*n;
    bi.biHeight= bi.biHeight*n;

    int ori_Padding= (4-(ori_width*sizeof(RGBTRIPLE))%4)%4;
    int padding= (4-(bi.biWidth*sizeof(RGBTRIPLE))%4)%4;
    
    RGBTRIPLE *count = malloc(sizeof(RGBTRIPLE)*bi.biWidth);
    
    bi.biSizeImage= abs(bi.biHeight) * ((bi.biWidth * sizeof (RGBTRIPLE)) + padding);
    bf.bfSize= bi.biSizeImage + sizeof (BITMAPFILEHEADER) + sizeof (BITMAPINFOHEADER); 
    
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
//    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(ori_height); i < biHeight; i++)
    {
        int xx=0;
        // iterate over pixels in scanline
        for (int j = 0; j < ori_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            for(int x=0;x<n;x++)
            {
                count[xx] = triple;s
                xx++;
            }
        }
        
        // to skip the cursor over padding;
        fseek(inptr,ori_padding,SEEK_CUR);
          
        // then add it back (to demonstrate how)
        for(int temp=0;temp<n;temp++)
        {
            fwrite(&count,sizeof(RGBTRIPLE),bi.biWidth,outptr);
            
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
