#include"BinarySearchTree.h"
#include<algorithm>


    /// @brief 将数组中的内容全部加入二叉树中
    /// @param T 
    /// @param v 
    void AddToTree(BinarySearchTree<int> &T,vector<int>& v){
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		T.insert(*it);
	}
}


template <typename Comparable>
void BSTSorting(vector<Comparable> &_arr, int _mode = 0){
    if(_mode){
        random_shuffle(_arr.begin(),_arr.end());//乱序操作，并进行输出
        for (vector<int>::iterator it = _arr.begin(); it != _arr.end(); it++) {
		cout << *it << " " ;
        }
        cout <<"左为乱序后的v2"<< endl;
    }
    BinarySearchTree<Comparable> T1;
    AddToTree(T1,_arr);
    _arr=T1.CreateVector();
    T1.makeEmpty();
    v_global.clear();
}

int main(){
    vector<int> v1,v2;
    int j=0;
    for (int i = 10; i > 0; i--)//输入一个倒序的数组
	{
		scanf("%d",&j);
        v1.push_back(j);
	}
    v2=v1;
    BSTSorting(v1);
    BSTSorting(v2,1);
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++) {
		cout << *it << " " ;
	}
    cout <<"左为v1"<< endl;
    for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++) {
		cout << *it << " " ;
	}
    cout <<"左为v2"<< endl;

    return 0;
}