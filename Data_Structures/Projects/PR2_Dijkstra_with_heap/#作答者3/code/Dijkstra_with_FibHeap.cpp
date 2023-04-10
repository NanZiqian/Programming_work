#include <iostream>
#include <utility>
#include <fstream>
#include <cmath>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "Fib_Heap.hpp"
using namespace std;
#define INF 0x7fffffff
#define MAX_NODE 23950000
#define MAX_EDGE 58340000
clock_t start, stop; //tools for timing test
double duration; //tools for timing test
struct EDGE
{
    int to, w, next;//"to" is the tail of the edge, while "w" is the weight of the edge
} edge[MAX_EDGE];
int head[MAX_NODE], cnt = 0; //"cnt" is the number of edges added to the graph
bool vis[MAX_NODE]; //flag if each node is collected
inline void addedge(int u, int v, int w) //Add the current edge to the graph
{
    edge[++cnt].to = v; //the number of edges+1 and set the end of  the edge to be v
    edge[cnt].next = head[u]; //the next the edge from u is linked to the current edge from u
    edge[cnt].w = w; //the weight of the current edge is set to be w
    head[u] = cnt; //the first edge from u is set to be current edge
}
int d[MAX_NODE];
int t; //the destination
int n; //the number of nodes
int m; //the number of edges
int s; //the source
class Node //node structrue of graph
{
public:
    int dis; //distance
    int vertex; //vertex num
    Node() = default; //make node
    ~Node() = default; //clear node
    Node(int a, int b) //make a new node with "a" as its dis and "b" as its vertex
    {
        dis = a;
        vertex = b;
    }
    friend bool operator<(Node a, Node b)//compare dis of a and b
    {
        return a.dis < b.dis; //if a < b, return true
    }
};
FibHeap<Node> H; //build a FibHeap H with Node
void dijkstra_with_Fib_Heap(int start, int des) //Dijkstra algorithm to calculate the distance of the shortest path from the source to each node
{
    d[start] = 0;
    H.Insert(Node(0, s));
    while (!H.isEmpty()) //While the Fibonacci heap is not null
    {
        int now = H.DeleteMin().vertex; //Delete and return the minimum node from Fibonacci heap
        if (now == des) //if already reach the destination
        {
            cout << "shortest distance: " << d[des] << endl;//print the minimum path it calculates
            return;//end the dijksta function
        }
        if (vis[now])//If the node is collected
            continue; //Skip
        vis[now] = true; //Collect the minimum node
        for (int i = head[now]; i; i = edge[i].next) //Go through every edge from the current edge
        {
            EDGE &e = edge[i];
            if (d[now] + e.w < d[e.to])//If the shortest path through the current node to e.to is shorter than the shortest path to e.to having stored
            {
                d[e.to] = d[now] + edge[i].w;//Update the shortest distance to e.to
                H.Insert(Node(d[e.to], e.to));//Push the edge to min-heap
            }
        }
    }
}
int main()
{
	cout << "Reading graph..." <<endl;
    fstream FILE_in;
    FILE_in.open(/*"Sample_Data.gr" "easy_test.txt"*/"USA-road-d.USA.gr", ios::in);//Open graph file to read in
    if (!FILE_in.is_open())//If fail to open the graph file
    {
        cout << "Could not open the data file!" << endl; //Warning
        exit(EXIT_FAILURE); //exit program
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
    cin >> s >> t;
    for (int i = 0; i <= n; i++)
    {
        d[i] = INF;
    }
    memset(vis, 0, sizeof(vis));
    start = clock(); //record the beginning time of dijkstra function
    dijkstra_with_Fib_Heap(s, t); //Calculate the distance of the shortest path from source to each node with Dijsktra algorithm
    stop = clock(); //record the endding time of dijkstra function
    duration = ((double)(stop - start)) / CLK_TCK; //calculate the duration for running dijkstra function
    cout << "ticks: " << (double)(stop - start) << endl;
    cout << "duration: " << duration << "sec" << endl;//print the duration
    /*
    fstream FILE_out;
    FILE_out.open("Result_of_all_node_by_minHeap2.txt", ios::out);
    if (!FILE_out.is_open())
    {
        cout << "Could not open the result file!" << endl;
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= n; i++)
    {
        FILE_out << d[i] << " ";
    }
    FILE_out.close();
    */
    return 0;
}
