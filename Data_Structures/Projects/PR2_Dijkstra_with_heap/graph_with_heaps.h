#ifndef GRAPH_WITH_HEAPS_H
#define GRAPH_WITH_HEAPS_H

#include<vector>
#include <algorithm>
#include"FibonacciHeap.h"
#include"BinomialQueue.h"
#define INF 0x7fffffff

//***************************************

 //ListGraph class

 //���캯��: 0 ����

 //***********************���ⲿ�ӿ�***********************
 //void SetVertex()                 --> ���ö����ֵ
 //void AddEdge(int v,int u, Comparable x) --> ��ӱ�
 //void AddEdge()               --> cin�汾����ӱ�
 //void listVertexes()       --> �г����е�ֵ
 //void listEdges()      --> �г����б�
 //vector<int>* dijkstra_with_FibonacciHeap(int src,vector<int>* dist) 
 //-->����ԭ���±�Ϳ�vectorָ��dist����dijkstra���㵥Դ���·������dist,���dist
 //void Print_shortest_distances(vector<int>* dist)   -->��ӡvector<int>* dist����
 //void testListGraph()  -->һ�������Ĳ���������ֻ����main��������һ��ͼListGraph<int> a(8);
/// @brief �ڽӱ��ʵ�ַ�ʽ
/// @tparam Comparable�ǽ��ֵ���ֵ������ 
template <typename Comparable, typename HeapType, typename HeapNode>
class ListGraph {
public:

    /// @brief ������������ʼ��ͼ����ͼ��adjָ��=new vector<VNode>
    /// @tparam Comparable 
    /// @param vernum 
    ListGraph(int vernum) {
        //��ʼ����ͷ����ָ����
        adj.resize(vernum);
        m_vernum = vernum;
    }

    ~ListGraph() {
        for (int i = 0; i < m_vernum; i++)
            if (adj[i].firstarc != nullptr)rdelete(adj[i].firstarc);
    }

    struct ArcNode {//�߽��
        ArcNode() {
            adjvex = -1;
            nextarc = nullptr;
        }
        ArcNode(int a, ArcNode* b, Comparable c) {
            adjvex = a;
            nextarc = b;
            info = c;
        }
        int adjvex;//�ñ���ָ��Ķ����λ��
        ArcNode* nextarc;//ָ����һ���ߵ�ָ��
        Comparable info;//�ͱ���ص���Ϣ
    };

    struct VNode {//�����㣬��ֵ��ָ���һ���ߵ�ָ��
        Comparable value = 0;
        ArcNode* firstarc = nullptr;
        HeapNode* m_HN = nullptr;
    };

    /// @brief �������ж���ֵ
    /// @tparam Comparable 
    void SetVertex() {

        for (int i = 0; i < m_vernum; ++i) {
            //cout<<"�������±�Ϊ"<<i<<"�Ķ����ֵ(int)"<<endl;
            cin >> adj[i].value;//���붥��ֵ
            if (cin.fail()) {
                //cout << "�������˴������������,Ĭ��ֵΪ0"<< endl;
                adj[i].value = 0;
            }
        }
    }

    /// @brief ���һ�����±�vָ���±�u��ȨֵΪx�ı�
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
            else {//ͷ�巨���µı߲�ͷ��
                ArcNode* p1 = new ArcNode(u, adj[v].firstarc, x);//����һ���µı߽��*p1,�ڽӵ����Ϊj
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
            else {//ͷ�巨���µı߲�ͷ��
                ArcNode* p1 = new ArcNode(u, adj[v].firstarc, x);//����һ���µı߽��*p1,�ڽӵ����Ϊj
                adj[v].firstarc = p1;
                m_arcnum++;
            }
        }
    }

    void listVertexes() {
        for (int i = 0; i < m_vernum; i++) {
            cout << "�±�Ϊ" << i << "�Ķ����ֵΪ" << adj[i].value << endl;
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



    //element TӦ���Ǹ�ipair���ֱ���Ž���±�t��·������x��
    //Ȼ��deletemin��һ���ڵ�Ž�s���ɳ������ڽӶ��㣬Ȼ�����deletemin��
    vector<int>* dijkstra(int src, vector<int>* dist) {
        // dist��¼��ԭ��src���������������̾���
        //��ʼ��ʱ���нڵ㶼�����ȶ����ԭ�����Ϊ0����ԭ��ֱ�����������ޣ�����ΪINF��
        if (!dist[0].empty())
            dist[0].clear();
        dist[0].resize(m_vernum);
        dist[0].assign(m_vernum, INF);
        dist[0][src] = 0;

        HeapType h;
        init_pairH_with_vector(h, dist);//��ʼ���ѣ������н����Ϣ����ѣ�pair->first�������㵽ԭ��ľ���INF��second����������±�


        /* ѭ��ֱ�����ȶ���Ϊ��*/
        while (!h.Empty()) {

            int u = h.GetMin()->GetElement().second;
            //cout << u << " heap remaining  "<< h.getnum()<<endl;
            // 'while' is used to get all adjacent vertices of a vertex
            ArcNode* p1 = adj[u].firstarc;
            while (p1 != nullptr) {

                // v���ڶ���Decrease���к�u�����Ľ��
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
    int m_vernum, m_arcnum = 0;//���������������
    vector<VNode> adj;
};

#endif