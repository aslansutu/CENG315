#include "the2.h"

// do not add extra libraries here
/*
    arr       : array to be sorted, in order to get points this array should contain be in sorted state before returning
    ascending : true for ascending, false for descending 
    size      : number of elements in the array
*/
int counting_sort(std::string *arr, int size, int index) {
    const int k = 27; // Alphabet size + 1 for strings that are shorter than index
    const int offsetVal = 'A' - 1; // Since all letters are capital
    int *bucket = new int[k];
    std::string *output = new std::string[size];
    int iterations = 0;

    // Set all values in bucket to zero
    for (int i = 0; i < k; i++) {
        bucket[i] = 0;
    }

    // Count letters. If size less than index than place in 0
    for (int i = 0; i < size; i++, iterations++) {
        if (arr[i].length() -1 < index) {
            bucket[0]++;
            continue;
        }

        bucket[arr[i][index] - offsetVal]++;
    }

    // Add bucket values
    for (int i = 1; i < k; i++, iterations++) {
        bucket[i] += bucket[i-1];
    }

    // Build output array
    for (int i = size - 1; i >= 0; i--, iterations++) {
        if (arr[i].length() -1 < index) {
            output[--bucket[0]] = arr[i];
            continue;
        }

        int c = arr[i][index]-offsetVal;
        output[--bucket[c]] = arr[i];
    }

    for (int i = 0; i < size; i++, iterations++) {
        arr[i] = output[i];
    }

    delete[] bucket;
    delete[] output;

    return iterations;
}

int radix_string_sort(std::string* arr, int size, bool ascending){
    int max_length = 0;

    for (int i = 0; i < size; i++) {
        max_length = max_length > arr[i].length() ? max_length : arr[i].length();
    }

    int iterations = 0;

    // Perform counting sort for each digit's place, starting from the least significant digit
    for (int index = max_length - 1; index >= 0; index--) {
        iterations += counting_sort(arr, size, index);
    }

    if (ascending == false) {
        std::string temp;
        for (int i = 0; i < size/2; i++) {
            temp = arr[i];
            arr[i] = arr[size - 1 - i];
            arr[size - 1 - i] = temp;
        }
    }


    return iterations; 
    
}
