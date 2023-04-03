#ifndef GRAPH_WITH_HEAPS_H
#define GRAPH_WITH_HEAPS_H

#include<vector>
#include <algorithm>
#include"FibonacciHeap.h"
#include"BinomialQueue.h"
#define INF 0x7fffffff

//***************************************

 //ListGraph class

 //构造函数: 0 参数

 //***********************类外部接口***********************
 //void SetVertex()                 --> 设置顶点的值
 //void AddEdge(int v,int u, Comparable x) --> 添加边
 //void AddEdge()               --> cin版本的添加边
 //void listVertexes()       --> 列出所有点值
 //void listEdges()      --> 列出所有边
 //vector<int>* dijkstra_with_FibonacciHeap(int src,vector<int>* dist) 
 //-->输入原点下标和空vector指针dist，用dijkstra计算单源最短路径存入dist,输出dist
 //void Print_shortest_distances(vector<int>* dist)   -->打印vector<int>* dist内容
 //void testListGraph()  -->一个完整的测试样例，只需在main函数创建一个图ListGraph<int> a(8);
/// @brief 邻接表的实现方式
/// @tparam Comparable是结点值与边值的类型 
template <typename Comparable, typename HeapType, typename HeapNode>
class ListGraph {
public:

    /// @brief 给定定点数初始化图，将图的adj指针=new vector<VNode>
    /// @tparam Comparable 
    /// @param vernum 
    ListGraph(int vernum) {
        //初始化表头结点的指针域
        adj.resize(vernum);
        m_vernum = vernum;
    }

    ~ListGraph() {
        for (int i = 0; i < m_vernum; i++)
            if (adj[i].firstarc != nullptr)rdelete(adj[i].firstarc);
    }

    struct ArcNode {//边结点
        ArcNode() {
            adjvex = -1;
            nextarc = nullptr;
        }
        ArcNode(int a, ArcNode* b, Comparable c) {
            adjvex = a;
            nextarc = b;
            info = c;
        }
        int adjvex;//该边所指向的顶点的位置
        ArcNode* nextarc;//指向下一条边的指针
        Comparable info;//和边相关的信息
    };

    struct VNode {//顶点结点，有值与指向第一个边的指针
        Comparable value = 0;
        ArcNode* firstarc = nullptr;
        HeapNode* m_HN = nullptr;
    };

    /// @brief 输入所有顶点值
    /// @tparam Comparable 
    void SetVertex() {

        for (int i = 0; i < m_vernum; ++i) {
            //cout<<"请输入下标为"<<i<<"的顶点的值(int)"<<endl;
            cin >> adj[i].value;//输入顶点值
            if (cin.fail()) {
                //cout << "您输入了错误的数据类型,默认值为0"<< endl;
                adj[i].value = 0;
            }
        }
    }

    /// @brief 添加一条从下标v指向下标u，权值为x的边
    /// @tparam Comparable 
    /// @param v 
    /// @param u 
    /// @param x 
    void AddEdge(int v, int u, Comparable x) {
        if (v < m_vernum && u < m_vernum) {
            if (adj[v].firstarc == nullptr) {
                adj[v].firstarc = new ArcNode(u, nullptr, x);
                m_arcnum++;
            }
            else {//头插法，新的边插头上
                ArcNode* p1 = new ArcNode(u, adj[v].firstarc, x);//生成一个新的边结点*p1,邻接点序号为j
                adj[v].firstarc = p1;
                m_arcnum++;
            }
        }
    }

    void AddEdge() {//cin version
        int v, u;
        Comparable x;
        cin >> v >> u >> x;
        if (v < m_vernum && u < m_vernum) {
            if (adj[v].firstarc == nullptr) {
                adj[v].firstarc = new ArcNode(u, nullptr, x);
                m_arcnum++;
            }
            else {//头插法，新的边插头上
                ArcNode* p1 = new ArcNode(u, adj[v].firstarc, x);//生成一个新的边结点*p1,邻接点序号为j
                adj[v].firstarc = p1;
                m_arcnum++;
            }
        }
    }

