#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


// const char* lookup(const char* path);
// bool parse(const char* line, char* abs_path, char* query);

int main(void)
{

    
    
  
    
    const char line = "GET /hello.php?name=seckin HTTP/1.1";
    printf("%c\n", line);
    // char* abs_path = malloc(strlen(line)+1); 
    // char* query = malloc(strlen(line)+1);
    // printf("parsed = %d\n", parse(line, abs_path, query));
    
    // free(abs_path);
    // abs_path = NULL;
    
    // free(query);
    // query = NULL;
}


// const char* lookup(const char* path)
// {
//     const char s[2] = " ";
//     st
    
    
//     // if(last_dot == NULL && strchr(path, '/') != NULL)
//     //     return "NOT FOUND";
       
//     int i = 0;
//     while(last_dot[i] != '\0')
//         i++;
//     last_dot++;
//     char* tmp = malloc(sizeof(char)*6);
//     if(strchr(last_dot, '?'))
//         strncpy(tmp, last_dot, i-2);
//     else
//         strncpy(tmp, last_dot, i-1);
    
    
//     printf("last b = %s\n", tmp);
    
//     const char* key[8] = {"css", "html", "gif", 
//     "ico", "jpg", "js", "php", "png"};
    
//     const char* value[8] = {"text/css", "text/html", 
//     "text/gif", "image/x-icon", "image/jpeg", 
//     "text/javascript", "text/x-php", "image/png"};
    

//     for(i = 0; i < 8; ++i)
//     {
//         if(strcasecmp(tmp, *(key+i)) == 0)
//         {
//             return *(value+i);
//         }
//     }
//     free(tmp);
//     return NULL;   
// }


// bool parse(const char* line, char* abs_path, char* query)
// {

// /********************** METHOD ****************************/
//     char* method = malloc(sizeof(char) * 5);
//     memcpy(method, line, 5);
//     method[4] = ' ';
//     method[5] = '\0';
    
//     if(strncmp(method, "GET ", 4) != 0)
//     {
//         // error(405);
//         printf("405\n");
//         return false;
//     } 
    
//     method[5] = '/';
    
//     if(strcmp(method, "GET /") != 0)
//     {
        
//     }
//     else if(strncpy())


//     return true;
// }