#ifndef THE1_H
#define THE1_H

void customSwap(unsigned short& a, unsigned short& b);
int medianOfThree(unsigned short* arr, int left, int right);
int lomutoPartition(unsigned short* arr, int left, int right, long& swap, double& avg_dist, double& max_dist);
int hoarePartition(unsigned short* arr, int left, int right, long& swap, double& avg_dist, double& max_dist);
int quickSort(unsigned short* arr, long& swap, double& avg_dist, double& max_dist, bool hoare, bool median_of_3, int size);

#endif // THE1_H
