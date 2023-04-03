#include"graph_with_heaps.h"

int main() {
    // ListGraph<int, FibonacciHeap<pair<int, int>>, FibonacciNode<pair<int, int>>> a(8);
    // a.testListGraph();
    ListGraph<int, BinomialQueue<pair<int, int>>,BinomialNode<pair<int, int>>> b(8);
    b.testListGraph();
    return 0;
}