#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    
    int two_bytes = sizeof(int);
    FILE* file = fopen("small.bmp", "rb");
    int* ptr = malloc(two_bytes);
    
    while(fread(ptr, 1, 1, file))
    {
        printf("before: %02x\n", *ptr);
        // fread(ptr, 1, 1, file);
        // printf("after: %x\n", *ptr);
    }
    
    
    free(ptr);
    fclose(file);
    
    return 0;
}