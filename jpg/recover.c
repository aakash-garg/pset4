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
    
    BYTE buffer;
    
    while()
    {
        fread()
    }
}
