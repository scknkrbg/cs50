#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name;
    do
    {
        name = GetString();
    }
    while(strlen(name) == 0);
    
    printf("%c", toupper(name[0]));
    
    for(int i = 0; i<strlen(name); i++)
    {
        if(name[i]==32)
            printf("%c", toupper(name[i+1]));
    }
    printf("\n");
    
    return 0;
}