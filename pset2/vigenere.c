#include <stdio.h>
#include <ctype.h> 
#include <string.h>
#include <stdlib.h>
#include <cs50.h>



int main(int argc, string argv[])
{
    string plain;
    if(argc != 2)
    {
        printf("%i = argc \n", argc);
        return 1;
    }
    else
    {
        string k = argv[1];
        int k_len = strlen(k);
        for(int i = 0; i < k_len; i++)
        {
            if(!isalpha(k[i]))
            {
                printf("Keyword must be only A-Z and a-z\n");
                return 1;
            }
        }
        
        
        do
        {
            plain  = GetString();
        }
        while(strlen(plain)==0);
    
        
        int plain_len = strlen(plain);
        int space = 0;
        
        for(int i = 0, j; i < plain_len; i++)
        {
            j = (i-space) % (k_len); 
            
            if((int) plain[i]==32)
            {
                printf("%c", plain[i]);   
                space++;
            }
            else if(!isalpha(plain[i]))
            {
                printf("%c", plain[i]);
                space++;
            }   
            
            // plain is uppercase
            else if(isupper(plain[i]))
            {
                // plain & key are uppercase
                if(isupper(k[j]))
                    printf("%c", 'A'+ (plain[i]-'A' + k[j]-'A')%26);
                // plain is uppercase while key is lowercase
                else
                    printf("%c", 'A'+ (plain[i]-'A' + k[j]-'a')%26);
            }
            // plain is lowercase
            else
                // plain is lowercase while key is uppercase
                if(isupper(k[j]))
                    printf("%c", 'a' + (plain[i] - 'a' + k[j] - 'A')%26);
                // plain & key are lowercase 
                else
                    printf("%c", 'a' + (plain[i] - 'a' + k[j] - 'a')%26);
        }
        printf("%i", i);
        printf("\n");
        return 0;
    }
}

// 