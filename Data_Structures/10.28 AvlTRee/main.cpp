#include"AvlTree.h"
#include<iostream> 
#include<ctime>
using namespace std;

int main(){
	time_t begin,end;
    double ret;

    int n=10,k1=4,k2=6;
    AvlTree<int>t1;


    cout << endl;
    cout << "n占主导，k较小" << endl;
    begin=clock();
    n=100;k1=1;k2=2;
    cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=1000;k1=1;k2=2;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=10000;k1=1;k2=2;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();



    cout<< endl;
    cout<<"n占主导，k较大"<<endl;
    begin=clock();
    n=100;k1=1;k2=100;
    cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=1000;k1=1;k2=100;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=10000;k1=1;k2=100;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();



cout<< endl;
    cout<<"k占主导，n较小"<<endl;
    begin=clock();
    n=1000;k1=1;k2=2;
    cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=1000;k1=10;k2=20;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=1000;k1=100;k2=200;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();


cout<< endl;
    cout<<"K占主导，n较大"<<endl;
    begin=clock();
    n=10000;k1=1;k2=2;
    cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=10000;k1=10;k2=20;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();

    n=10000;k1=100;k2=200;
        cout<<"n= "<< n <<"k1="<< k1 <<"k2="<< k2 <<endl;
    for(int i=1;i<=n;i++){
        t1.insert(i);
    }
    begin=clock();
    t1.printWantedTree(k1,k2);
	end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"runtime:   "<<ret<<endl;
    t1.makeEmpty();



    return 0;
}