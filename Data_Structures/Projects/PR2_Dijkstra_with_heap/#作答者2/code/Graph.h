#ifndef __GRAPH__
#define __GRAPH__
// This is a header file for Graph
#include <string>
using namespace std;

struct Edge {
    int to, w, nxt;
};
struct Graph {
    int numNode, numEdge, *heads;
    Edge *edges;
    Graph(int m_, int n_, int *head_, Edge *e_) : numEdge(m_), numNode(n_), heads(head_), edges(e_) {};
};

#endif

