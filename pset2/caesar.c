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
        return argc;
    }
    else
    {
        int k = atoi(argv[1]);
        do
        {
            plain  = GetString();
        }
            while(strlen(plain)==0);
           // printf("key = %i\n", k);
        
            for(int i = 0; i < strlen(plain); i++)
            {
                if(plain[i]==32)
                    printf("%c", plain[i]);
                else if(!isalpha(plain[i]))
                    printf("%c", plain[i]);
                else if(isupper(plain[i]))
                    printf("%c", 'A' + ((plain[i] - 'A' + k) % 26));
                else printf("%c", 'a' + ((plain[i] - 'a' + k) % 26));
           
            
            }
            printf("\n");
            return 0;
        }
  

}