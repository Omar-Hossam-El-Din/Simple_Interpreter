#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "heap.h"
int parent(int i)
{
    return (i-1)/2;
}

int LeftChild(int i)
{
    return 2*i+1;
}

int RightChild(int i)
{
    return 2*i+2;
}

void MaxHeapify(variable arr[], int n, int i)
{
    variable temp;
    int largest = i; // Initialize largest as root
    int left = LeftChild(i);
    int right= RightChild(i);

    // If left child is larger than root
    if (left < n && arr[left].value > arr[largest].value)
        largest = left;

    // If right child is larger than largest
    if (right < n && arr[right].value > arr[largest].value)
        largest = right;

    // If largest is not root
    if (largest != i)
    {
        temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Recursively call the swap_largest
        MaxHeapify(arr, n, largest);
    }
}

void BuildHeap(variable arr[], int n)
{
    // Build heap from an unsorted array (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        MaxHeapify(arr, n, i);
}

void SortHeap(variable arr[], int n)
{
    variable temp;
    // One by one extract an element from heap
    for (int i = n-1 ; i >= 0; i--)
    {

        // Move current root to end
        temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // call swap_largest on the reduced heap
        MaxHeapify(arr, i, 0);
    }
}

void print(variable arr[], int n)
{
    printf("\n\nSort According to values using Heap\n\n");
    for(int i = 0; i < n; i++)
    {
        printf("%s = %.2f\n", arr[i].name, arr[i].value);
    }

}
