#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstring>
#include <queue>
#include <limits.h>
#include "Graph.h"
#include "Heap.h"
using namespace std;

Edge e[1057070]; // Edges
int head[435670], cnt = 0; // Head of adjacency table
long long r[435670]; // The shortest path

Graph buildGraph(string str);

// Used to test priority_queue
bool operator < (Path u, Path v) {
    return u.length > v.length;
}

// Define a function to add edges to the graph
void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
}

int dijkstra(Graph &graph, int src, int dist){
    // Initialize all distances to infinity except for the starting vertex, which has a distance of 0.
    memset(r, 0x3f, sizeof(r));
    r[src] = 0;
    // Create a min heap to store the paths to each vertex.
    // When you want to change the heap used, simply change the type name into other heaps
    FibonacciHeap heap;
    // Insert the starting vertex with a distance of 0 into the heap.
    heap.insert(Path(src, src, 0));
    // While the heap is not empty, continue to find the shortest path to each vertex.
    while(!heap.isEmpty()){
        // Delete the path with the minimum distance from the heap.
        Path min_path = heap.deleteMin();
        int vertex = min_path.end;
        long long distance = min_path.length;
        // If the distance to the vertex is greater than the current distance, skip it.
        if(distance > r[vertex]){
            continue;
        }
        // For each edge connected to the vertex, calculate the new distance and update the distances vector if it is shorter.
        for(int i = graph.heads[vertex]; i; i = graph.edges[i].nxt){
            Edge edge = graph.edges[i];
            long long new_distance = distance + edge.w;
            if(new_distance < r[edge.to]){
                r[edge.to] = new_distance;
                // Insert the new path into the heap.
                heap.insert(Path(src, edge.to, new_distance));
            }
        }
    }
    // Return the distance to the destination vertex.
    return r[dist];
}

// The version for correctness check on https://loj.ac/p/119

// int main() {
//     int n, m, s, t;
//     scanf("%d%d%d%d", &n, &m, &s, &t);
//     for(int i = 1; i <= m; ++i) {
//         int x, y, z;
//         scanf("%d%d%d", &x, &y, &z);
//         add(x, y, z);
//         add(y, x, z);
//     }
//     Graph graph(m, n, head, e);
//     int ans = dijkstra(graph, s, t);
//     printf("%d\n", ans);
//     return 0;
// }

// The version for runtime comparison

// int main(void){
//     Graph graph = buildGraph("input.txt");
//     printf("Graph built with %d vertices and %d edges\n", graph.numNode, graph.numEdge);
//     double st = clock();
//     for(int i = 1; i <= 1000; ++i) {
//         int s = 1ll * rand() * rand() % graph.numNode + 1;
//         int t = 1ll * rand() * rand() % graph.numNode + 1;
//         int r = dijkstra(graph, s, t);
//     }
//     double ed = clock();
//     printf("Runtime for a single query: %lfms\n", (ed - st) / 1000);
//     return 0;
// }

// The main function

int main(void){
    Graph graph = buildGraph("input.txt");
    cout << "graph built" << endl;
    int s, t;
    while(scanf("%d%d", &s, &t) == 2) {
        int r = dijkstra(graph, 1, 3);
        printf("%d\n", r); 
    }
    return 0;
}



// This code reads input from a file and builds a graph using a forward star representation

Graph buildGraph(string filename) {    

    // Open the input file
    ifstream readFile; 
    readFile.open(filename, std::ios::in);
    if(!readFile.is_open()) {
        std::cout << "Fail to open file: " << filename << std::endl;
        return Graph(0,0,nullptr, nullptr);
    }

    // Read the number of vertices and edges
    int n = 0, m = 0;
    string s;
    char c;
    int u, v, w;

    // Read the input file line by line
    while(getline(readFile, s)){
    	istringstream iss(s);
    	iss >> c;
    	if(c == 'a'){
    		iss >> u >> v >> w;
    		add (u,v,w);
		}
        if(c == 'p'){
            string ss;
        	iss >> ss >> n >> m;
        }
	}

    // Close the input file
    readFile.close();

    // Return the graph as a struct
    return Graph(m, n, head, e);
}

