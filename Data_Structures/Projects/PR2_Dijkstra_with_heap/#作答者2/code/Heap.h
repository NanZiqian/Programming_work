#ifndef __HEAPS__
#define __HEAPS__

struct Path{
    int start, end;
    long long length;
    Path(){}
    Path(int s, int e, int l):start(s), end(e), length(l){}
};

struct Node{
    Path path;
    int dist;
    Node *left, *right;
    Node(Path p) : path(p), dist(0), left(nullptr), right(nullptr) {}
};

class CompleteHeap{
private:
    Path heap[100000];
    int size = 0;
    void percolateUp(int index);
    void percolateDown(int index);
    // swap function involved in other member functions
    void swap(Path & h1, Path & h2);
public:
    // Insert a new path
    void insert(Path p);
    // Delete the minimum path
    Path deleteMin();
    // Check if the heap is empty
    bool isEmpty();
};

class LeftistHeap{
private:
    Node* root;
    // Merge two nodes
    Node* merge(Node* h1, Node* h2);
    // swap function involved in other member functions
    void swap(Node*& h1, Node*& h2);
public:
    // Constructor
    LeftistHeap();
    // Insert a new path
    void insert(Path p);
    // Delete the minimum path
    Path deleteMin();
    // Check if the heap is empty
    bool isEmpty();
};

class SkewedHeap {
private:
    Node* root;
    // merge two nodes
    Node* merge(Node* h1, Node* h2);
    // swap function involved in other member functions
    void swap(Node*& h1, Node*& h2);
public:
    SkewedHeap();
    // insert a path into the heap
    void insert(Path p);
    // extract the minimum path from the heap
    Path deleteMin();
    // check if the heap is empty
    bool isEmpty();
};

class FibonacciHeap {
private:
    struct List;
    struct trNode;
    List *minp;
    List *C[100];
    List* _add(List *X, List *Y);
    List* newNode(Path p);
    List * _delete(List *p);
public: 
    FibonacciHeap();
    void insert(Path p);
    Path deleteMin();
    bool isEmpty();
    void print(List *p);
};

#endif
