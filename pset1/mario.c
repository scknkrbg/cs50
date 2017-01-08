#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int c = 24;
    while(c < 0 ||  c > 23)
    {
        printf("Height: ");
        c = GetInt();
    }

    for(int i = 2; i <= c + 1; i++)
    {
        printf("%*s", c + 1 - i, "");

        for(int t = 1; t <= i; t++)
        {
            printf("%s", "#");
        }
        printf("\n");
    }


}