    void listVertexes() {
        for (int i = 0; i < m_vernum; i++) {
            cout << "下标为" << i << "的顶点的值为" << adj[i].value << endl;
        }
    }

    void listEdges() {
        ArcNode* p1 = adj[0].firstarc;
        for (int i = 0; i < m_vernum; i++) {
            p1 = adj[i].firstarc;
            while (p1 != nullptr) {
                cout << "(" << i << "," << p1->adjvex << "," << p1->info << ")" << endl;
                p1 = p1->nextarc;
            }

        }
    }


    void rdelete(ArcNode* p) {
        if (p->nextarc != nullptr) {
            rdelete(p->nextarc);
        }
        delete p;
        //cout<<"ArcNode deleted.  ";
    }


    void init_pairH_with_vector(HeapType& h, vector<int>* dist) {
        int i = 0;
        for (vector<int>::iterator it = dist[0].begin(); it != dist[0].end(); it++, i++) {
            adj[i].m_HN = h.Insert(make_pair(dist[0][i], i));
            //cout<<"Hnode insert succussful! "<< i<< endl;
            
        }
        //cout << h.GetMin()->GetElement().first << endl;
    }



    //element T应该是个ipair，分别存着结点下标t与路径长度x。
    //然后deletemin出一个节点放进s，松弛它的邻接顶点，然后继续deletemin。
    vector<int>* dijkstra(int src, vector<int>* dist) {
        // dist记录了原点src到所有其他点的最短距离
        //初始化时所有节点都放优先队列里，原点距离为0，与原点直接相连的有限，其余为INF；
        if (!dist[0].empty())
            dist[0].clear();
        dist[0].resize(m_vernum);
        dist[0].assign(m_vernum, INF);
        dist[0][src] = 0;

        HeapType h;
        init_pairH_with_vector(h, dist);//初始化堆，将所有结点信息插入堆，pair->first是其他点到原点的距离INF，second是其他点的下标


        /* 循环直到优先队列为空*/
        while (!h.Empty()) {

            int u = h.GetMin()->GetElement().second;
            //cout << u << " heap remaining  "<< h.getnum()<<endl;
            // 'while' is used to get all adjacent vertices of a vertex
            ArcNode* p1 = adj[u].firstarc;
            while (p1 != nullptr) {

                // v是在堆中Decrease所有和u相连的结点
                int v = p1->adjvex;
                int weight = p1->info;
                //cout<< v << " " << weight <<endl;
                // If there is shorted path to v through u.
                if (dist[0][v] > dist[0][u] + weight) {
                    // Updating distance of v
                    dist[0][v] = dist[0][u] + weight;
                    //cout << dist[0][v]<<endl;
                    h.DecreaseKey(adj[v].m_HN, make_pair(dist[0][v], v));
                    //h.printqueue();
                    //cout<<endl;
                    
                }
                p1 = p1->nextarc;
            }//end while
            h.DeleteMin();
        }//end while
        return dist;

    }



    void Print_shortest_distances(vector<int>* dist) {
        cout << "Vertex Distance from Source" << endl;
        for (int i = 0; i < m_vernum; ++i)
            cout << "Point " << i << " : " << dist[0][i] << endl;
    }

    /// @brief the Graph must have more than 7 nodes
    void testListGraph() {
        vector<int>* p1 = new vector<int>;
        AddEdge(0, 1, 1);
        AddEdge(1, 2, 1);
        AddEdge(2, 4, 1);
        AddEdge(4, 3, 3);
        AddEdge(3, 2, 1);
        AddEdge(1, 5, 4);
        AddEdge(1, 6, 4);
        AddEdge(5, 6, 5);
        AddEdge(6, 7, 4);
        AddEdge(5, 7, 3);
        listEdges();
        dijkstra(0, p1);
        Print_shortest_distances(p1);
        delete p1;
    }

private:
    int m_vernum, m_arcnum = 0;//顶点总数与边总数
    vector<VNode> adj;
};

#endif