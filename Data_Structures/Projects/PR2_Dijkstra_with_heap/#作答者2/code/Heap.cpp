#include "Heap.h"
#include <iostream>
using namespace std;

///////////////////////////////////////////////////////////
// The implementation of Binary Heap (Complete Heap)
///////////////////////////////////////////////////////////

void CompleteHeap::percolateUp(int index){
    // Compare the node with its parent, and swap if parent is greater
    while(index > 0 && heap[(index-1)/2].length > heap[index].length){
        swap(heap[(index-1)/2], heap[index]);
        index = (index-1)/2;
    }
}

void CompleteHeap::percolateDown(int index){
    // Compare the node with its children, and swap with the smaller child
    int left_child = index*2 + 1;
    int right_child = index*2 + 2;
    int smallest = index;
    if(left_child < size && heap[left_child].length < heap[smallest].length){
        smallest = left_child;
    }
    if(right_child < size && heap[right_child].length < heap[smallest].length){
        smallest = right_child;
    }
    if(smallest != index){
        swap(heap[index], heap[smallest]);
        percolateDown(smallest);
    }
}

// Insert a new path into the heap
void CompleteHeap::insert(Path path){
    // Insert the new node at the end of the heap
    heap[size] = path;
    size++;
    // Heapify up the new node
    percolateUp(size-1);
}

// Delete the minimum path from the heap
Path CompleteHeap::deleteMin(){
    // Swap the root with the last node
    Path min_path = heap[0];
    heap[0] = heap[size-1];
    size--;
    // Heapify down the root
    percolateDown(0);
    return min_path;
}

// Check if the heap is empty
bool CompleteHeap::isEmpty(){
    return size == 0;
}

// swap function involved in other functions
void CompleteHeap::swap(Path& a, Path& b){
    Path temp = a;
    a = b;
    b = temp;
}

///////////////////////////////////////////////////////////
// The implementation of Leftist Heap
///////////////////////////////////////////////////////////

// swap function involved in the functions
void LeftistHeap::swap(Node*& h1, Node*& h2) {
    Node* temp = h1;
    h1 = h2;
    h2 = temp;
}

// Merge two nodes
Node* LeftistHeap::merge(Node* h1, Node* h2) {
    if (h1 == nullptr) return h2;
    if (h2 == nullptr) return h1;
    if (h1->path.length > h2->path.length) swap(h1, h2);
    h1->right = merge(h1->right, h2);
    if (h1->left == nullptr || h1->left->dist < h1->right->dist) swap(h1->left, h1->right);
    if (h1->right == nullptr) h1->dist = 0;
    else h1->dist = h1->right->dist + 1;
    return h1;
}

// Constructor
LeftistHeap::LeftistHeap() {
    root = nullptr;
}

// Insert a new path
void LeftistHeap::insert(Path p) {
    Node* newNode = new Node(p);
    root = merge(root, newNode);
}

// Delete the minimum path
Path LeftistHeap::deleteMin() {
    Path minPath = root->path;
    Node* oldRoot = root;
    root = merge(root->left, root->right);
    delete oldRoot;
    return minPath;
}

// Check if the heap is empty
bool LeftistHeap::isEmpty() {
    return root == nullptr;
}

///////////////////////////////////////////////////////////
// The implementation of Skew Heap
///////////////////////////////////////////////////////////

SkewedHeap::SkewedHeap() {
    root = nullptr;
}

// swap function involved in the functions
void SkewedHeap::swap(Node*& h1, Node*& h2) {
    Node* temp = h1;
    h1 = h2;
    h2 = temp;
}

// merge two trees
Node* SkewedHeap::merge(Node* h1, Node* h2) {
    if(!h1) return h2;
    if(!h2) return h1;
    if (h2->path.length < h1->path.length) {
        swap(h1, h2);
    }
    h1->right = merge(h1->right, h2);
    swap(h1->left, h1->right);
    return h1;
}

// insert a path into the heap
void SkewedHeap::insert(Path p) {
    Node* newNode = new Node(p);
    root = merge(root, newNode);
}

// extract the minimum path from the heap
Path SkewedHeap::deleteMin() {
    Path minPath = root->path;
    Node* oldRoot = root;
    root = merge(root->left, root->right);
    if(oldRoot) delete oldRoot;
    return minPath;
}

// check if the heap is empty
bool SkewedHeap::isEmpty() {
    return root == nullptr;
}

