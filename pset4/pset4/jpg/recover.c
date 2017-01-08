/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

#define WORD 512

int main(void)
{
    FILE* card = fopen("card.raw", "r");
    if(card == NULL)
    {
        printf("file not found!");
        return 1;
    }
    
    int control; 
    unsigned char str[WORD];
    char jpg_name[20];
    int counter = 0;    
    while(fread(str, sizeof(char), WORD, card) > 0)
    {
        if(str[0] == 0xff && str[1] == 0xd8 && str[2] == 0xff && (str[3] >= 0xe0 && str[3] <= 0xef))
        {
            // fseek(card, -WORD, SEEK_CUR);
            sprintf(jpg_name, "%03i.jpg", counter);   
            FILE* out = fopen(jpg_name, "a");
            do
            {
                // printf("%li\n", ftell(card)-WORD);
                fwrite(str, sizeof(char), WORD, out);
                control = fread(str, sizeof(char), WORD, card);
            }
            while(!(str[0] == 0xff && str[1] == 0xd8 && str[2] == 0xff && str[3] >= 0xe0 && str[3] <= 0xef) && control > 0 );
            fseek(card, -WORD, SEEK_CUR);
            fclose(out);
            counter++;
            
        }
    }
    
    fclose(card);
    // free(jpg_name);
    return 0;
} 

