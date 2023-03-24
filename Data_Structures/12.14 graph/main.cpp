#include"graph.h"
#include<time.h>

void testListGraph(){
    double* dist;
    ListGraph<int> a(7);
    a.SetVertex();
    a.AddEdge(0,1,1);
    a.AddEdge(1, 2, 1);
    a.AddEdge(2, 4, 1);
    a.AddEdge(4, 3, -3);
    a.AddEdge(3, 2, 1);
    a.AddEdge(1, 5, 4);
    a.AddEdge(1, 6, 4);
    a.AddEdge(5, 6, 5);
    a.AddEdge(6, 7, 4);
    a.AddEdge(5, 7, 3);
    a.listEdges();
    dist=a.bellmanFord(0);
    for(int i=0;i<7;i++){
        cout<<"从顶点0到顶点"<<i<<"的最短路径为："<<dist[i]<<endl;
    }
    delete dist;
}

void testtime(int x){//x*n=边数
    double* dist;
    clock_t start,end;

    ListGraph<int> a(10000);
    a.SetVertex();
    for(int j=1;j<=x;j++)
        for(int i=0;i<10000;i++)
            a.AddEdge(i,(i+j)%10000,i);//j必须<n，j_max*i_max必须<n*(n-1)/2，n为边数

    start=clock();

    dist=a.bellmanFord(0);
    delete dist;
    dist=a.bellmanFord(5000);
    delete dist;
    dist=a.bellmanFord(10000);
    end=clock();
    cout<<"n=10000,x="<<x<<"的耗时为："<<(double)(end-start)/CLOCKS_PER_SEC/3<<endl;
    delete dist;
}

int main(){
    testtime(2000);
    testtime(3000);
    testtime(4000);
    testtime(5000);
    testtime(6000);
    testtime(7000);
    testtime(8000);
    system("pause");
    return 0;
}