///////////////////////////////////////////////////////////
// The implementation of Fibonacci Heap
///////////////////////////////////////////////////////////

struct FibonacciHeap::trNode {
    Path p;  // Data stored in tree node
    List *ch; // List node of children
    int sz;  // Size of the tree node
};
struct FibonacciHeap::List {
    List *pre;     // The previous list node 
    List *nxt;     // The next list node
    trNode *ver;   // The pointer to the tree node
    ~List() {
        delete ver; // When deleting the list node, delete cooresponding tree node.
    }
};

void FibonacciHeap::print(List *p = NULL) {
    if(p == NULL) p = minp;
    if(!p) return;
    cout << "in" << endl;
    for(List *i = p; ; i = i->nxt) {
        cout << i->ver->p.length << ' ' << i->ver->sz << endl;
        // if(i->ver->ch) print(i->ver->ch);
        if(i->nxt == p) break;
    }
    cout << "out" << endl;
}

// Create a new node and assign the pointers.
FibonacciHeap::List* FibonacciHeap::newNode(Path p) {
    List *c = new List;
    c->ver = new trNode;
    c->ver->p = p;
    c->ver->ch = nullptr;
    c->ver->sz = 0;
    c->pre = c;
    c->nxt = c;
    return c;
}

// Initially, set all the pointer to null.
FibonacciHeap::FibonacciHeap() {
    for(int i = 0; i < 100; ++i) C[i] = nullptr;
    minp = nullptr;
}

// Merge two lists and return the result
FibonacciHeap::List* FibonacciHeap::_add(List *X, List *Y) {
    if(!X) return Y;
    else if(!Y) return X;
    else {
        // 4 pointers need to be adjusted
        X->nxt->pre = Y->pre;
        Y->pre->nxt = X->nxt;
        X->nxt = Y;
        Y->pre = X;
        return X;
    }
}
// Delete a node from a list and return one of the remaining nodes.
FibonacciHeap::List * FibonacciHeap::_delete(List *p) {
    List *ret = p->nxt;
    p->nxt->pre = p->pre;
    p->pre->nxt = p->nxt;
    delete p;
    return ret;
}
// Insert a new node into heap
void FibonacciHeap::insert(Path p) {
    if(!minp) {
        minp = newNode(p);
        return;
    }
    List *c = newNode(p);
    minp = _add(minp, c);
    if(p.length < minp->ver->p.length) minp = c;
}
// Delete the minimum element and return its data
Path FibonacciHeap::deleteMin() {
    Path ret = minp->ver->p;
    List *c;
    // First add the children to the root list
    if(!minp->ver->ch) {
        if(minp->pre == minp) {
            delete minp;
            minp = nullptr;
            return ret;
        } else {
            c = _delete(minp);
        }
    } else {
        c = minp->ver->ch; 
        if(minp->pre == minp) {
            delete minp;
        } else {
            List *tmp = _delete(minp);
            c = _add(c, tmp);
        }
    }
    int mx = 0;
    for(List *i = c; ; i = i->nxt) {
        mx = max(mx, i->ver->sz);
        if(i->nxt == c) break;
    }
    // Merge trees of the same sizes. 
    for(List *i = c; ; i = i->nxt) {
        int sz = i->ver->sz;
        // Merging can be done many times
        while(C[sz]) {
            C[sz]->pre = C[sz]->nxt = C[sz];
            i->ver->ch = _add(i->ver->ch, C[sz]); // Merging is a simple connection of children list and root list
            i->ver->sz++;
            C[sz] = nullptr;
        }
        C[sz] = i;
        mx = max(mx, sz);
        if(i->nxt == c) break;
    }
    // Rebuild the root list
    List *las = nullptr, *fir = nullptr;
    minp = nullptr;
    for(int i = 0; i <= mx; ++i) if(C[i]) {
        if(las) {
            C[i]->pre = las;
            las->nxt = C[i]; 
        }
        if(!minp || C[i]->ver->p.length < minp->ver->p.length) 
            minp = C[i];
        las = C[i];
        if(!fir) fir = C[i];
        C[i] = nullptr;
    }
    las->nxt = fir;
    fir->pre = las;
    return ret;
}
// Check if the heap is empty.
bool FibonacciHeap::isEmpty() {
    if(minp == nullptr) return true;
    else return false;
}
