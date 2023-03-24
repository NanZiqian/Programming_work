#include"DoubleLinkedList.h"

static List<int>::const_iterator& find(const List<int>& L,int x){
    static List<int>::const_iterator itr;
    int i=1;
    for (itr = L.begin();itr != L.end();itr++,i++){
        if(*itr==x){
            cout << "已找到在第" << i << "个节点" << endl;
            return itr;
        }
    }
    if(itr == L.end()){
        cout << "未找到" << endl;
        static List<int>::const_iterator l = L.begin();
        return l;
    }
}

void printall(const List<int>& L){
    for (List<int>::const_iterator itr = L.begin();itr != L.end();itr++){
        cout << *itr << " ";
    }
    if(L.size()==0)cout <<"无节点";
    cout << endl;
}

int main(){
    
    List<int>l1;
    List<int>::const_iterator itr=l1.begin();
    l1.push_front(10);
    l1.push_front(20);
    l1.push_front(30);
    cout << "l1有几个元素?" << l1.size() << endl;
    cout << "l1是否是空的?" << l1.empty() <<endl;
    find(l1,10);

    List<int>::iterator it=l1.begin();
    l1.insert(it,30);
    cout << "l1有几个元素?" << l1.size() << endl;
    printall(l1);
    find(l1,10);

    l1.erase(l1.begin(),l1.end());
    cout << "已清除" << endl;
    cout << "l1有几个元素?" << l1.size() << endl;
    printall(l1);

    return 0;
}