#include "the0.h"

void insertionSort(int* arr, long &comparison, long & swap, int size) 
{
    int i = 1;
    int x, j;

    while (i < size)
    {
        x = arr[i];
        j = i - 1;

        while (j >= 0)
        {
            comparison++;
            if (arr[j] > x)
            {
                arr[j+1] = arr[j];
                j--;
                swap++;
            }
            else 
            {
                break;
            }
        }
        arr[j+1] = x;
        i++;
    }    
}