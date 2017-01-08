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

typedef char BYTE;

char* indexes(const char* path);
const char* lookup(const char* path);
bool parse(const char* line, char* abs_path, char* query);
bool load(FILE* file, BYTE** content, size_t* length);

int main(void)
{
    // const char* s = "leylaleyla.php?";
    
    // const char* d = lookup(s);
    
    // printf("%s\n", d);
    
   // home.php?name=seckin
    BYTE* content;
    size_t length;
  
    FILE *file = fopen("../public/cat.jpg", "rb");
    printf("%s\n", load(file, &content, &length) == 1 ? "dosya yuklendi" : "dosya yuklenmedi");
    
    const char* pth = "./";
    char* mm = indexes(pth);
    printf("file = %s\n", indexes(pth));
    free(mm);
    
    const char* line = "GETabc /hello.php HTTP/1.1";
    char* abs_path = malloc(strlen(line)+1); 
    char* query = malloc(strlen(line)+1);
    printf("parsed = %d\n", parse(line, abs_path, query));
    printf("lookup =%s\n", lookup("/hello.php"));
    
    free(abs_path);
    abs_path = NULL;
    
    free(query);
    query = NULL;

    fclose(file);
}

char* indexes(const char* path)
{
    DIR* directory = opendir(path);
    if(directory == NULL)
        return "Directory not found!";
    
    // printf("Directory = %s\n", path);
    struct dirent *d;
    int len = strlen(path) + strlen("/index.php")+2;
    
    char* dd = malloc(len * sizeof(char));
    strcpy(dd, path); 

    while(1)
    {
        if((d = readdir(directory)) != NULL)
        {
            if(strcmp(d->d_name, "deneme.php") == 0)
            {
                if(*(dd+strlen(dd)-1) == '/')
                {
                    closedir(directory);
                    strcat(dd, "index.php");
                    return dd;
                }
                    
                else
                {
                    closedir(directory);
                    return strcat(dd, "/index.php");
                }
            }
                
            else if(strcmp(d->d_name, "index.html") == 0)
            {
                if(*(dd+strlen(dd)-1) == '/')
                {
                    closedir(directory);
                    char* bb = strcat(dd, "index.html");
                    free(dd);
                    return bb;
                }
                else
                {
                    closedir(directory);
                    char* bb = strcat(dd, "/index.html");  
                    free(dd);
                    return bb;
                }
                    
            }
            else
            {
                // printf("bisiler oldu\n");
                continue;
            }
        }
        else
        {
            closedir(directory);
            return "Empty directory.";
        }
            
    }
    closedir(directory);
    return "File not found!";
}


bool load(FILE* file, BYTE** content, size_t* length)
{

    int len;

    //determine size
    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // read file into buffer
    *content = malloc(len);
    fread(*content, len, 1, file);
    *length = len;
    return true;
}



const char* lookup(const char* path)
{
   if(path == NULL)
        return "NOT FOUND";
    else if (strcmp(path, "/") == 0)
    {
        return path;
    }
    else if(strrchr(path, '.') == NULL && strlen(path) > 1)
    {
        char tmp[strlen(path)+2];
        for(int i = 0; i < strlen(path)+2; i++)
        {
            tmp[i] = *(path+i);
            if(*(path+i+1) == '\0' && *(path+i) != '/')
            {
                tmp[i+1] = '/';
                tmp[i+2] = '\0';
            }
        }
        
        const char* t = tmp;
        return t;
    }
    else
    {
        char* last_dot = strrchr(path, '.');
        last_dot++;
        const char* tmp = last_dot;
    
        
        const char* key[8] = {"css", "html", "gif", 
        "ico", "jpg", "js", "php", "png"};
    
        const char* value[8] = {"text/css", "text/html", 
        "image/gif", "image/x-icon", "image/jpeg", 
        "text/javascript", "text/html", "image/png"};
    

        for(int i = 0; i < 8; ++i)
        {
            if(strncasecmp(tmp, *(key+i),3) == 0)
            {
                // printf("abs_path = %s, %s\n", path, *(value+i));
                return *(value+i);
            }
        }
        return NULL;   
    }
}

bool parse(const char* line, char* abs_path, char* query)
{

/********************** METHOD ****************************/
    char* method = malloc(sizeof(char) * 5);
    memcpy(method, line, 5);
    *(method+4) = ' ';
    *(method+5) = '\0';
    
    if(strncmp(method, "GET ", 4) != 0)
    {
        // error(405);
        printf("405\n");
        return false;
    }

/********************** ABS PATH ***************************/
    const char* abs_path_start = strchr(line, ' ');
    abs_path_start++;
    printf("abs_path_start =%s\n", abs_path_start);
    
    if(*abs_path_start != '/')
    {
        printf("501\n");
        // error(501);
        return false;
    }
    
    
   
    if(strchr(abs_path_start, '?') != NULL )
    {
         int i = 0;
        while(*(abs_path_start + i) != '?')
        {
           *(abs_path + i) = *(abs_path_start + i);
            i++;   
        }
        *(abs_path + i) = '\0';
        
        // strncpy(abs_path, abs_path_start, i);
        // strcat(abs_path, "\0");
        printf("abs_path =%s %i\n", abs_path, i);
    }
    else
    {
        int i = 0;
        while(*(abs_path_start + i) != ' ')
        {
            *(abs_path + i) = *(abs_path_start + i);
            i++;   
        }
        *(abs_path + i) = '\0';
            
        // strncpy(abs_path, abs_path_start, i-1);
        // strcat(abs_path, "\0");
        printf("abs_path =%s\n", abs_path);
    }
    
    if(strchr(abs_path, '"') != NULL)
    {
        printf("400\n");
        // error(400);
        return false;
    }

    if(lookup(abs_path) == NULL)
    {
        printf("501\n");
        // error(501);
        return false;
    }
    // else if(lookup(abs_path) == "/")
    // {
        
    // }
    
    if(strcmp(lookup(abs_path), "NOT FOUND") == 0)
    {
        printf("404\n");
        // error(501);
        return false;
    }
/********************** QUERY *****************************/
    if(strchr(abs_path_start, '?') != NULL)
    {
        const char* query_start = strchr(abs_path_start, '?');
        // query_start = strchr(query_start, ' ');
        int i = 0;
        while(*(query_start + i) != ' ')
            i++;
        
        query_start++;
        strncpy(query, query_start, i);
        if(i == 0)
            query = "";
        else
            *(query + i) = '\0';
            
    
        printf("query =%s\n", query);
    }
    else
    {
        strcpy(query, "");
        printf("query = %s\n", query);
    }

    if(strchr(query, '"') != NULL)
    {
        printf("400\n");
        // error(400);
        return false;
    }

/********************** HTTP VERSION **********************/    
    char* http_tmp = strrchr(line, ' ');
    if(*(http_tmp-1) == ' ')
    {
        printf("505\n");
        // error(505);
        return false;
    }
    else
        http_tmp++;

    http_tmp = strstr(line, "HTTP/1.1");
    // http_tmp++;
    printf("http version = %s\n", http_tmp);
    
    if(http_tmp == NULL)
    {
        printf("505\n");
        // error(505);
        return false;
    }
    
    free(method);
    method = NULL;
    // error(501);
    // printf("501\n");
    return true;
}


