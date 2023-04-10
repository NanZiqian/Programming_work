#include <iostream>
#include <utility>
#include <fstream>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "minHeap.hpp" //Header that includes the Binart min-heap classes
using namespace std;
#define INF 0x7fffffff
#define MAX_NODE 23950000 //The maximum of vertices permitted
#define MAX_EDGE 58340000 //The maximum of edges permitted
clock_t start, stop;
double duration;
struct EDGE
{
    int to; //The tail of the edge
    int w; //The weight of the edge
    int next; //The next edge with the same head as that of the current edge
} edge[MAX_EDGE]; //Array of edges
int head[MAX_NODE]; //The first adjacent edge of each node 
int cnt = 0; //The number of edges already added to the graph
bool vis[MAX_NODE]; //Flag if each node is collected
inline void addedge(int u, int v, int w) //Add the current edge to the graph
{
    edge[++cnt].to = v; //The number of edges+1 and set the end of  the edge to be v
    edge[cnt].next = head[u]; //The next the edge from u is linked to the current edge from u
    edge[cnt].w = w; //The weight of the current edge is set to be w
    head[u] = cnt; //The first edge from u is set to be current edge
}
int d[MAX_NODE]; //Store the shortest path from the source to each vertex 
int n; //The number of nodes
int m; //The number of edges
int s; //The source of the path
int t; //The terminal of the path

class Node
{
public:
    int dis;
    int vertex;
    Node() = default; //ctor
    ~Node() = default; //detor
    Node(int a, int b)
    {
        dis = a; //The shortest distance
        vertex = b; //The identifier of the vertex
    }
    friend bool operator<(Node a, Node b)
    {
        return a.dis < b.dis;
    }
};

minHeap<Node, MAX_NODE> H; //Construct a Heap with struct Node as its key and max size is MAX_NODE

void dijkstra_with_minHeap(int start, int des) //Dijkstra algorithm to calculate the distance of the shortest path from the source to each node
{
    d[start] = 0; //Set the shortest path from the source to the source to be 0
    H.push(Node(0, s)); //Push the source to binary heap
    while (!H.empty()) //While the binary heap is not empty
    {
        int now = H.deletemin().vertex; //Delete and return the minimum vertex from binary heap
        if (now == des) //If the current vertex is end vertex
        {
            cout << "shortest distance: " << d[des] << endl; //Print out the result
            return; //Exit the function
        }
        if (vis[now]) //If the vertex is collected 
            continue; //Skip
        vis[now] = true; //Collect the minimum vertex
        for (int i = head[now]; i; i = edge[i].next) //Go through every edge from the current vertex
        {
            EDGE &e = edge[i];
            if (d[now] + e.w < d[e.to]) //If the shortest path through the current node to e.to is shorter than the shortest path to e.to having stored
            {
                d[e.to] = d[now] + edge[i].w; //Update the shortest distance of the path to e.to
                H.push(Node(d[e.to], e.to)); //Push the edge to binary heap
            }
        }
    }
}
int main()
{
	cout << "Reading graph..." <<endl;
    fstream FILE_in;
    FILE_in.open("E:/ADS/test1.txt", ios::in); //Open graph file to read in
    if (!FILE_in.is_open()) //If fail to open the graph file
    {
        cout << "Could not open the data file!" << endl; //Warning
        exit(EXIT_FAILURE); //An unsuccessful termination status is returned to the host environment
    }
    char flag;
    int u; //The head of an edge
    int v; //The tail of an edge
    int w; //The weight of an edge
    string temp;
    while (FILE_in >> flag)
    {
        if (flag == 'c') //If the line begins with 'c', it is a comment line
        {
            getline(FILE_in, temp); //It doesn't need to be read in to graph, so skip
        }
        else if (flag == 'p') //If the line begins with 'p'
        {
            FILE_in >> temp >> n >> m; //Read the identifier 'sp' into temp and read the number of nodes and edges of the graph into n an m respectively
        }
        else if (flag == 'a') //If the line begins with 'a'
        {
            FILE_in >> u >> v >> w; //Read the head, tail and weight of the current edge
            addedge(u, v, w); //Add the curent edges to the graph
        }
    }
    FILE_in.close(); //Close the graph file
    cout << "Please input the start vertex and end vertex." << endl;
    cout << "For example: 1 19260817" << endl;
    cin >> s >> t; //Read in the start vertex and end vertex
    for (int i = 0; i <= n; i++)
    {
        d[i] = INF; //Initialize the shortest distance to be INFINITY for each vertex
    }
    memset(vis, 0, sizeof(vis)); //Flag all the vertices to be not collected
    H.clear(); //Clear the binary heap
    start = clock(); 
    dijkstra_with_minHeap(s, t); //Calculate the distance of the shortest path from source to each node with Dijsktra algorithm
    stop = clock();
    duration = ((double)(stop - start)) / CLK_TCK; 
    cout << "ticks: " << (double)(stop - start) << endl;
    cout << "duration: " << duration << "sec" << endl;//print the duration
//    fstream FILE_out;
//    FILE_out.open("Result_of_all_node_by_minHeap2.txt", ios::trunc | ios::out);
//    if (!FILE_out.is_open())
//    {
//        cout << "Could not open the result file!" << endl;
//        exit(EXIT_FAILURE);
//    }
//    for (int i = 1; i <= n; i++)
//    {
//        FILE_out << d[i] << " ";
//    }
//    FILE_out.close();
//    cout << "The result of all node has been submitted in the file \"Result_of_all_node_by_minHeap2.txt\"" << endl;
    return 0;
}