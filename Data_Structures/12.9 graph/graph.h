#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

/// @brief 邻接表的实现方式
/// @tparam Comparable 
template <typename Comparable>
class ListGraph{
public:

    /// @brief 给定定点数初始化图，将图的adj指针=new vector<VNode>
    /// @tparam Comparable 
    /// @param vernum 
    ListGraph(int vernum){
        //初始化表头结点的指针域
        VNode p1;
        adj.assign(vernum,p1);
        m_vernum=vernum;
    }

    ~ListGraph(){
        for(int i=0;i<m_vernum;i++)
            if(adj[i].firstarc!=nullptr)rdelete(adj[i].firstarc);
    }

    struct ArcNode{//边结点
        ArcNode(){
            adjvex=-1;
            nextarc=nullptr;
        }
        int adjvex;//该边所指向的顶点的位置
	    struct ArcNode * nextarc;//指向下一条边的指针
        Comparable info;//和边相关的信息
    };

    struct VNode{//顶点结点，有值与指向第一个边的指针
        Comparable value;
        struct ArcNode * firstarc;
    VNode(){
        firstarc=nullptr;
    }
    };





    /// @brief 输入所有顶点值
    /// @tparam Comparable 
    void SetVertex(){
        for(int i = 0; i<m_vernum; ++i){
        cout<<"请输入下标为"<<i<<"的顶点的值"<<endl;
		cin>> adj[i].value;//输入顶点值
        }
    }

    /// @brief 添加一条从下标v指向下标u，权值为x的边
    /// @tparam Comparable 
    /// @param v 
    /// @param u 
    /// @param x 
    void AddEdge(int v,int u, Comparable x){
        if(v<m_vernum && u<m_vernum){
            if(adj[v].firstarc==nullptr){
                adj[v].firstarc=new ArcNode;
                adj[v].firstarc->adjvex=u;
                adj[v].firstarc->info=x;
                adj[v].firstarc->nextarc=nullptr;
                m_arcnum++;
            }
            else{//头插法，新的边插头上
                ArcNode* p1=new ArcNode;//生成一个新的边结点*p1
                p1->adjvex=u;//邻接点序号为j
                p1->nextarc= adj[v].firstarc;
                adj[v].firstarc=p1;
                adj[v].firstarc->info=x;
                m_arcnum++;
            }
        }
    }
    
    void listVertexes(){
        for(int i=0;i<m_vernum;i++){
            cout <<"下标为"<<i<<"的顶点的值为"<<adj[i].value<<endl;
        }
    }

    void listEdges(){
        ArcNode * p1=adj[0].firstarc;
        for(int i=0;i<m_vernum;i++){
            p1=adj[i].firstarc;
            while(p1!=nullptr){
                cout<<"("<<i<<","<<p1->adjvex<<","<<p1->info<<")"<<endl;
                p1=p1->nextarc;
            }
            
        }
    }


    void rdelete(ArcNode* p){
        if(p->nextarc!=nullptr){
            rdelete(p->nextarc);
        }
        delete p;
        cout<<"yes!";
    }
    

private:
    int m_vernum=0,m_arcnum=0;//顶点总数与边总数
    vector<VNode> adj;
};






/// @brief 邻接矩阵的实现方式
/// @tparam Comparable 
template <typename Comparable>
class MatrixGraph{
public:
    MatrixGraph(int vernum){
        m_vernum=vernum;
        for(int i = 0; i<vernum;++i)//初始化邻接矩阵,边的权值均置为极大值
            for(int j = 0; j<vernum;++j)
                arcs[i][j]=IntMax;
    }

    ~MatrixGraph(){
    }

    void SetVertex(){
        adj.resize(m_vernum);
        for(int i = 0; i<m_vernum; ++i){
        cout<<"请输入下标为"<<i<<"的顶点的值"<<endl;
		cin>> adj[i];//输入顶点值
        }
    }
    
    void AddEdge(int v,int u, Comparable x){
        arcs[v][u]=x;
        m_arcnum++;
    }

    void listVertexes(){
        for(int i=0;i<m_vernum;i++){
            cout <<"下标为"<<i<<"的顶点的值为"<<adj[i]<<endl;
        }
    }

    void listEdges(){
        for(int i = 0; i<m_vernum;++i)
            for(int j = 0; j<m_vernum;++j)
                if(arcs[i][j]<IntMax) cout<<"("<<i<<","<<j<<","<<arcs[i][j]<<")"<<endl;
    }


private:
    int m_vernum=0,m_arcnum=0,IntMax=31000;//顶点总数与边总数
    Comparable  arcs[100][100];
    vector<Comparable>adj;
};










