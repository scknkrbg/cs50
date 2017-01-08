#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main (void)
{
    float raw;
    int owed;
    do
    {
        printf("O hai! How much change is owed?\n");
        raw = GetFloat() * 100;
        owed = round(raw);    
        // printf("%i\n", owed);
        // owed = round(owed);
    } while (owed < 0);
    
    
    int counter = 0;
    while(owed != 0)
    {
    	if((owed / 25) > 0 )
    	{
    		counter += (owed / 25);
    		owed %= 25;
    	}
    	else if ((owed / 10) > 0)
    	{
    		counter += (owed / 10);
    		owed %= 10;
    	}
    	else if ((owed / 5) > 0)
    	{
    		counter += (owed / 5);
    		owed %= 5;
    	}
    	else
    	{
    		counter += (owed / 1);
    		owed %= 1;
    	}
    }
    printf("%i\n", counter);
}