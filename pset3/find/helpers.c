/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    bool result = false;
    for(int i = 0; i < n; i++)
    {
        if(values[i] == value)
            result = true;
    }
    return result;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    // selction sort
    int min = values[0];
    for(int i = 0; i < n; i++)
    {
        for(int t = i; t < n; i++)
        {
            if(min > values[t])
                min = values[t];
        }
        values[i] = min;
    }
}

