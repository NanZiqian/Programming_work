#ifndef LIST_GRAPH
#define LIST_GRAPH

#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
using namespace std;

//***************************************

 //ListGraph class

 //构造函数: 0 参数

 //***********************类外部接口***********************
 //void SetVertex()                 --> 设置顶点的值
 //void AddEdge(int v,int u, Comparable x) --> 添加边
 //void AddEdge()               --> cin版本的添加边
 //void listVertexes()       --> 列出所有点值
 //void listEdges()      --> 列出所有边
/// @brief 邻接表的实现方式
/// @param Comparable是结点值与边值的类型 
template <typename Comparable>
class ListGraph {
public:

    /// @brief 给定定点数初始化图，将图的adj指针=new vector<VNode>
    /// @tparam Comparable 
    /// @param vernum 
    ListGraph(){
        adj.resize(1);
        adj[0].firstarc=nullptr;
        m_vernum=1;
        m_arcnum = 0;
    }

    ListGraph(int vernum) {
        //初始化表头结点的指针域
        adj.resize(vernum);
        m_vernum = vernum;
        m_arcnum = 0;
    }

    ~ListGraph() {
        makeEmpty();
    }

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

    /// @brief 添加一条从下标v指向下标u，权值为x的边；即有向图
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

    //将图清空，然后重置结点数，结点.value=x firstarc=nullptr
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

    void testListGraph(){//创建一个至少有8个节点的图
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

    struct ArcNode {//边结点
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
        int adjvex;//该边所指向的顶点的位置
        ArcNode* nextarc;//指向下一条边的指针
        Comparable info;//和边相关的信息
    };

    struct VNode {//顶点结点，有值与指向第一个边的指针
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

    int m_vernum, m_arcnum;//顶点总数与边总数
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