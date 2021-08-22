#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

typedef struct
{
    char* name;
    float value;

} variable;
int parent(int i);
int LeftChild(int i);
int RightChild(int i);
void MaxHeapify(variable arr[], int n, int i);
void BuildHeap(variable arr[], int n);
void SortHeap(variable arr[], int n);
void print(variable arr[], int n);
#endif
