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
        adj.resize(m_vernum);
        for(int i = 0; i<m_vernum; ++i){
            //cout<<"请输入下标为"<<i<<"的顶点的值(int)"<<endl;
            cin>> adj[i].value;//输入顶点值
            if(cin.fail()){
                //cout << "您输入了错误的数据类型,默认值为0"<< endl;
                adj[i].value=0;
            }
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
        //cout<<"ArcNode deleted.  ";
    }
    
    /// @brief bellmanFord算法寻找单源最短路径
    /// @param start 
    /// @return 
    double * bellmanFord(int start){
        //将存放最短路径的数组初始化
        double* dist = new double[m_vernum];
        for(int i=0;i<m_vernum;i++) *(dist+i)=214748364;
        dist[start] = 0;
    //最坏情况需要进行v-1次才能完成，若存在relaxedAnEdge=false结束循环，说明已经提前达成了放松
        bool relaxedAnEdge = true;

    //把所有顶点的边都进行放松
    ArcNode * p1=adj[0].firstarc;;
    for (int v = 0; v < m_vernum - 1 && relaxedAnEdge; v++) {
        relaxedAnEdge = false;
        for(int i=0;i<m_vernum;i++){
            p1=adj[i].firstarc;
            while(p1!=nullptr){
                if (dist[i] + p1->info < dist[p1->adjvex]) {
                    dist[p1->adjvex] = dist[i] + p1->info;
                    relaxedAnEdge = true;
                }
                p1=p1->nextarc;
            } 
        }
    }

    // Run algorithm a second time to detect which nodes are part
    // of a negative cycle. A negative cycle has occurred if we
    // can find a better path beyond the optimal solution.
    relaxedAnEdge = true;
    for (int v = 0; v < m_vernum - 1 && relaxedAnEdge; v++) {
        relaxedAnEdge = false;
        for(int i=0;i<m_vernum;i++){
            p1=adj[i].firstarc;
            while(p1!=nullptr){
                if (dist[i] + p1->info < dist[p1->adjvex]) {
                    dist[p1->adjvex] = -214748364;
                    relaxedAnEdge = true;
                }
                p1=p1->nextarc;
            } 
        }
    }
    return dist;
    }



private:
    int m_vernum=0,m_arcnum=0;//顶点总数与边总数
    vector<VNode> adj;
};
