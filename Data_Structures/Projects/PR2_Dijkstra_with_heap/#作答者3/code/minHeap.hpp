#ifndef _MIN_HEAP_HPP
#define _MIN_HEAP_HPP
#include <cmath>
#include <algorithm>
using namespace std;
template <class T, int capacity>
class minHeap
{
public:
    minHeap() = default; //constructor
    ~minHeap() = default; //destructor
    bool empty() //Judge if the heap is empty
    {
        return size == 0 ? true : false;
    }
    void push(T value) //push a new node to the heap
    {
        min_heap[++size] = value;
        PercolateUp(size); //Adjust its position in heap
    }
    T deletemin() //Delete the minimum vertex
    {
        T temp = min_heap[1];
        swap(min_heap[1], min_heap[size]); //Replace the  minimum vertex with the last vertex
        size--; //Size of heap minus 1
        PercolateDown(1); //Percolate down the vertex swapped to the first position
        return temp;
    }
    void clear() //Clear the heap
    {
        size = 0; 
    }
private:
    T min_heap[capacity];
    int size = 0; //Size of the heap
    void PercolateUp(int p) //Percolate up
    {
        if (p == 1) //If it is in the first position, stop percolate down
        {
            return;
        }
        if (min_heap[p] < min_heap[p >> 1]) //If the key of the current vertex is smaller than its parent's
        {
            swap(min_heap[p], min_heap[p >> 1]); //swap the current vertex and its parent
            PercolateUp(p >> 1); //Continue to percolatedown
        }
        return;
    }
    void PercolateDown(int p) //Percolate down
    {
        int child = p << 1; //index of children = index of parent * 2
        if(child + 1 < size && min_heap[child + 1] < min_heap[child]) 
        {
            child++; //Find the child with smaller key
        }
        if(child < size && min_heap[child] < min_heap[p])
        {
            swap(min_heap[child], min_heap[p]); //swap the current vertex and its child with smaller key
            PercolateDown(child); //Continue to percolate
        }
    }
};
#endif