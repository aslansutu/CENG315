#include "the1.h"

int abs(int a) {
    if (a < 0) {
        return -1 * a;
    }
    else {
        return a;
    }
    
}

void customSwap(unsigned short& a, unsigned short& b, long& swap, double& avg_dist, double& max_dist) {
    unsigned short temp = a;
    a = b;
    b = temp;

    int d = &b - &a;
    d = abs(d);
    avg_dist = ((avg_dist * swap) + d) / (swap + 1);
    if (d > max_dist)
        max_dist = d;
    swap++;
}

int medianOfThree(unsigned short* arr, int left, int right) {
    int mid = left + (right - left) / 2;

    unsigned short& leftVal = arr[left];
    unsigned short& rightVal = arr[right];
    unsigned short& midVal = arr[mid];

    long swap = 0;
    double avg_dist = 0.0;
    double max_dist = 0.0;

    customSwap(leftVal, rightVal, swap, avg_dist, max_dist);
    customSwap(leftVal, midVal, swap, avg_dist, max_dist);
    customSwap(midVal, rightVal, swap, avg_dist, max_dist);

    return mid;
}

int lomutoPartition(unsigned short* arr, int left, int right, long& swap, double& avg_dist, double& max_dist) {
    unsigned short pivot = arr[right];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (arr[j] >= pivot) {
            i++;
            if (i != j) {
                customSwap(arr[i], arr[j], swap, avg_dist, max_dist);
            }
        }
    }
    customSwap(arr[i + 1], arr[right], swap, avg_dist, max_dist);
    return i + 1;
}

int hoarePartition(unsigned short* arr, int left, int right, long& swap, double& avg_dist, double& max_dist) {
    unsigned short pivot = arr[(left + right) / 2];
    int i = left - 1;
    int j = right + 1;

    while (true) {
        do {
            i++;
        } while (arr[i] > pivot);

        do {
            j--;
        } while (arr[j] < pivot);

        if (i >= j) return j;

        customSwap(arr[i], arr[j], swap, avg_dist, max_dist);
    }
}

int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size) {
    if (size <= 1) return 0;

    int recursive_calls = 0;

    if (median_of_3) {
        int median_index = medianOfThree(arr, 0, size - 1);
        customSwap(arr[median_index], arr[size - 1], swap, avg_dist, max_dist);
    }

    int p;
    if (hoare) {
        p = hoarePartition(arr, 0, size - 1, swap, avg_dist, max_dist);
    } else {
        p = lomutoPartition(arr, 0, size - 1, swap, avg_dist, max_dist);
    }

    recursive_calls += quickSort(arr, swap, avg_dist, max_dist, hoare, median_of_3, p);
    recursive_calls += quickSort(arr + p + 1, swap, avg_dist, max_dist, hoare, median_of_3, size - p - 1);

    recursive_calls += 2;

    return recursive_calls;
}
