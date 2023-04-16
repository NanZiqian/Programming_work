#ifndef LIST_GRAPH
#define LIST_GRAPH

#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
using namespace std;

//***************************************

 //ListGraph class

 //���캯��: 0 ����

 //***********************���ⲿ�ӿ�***********************
 //void SetVertex()                 --> ���ö����ֵ
 //void AddEdge(int v,int u, Comparable x) --> ��ӱ�
 //void AddEdge()               --> cin�汾����ӱ�
 //void listVertexes()       --> �г����е�ֵ
 //void listEdges()      --> �г����б�
/// @brief �ڽӱ��ʵ�ַ�ʽ
/// @param Comparable�ǽ��ֵ���ֵ������ 
template <typename Comparable>
class ListGraph {
public:

    /// @brief ������������ʼ��ͼ����ͼ��adjָ��=new vector<VNode>
    /// @tparam Comparable 
    /// @param vernum 
    ListGraph(){
        adj.resize(1);
        adj[0].firstarc=nullptr;
        m_vernum=1;
        m_arcnum = 0;
    }

    ListGraph(int vernum) {
        //��ʼ����ͷ����ָ����
        adj.resize(vernum);
        m_vernum = vernum;
        m_arcnum = 0;
    }

    ~ListGraph() {
        makeEmpty();
    }

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

    /// @brief ���һ�����±�vָ���±�u��ȨֵΪx�ıߣ�������ͼ
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
        }else
            cout << v << u << x << "AddEgde error!!";
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
        ArcNode* p1;
        for (int i = 0; i < m_vernum; i++) {
            p1 = adj[i].firstarc;
            while (p1 != nullptr) {
                cout << "(" << i << "," << p1->adjvex << "," << p1->info << ")" << endl;
                p1 = p1->nextarc;
            }

        }
    }

    void listEdges_ofnode(const int& u){
        
        int sum=0;
    //find out how many edges do node"u" have
        ArcNode* p1 = adj[u].firstarc;
        while (p1 != nullptr) {
            sum++;
            p1 = p1->nextarc;
            if(p1 == nullptr)
                break;
        }
        cout << "There are " << sum <<" exits:";
    //list them
        int x=sum;
        p1 = adj[u].firstarc;
        while (p1 != nullptr) {
            x--;
            if(x>1)
                cout << " " << p1->info <<",";
            else if(x==1)
                cout << " " << p1->info;
            else if(x==0)
                cout << " and " << p1->info <<"." << endl;
            p1 = p1->nextarc;
        }
    }

    int find_edge(int index,Comparable x){
        return find_edge(adj[index].firstarc,x);
    }

    //��ͼ��գ�Ȼ�����ý���������.value=x firstarc=nullptr
    void resize(int vernum , Comparable && x){
        makeEmpty();
        adj.resize(vernum);
        VNode a(x);
        adj.assign(vernum,a);
        m_vernum = vernum;
        m_arcnum = 0;
    }

    Comparable getVnode_value(int & index){
        return adj[index].value;
    }

    void alterVnode_value(int & index , Comparable && x){
        adj[index].value=x;
    }

    void testListGraph(){//����һ��������8���ڵ��ͼ
        AddEdge(0,1,1);
        AddEdge(1, 2, 1);
        AddEdge(2, 4, 1);
        AddEdge(4, 3, -3);
        AddEdge(3, 2, 1);
        AddEdge(1, 5, 4);
        AddEdge(1, 6, 4);
        AddEdge(5, 6, 5);
        AddEdge(6, 7, 4);
        AddEdge(5, 7, 3);
        listEdges();
    }

private:

    struct ArcNode {//�߽��
        ArcNode() {
            adjvex = -1;
            nextarc = nullptr;
        }
        ArcNode(int a, ArcNode* b, Comparable & c) {
            adjvex = a;
            nextarc = b;
            info = c;
        }
        ArcNode(int a, ArcNode* b, Comparable && c) {
            adjvex = a;
            nextarc = b;
            info = c;
        }
        int adjvex;//�ñ���ָ��Ķ����λ��
        ArcNode* nextarc;//ָ����һ���ߵ�ָ��
        Comparable info;//�ͱ���ص���Ϣ
    };

    struct VNode {//�����㣬��ֵ��ָ���һ���ߵ�ָ��
        Comparable value;
        ArcNode* firstarc;
        VNode(){
            
            firstarc = nullptr;
        }
        VNode(Comparable & X){
            value = X;
            firstarc = nullptr;
        }
        VNode(Comparable && X){
            value = X;
            firstarc = nullptr;
        }
    };

    int m_vernum, m_arcnum;//���������������
    vector<VNode> adj;

    void rdelete(ArcNode* p) {
        if (p->nextarc != nullptr) {
            rdelete(p->nextarc);
        }
        delete p;
        //cout<<"ArcNode deleted.  ";
    }

    int find_edge(ArcNode* p,Comparable x) {

        if (p->info!=x && p->nextarc != nullptr) {
            return find_edge(p->nextarc,x);
        }else if(p->info==x)
            return p->adjvex;
        else if(p->nextarc == nullptr)
            return -1;
        

    }

    void makeEmpty(){
        for (int i = 0; i < m_vernum; i++){
            if (adj[i].firstarc != nullptr){
                rdelete(adj[i].firstarc);
                adj[i].firstarc = nullptr;
            }
        }
    }

    
};

#endif