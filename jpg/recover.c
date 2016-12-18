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
#include"bmp.h"

int main(int argc, char* argv[])
{
    FILE *fp;
    fp=fopen("card.raw","r");
    
    if(fp==NULL)
    {
        cout<<"Error opening file.\n";
    }
    
    FILE *output;
    output=NULL;
    
    BYTE buffer[512];
    int count=0;
    
    while(1)
    {
        fread(buffer, 512,1,fp);
        
        if(buffer[0]=0xff && buffer[1]=0xd8 && buffer[2]=0xff && (buffer[3]==0xe0 || buffer[4]==0xe1)
        {
            fclose(output);
        
            char* filename[10];
            sprintf(filename,"%.3d.jpg"count);
            count++;
            fopen("filename","w");
        }
        fwrite(buffer,512,1,output);
        if(feof(fp))
        {
            break;
        }
        
    }
    
    fclose(output);
    fclose(fp);
}
