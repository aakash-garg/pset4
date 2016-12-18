/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
typedef uint8_t  BYTE;

int main()
{
    FILE *fp;
    fp=fopen("card.raw","r");
    
    if(fp==NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }
    
    FILE *output;
    output=NULL;
    
    BYTE buffer[512];
    int count=0;
    
    while(fread(buffer,512,1,fp)==1)
    {
        
        if(buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]==0xe0 || buffer[4]==0xe1))
        {
            if(output!=NULL)
            fclose(output);
        
            char filename[10];
            sprintf(filename,"%03d.jpg",count);
            count++;
            output = fopen(filename,"w");
        }
        
        if(output!=NULL)
        fwrite(buffer,512,1,output);
        
    }

    fclose(output);
    fclose(fp);
    
    return 0;
}