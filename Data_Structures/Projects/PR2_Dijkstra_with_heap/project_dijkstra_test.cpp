#include<iostream>
#include<fstream>
#include<ctime>
#include<string.h>
#include"graph_with_heaps.h"

struct edge     //输入的边结构，分别为起始节点，末节点和边权值
{
    int node1,node2;
    int dis;

    edge():node1{0},node2{0},dis{0} {}
};

int main(int argc,char** argv)      //需输入文件名，如.\project_dijkstra_test.exe Square-n.20.0.gr Square-n.20.0.ss
{
    using namespace std;
    ifstream grin;      //打开.gr
    ifstream ssin;      //打开.ss
    char ch;        //读入字符
    int num_node,num_arc;
    ofstream fout("time.txt",ios::out|ios::app);        //打开记录时间的文件
    int num_source_line;
    int node;
    clock_t start_1,end_1;
    vector<int>* p1=new vector<int>;
//从文件输入图
    grin.open(argv[1]);
    grin.get(ch);
    while(ch!='\n')
    {
        if(ch=='c')
            while(ch!='\n')
                grin.get(ch);
        else if(ch=='p')
        {
            for(int i=0;i<4;i++)
                grin.get(ch);
            grin>>num_node>>num_arc;
            grin.get(ch);
            break;
        }
        grin.get(ch);
    }
    ListGraph<int> gra(num_node);
    edge eg;
    grin.get(ch);
    while(ch!='\n')
    {
        if(ch=='c')
            while(ch!='\n')
                grin.get(ch);
        else if(ch=='a')
        {
            grin.get(ch);
            grin>>eg.node1>>eg.node2>>eg.dis;
            gra.AddEdge(eg.node1,eg.node2,eg.dis);
            grin.get(ch);
        }
        grin.get(ch);
    }
    grin.close();
//从文件输入图
//从文件输入需求最短路径的点
    ssin.open(argv[2]);
    
    ssin.get(ch);
    while(ch!='\n')
    {
        if(ch=='c')
            while(ch!='\n')
                ssin.get(ch);
        else if(ch=='p')
        {
            for(int i=0;i<11;i++)
                ssin.get(ch);
            ssin>>num_source_line;
            ssin.get(ch);
            break;
        }
        ssin.get(ch);
    }
    
    ssin.get(ch);
    while(ch!='\n')
    {
        if(ch=='c')
            while(ch!='\n')
                ssin.get(ch);
        else if(ch=='s')
        {
            ssin.get(ch);
            ssin>>node;
            start_1=clock();
            gra.dijkstra_with_FibonacciHeap(node,p1);
            end_1=clock();
            double time=1.0*(end_1-start_1)/CLOCKS_PER_SEC;
            fout<<num_node<<" "<<num_arc<<" "<<time<<endl;
            ssin.get(ch);
        }
        ssin.get(ch);
    }
    ssin.close();
//从文件输入需求最短路径的点
    delete p1;
    std::system("pause");
    return 0;
}