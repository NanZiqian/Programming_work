#include"graph.h"

void testListGraph(){
    ListGraph<int> a(10);
    a.SetVertex();
    a.AddEdge(0,1,2);
    a.AddEdge(0,2,2);
    a.listVertexes();
    a.listEdges();
}

void testMatrixGraph(){
    MatrixGraph<int> a(10);
    a.SetVertex();
    a.AddEdge(0,1,2);
    a.listVertexes();
    a.listEdges();
}

int main(){
    cout<<"testListGraph"<<endl;
    testListGraph();
    cout<<"testMatrixGraph"<<endl;
    testMatrixGraph();
    system("pause");
    return 0;
}