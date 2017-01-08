/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

void sort(int values[], int n);
bool binary_search(int value, int values[], int start, int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    // binary search
    sort(values, n);
    return binary_search(value, values, 0, n);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int min_index, temp;
    int min_array(int values[], int start, int end);
    // TODO: implement an O(n^2) sorting algorithm
    // selection sort
    for(int start = 0; start < n; ++start)
    {
        min_index = min_array(values, start, n);
        temp = values[min_index];
        values[min_index] = values[start];
        values[start] = temp;
    }
}


int min_array(int values[], int start, int end)
{
    int min = values[start];
    int min_index = start;
    for(start++; start < end; ++start)
    {
        if(min > values[start])
        {
            min = values[start];
            min_index = start;
        }
    }
    return min_index;
}



bool binary_search(int value, int values[], int start, int n)
{
    int avg = (start + n) / 2;
    if(start > n)
        return false;
    else if(values[avg] == value)
        return true;
    else if(values[avg] > value)
        return binary_search(value, values, start, avg-1);
    else 
        return binary_search(value, values, avg+1, n);
}