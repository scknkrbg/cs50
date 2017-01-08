/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>


/**
 * 
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    control = root;
    FILE* w = fopen("words.txt", "a+");
    fprintf(w, "%s\n", word);
    fclose(w);
    int wsize = strlen(word);
    int cposition;
    for(int counter = 0; counter < wsize; counter++)
    {
        if(isalpha(word[counter]) || word[counter] == '\'')
            cposition = word[counter] == '\'' ? 26 : tolower(word[counter])-'a';
        else
            return false;
        // printf("%i %i loc = %p\n", control->is_word, cposition, control->children[cposition]);
        
        if(control->children[cposition] == NULL)
            return false;
        else if (counter == wsize-1 && control->is_word == true)
            return true;
        else
            control = control->children[cposition];
    }
    return false;
}


/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    if(dict == NULL)
    {
        printf("%s not found!", dictionary);
        return -1;
    }
    
    // root = NULL;
    root = calloc(1, sizeof(node)); 
    control = root;
    
    int ccount = 0, loc;
    wcount = 0;
    char c = fgetc(dict);
    while(c != EOF)
    {
        loc = letter_loc(c);
        if(ccount >= 0 && loc >= 0)
        {
            if(control->children[loc] == NULL)
            {
                control->children[loc] = calloc(1, sizeof(node));
            }
        // TEST for dynamic memory allocation of chars.
        // printf("%c at %ith loc = %p\n", c, loc, control->children[loc]);
        }
        
        c = fgetc(dict);

        if(c == '\n')
        {
            control->is_word = true;
            control = root;
            wcount++;
            ccount = 0;
            c = fgetc(dict);
        } 
        else
        {
            ccount++;
            // control->is_word = false;
            if(loc >= 0)
            {
                control = control->children[loc];
            }   
        }

    }

    
    int f_wcount = dict_wcount(dict);
    // ptr_wcount = &wcount;
    // printf("ptr_wcount %i\n", *ptr_wcount);
    fclose(dict);
    
    if(f_wcount == wcount)
        return true;
    else
        return false;
}




/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   return wcount;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    int deleted = 0, c2=0;
    for(int c = 0; c < 27; c++)
    {
        control = root;
        if(control->children[c] != NULL) //root->children[c]
        {
            // printf("%i %i = %p\n", control->is_word, c, control->children[c]);
            // control = control->children[c]; //root->children[c]->children[i]
            for(int i = 0; i < 27; i++)
            {
                if(control->children[i] != NULL)
                {   
                    c2 = i;
                    // printf("%i %i = %p\n", control->is_word, i, control->children[i]);
                    control2 = control;
                    // printf("%i = %p\n", i, control2->children[c2]);
                    control = control->children[i];
                    // printf("%i = %p\n", i, control2->children[c2]);
                    i = -1;
                }
                
                
                if(i == 26 && control2->children[c2] != NULL)
                {
                    // printf("%i = %p\n", i, control2->children[c2]);
                    if(control2->is_word == true)
                    {
                        // printf("%c %i %i loc %p\n", c2+97, control2->is_word, c2, control2->children[c2]);
                        deleted++;
                    }
                    // printf("%c %i loc = %p\n", c2+97, c2, control2->children[c2]);
                    free(control2->children[c2]);
                    // printf("deleted = %i\n", deleted);
                    control2->children[c2] = NULL;
                    control = root;
                    i = c-1;
                }
            
            }
        }
    }
    free(root);
    // printf("deleted = %i, wcount = %i\n", deleted, wcount);
    // if(deleted == wcount)
    //     return true;
    return true;
}


// harfin trie children node uzerindeki yerini soyler.
int letter_loc (char c)
{
    if(c == '\'')
        return 26;
    else if(isalpha(c))
        return ((c-'a') % 26);
    return -1;
}



// dosya icindeki kelimeleri sayar. 
int dict_wcount(FILE* file)
{
    int count = 0;

    rewind(file);
    char c = fgetc(file);
    while(c != EOF)
    {
    	if(c == '\n')
    		count++;
    	c = fgetc(file);
    }
    return count;
}

