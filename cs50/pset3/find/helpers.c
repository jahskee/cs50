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
#include <string.h>
#include <ctype.h>
#include <stdlib.h>       

#include "helpers.h"

bool binsearch(int key, int* haystack, int low, int high);
void bubble_sort(int* array, int size);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    sort(values, n);
    return binsearch(value, values, 0, n);
   
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    return bubble_sort(values, n);
    
}


bool binsearch(int key, int* haystack, int low, int high)
{

    if ((high - low) == 1) 
    {
        if (key == haystack[high - 1]) 
        {
            return true;
        }
        return false;
    }

    int mid = (int) (low + high) / 2;

    if (key == haystack[mid]) 
    {
        return true;
    }

    // keep searching
    if (key < haystack[mid]) 
    {
        // search left
        high = mid;
    }
    else 
    {
        // search right
        low = mid;
    }

    return binsearch(key, haystack, low, high);
}

void bubble_sort(int* array, int size)
{
    for (int j = 0; j < size; j++) 
    {
        for (int i = 0; i < size - 1; i++) 
        {
            if (array[i] > array[i + 1]) 
            {
                int store = array[i];
                array[i] = array[i + 1];
                array[i + 1] = store;
            }
        }
    }
}