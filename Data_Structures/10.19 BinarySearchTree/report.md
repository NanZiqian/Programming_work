# BST 排序算法的实现
信息与计算科学 南子谦
October 19 2022

## 写在前面-我的感想
> 我们创建BinarySearchTree类时，若要创建指针，则应该手动new一个空间出来，并且在程序结尾delete；千万不能不new就用了，因为它不想直接创建实例会在栈区给你分配空间，单单一个指针将是没有操作权限的野指针，当执行到和该指针相关的操作的时候程序就会崩溃！
> 课本代码给我最大的其实就是对私有属性的严格控制，既然私有属性在类外调用公开函数的时候不能访问，就应该在类内定义函数的时候用接口函数内调用完毕。
> 另一点我的感想是，写迭代函数的时候，首先应该想的是什么时候函数会不再迭代，而是return，并且写在最前面。

---

## 我的main.cpp（包括main函数和BSTSorting函数）
> 我创建了两个vector变量v1v2，数据都是从10到1的倒计时，一个用于不无序排序，一个用于无序排序。
> 我的BSTSorting函数用到了两个函数，一个是AddToTree函数，我在main.cpp中也进行了定义，功能是把vector的所有数据insert入二叉树；另一个是在头文件中BinarySearchTree类下的公开CreateVector函数，用于将二叉树的数据遍历并存储于v_global数组中，由于遍历是递归函数，我的v_global是个全局数组，这可以用遍历的非递归形式避免。
> v1原本是倒计时的数据，main函数中我还把乱序后的v2进行了输出，它们分别与最后我v1和v2的输出进行了对比。
```
#include"BinarySearchTree.h"


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
        ;//乱序操作，并进行输出
        for (vector<int>::iterator it = _arr.begin(); it != _arr.end(); it++) {
		cout << *it << " " ;
        }
        cout <<"左为乱序后的v2"<< endl;
    }
    BinarySearchTree<Comparable> T1;
    AddToTree(T1,_arr);
    _arr=T1.CreateVector();
    T1.makeEmpty();
}

int main(){
    vector<int> v1,v2;
    for (int i = 10; i > 0; i--)//输入一个倒序的数组
	{
		v1.push_back(i);
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
```

##我的测试结果
```
10 9 8 7 6 5 4 3 2 1
2 9 1 8 10 5 3 7 6 4 左为乱序后的v2
1 2 3 4 5 6 7 8 9 10 左为v1
1 2 3 4 5 6 7 8 9 10 左为v2
```

## 我的内存泄漏检查
> 无内存泄漏
```
FINAL SUMMARY:

DUPLICATE ERROR COUNTS:
	Error #   1:      5
	Error #   2:      5

SUPPRESSIONS USED:

ERRORS FOUND:
      0 unique,     0 total unaddressable access(es)
      3 unique,    11 total uninitialized access(es)
      0 unique,     0 total invalid heap argument(s)
      0 unique,     0 total GDI usage error(s)
      0 unique,     0 total handle leak(s)
      0 unique,     0 total warning(s)
      0 unique,     0 total,      0 byte(s) of leak(s)
      0 unique,     0 total,      0 byte(s) of possible leak(s)
ERRORS IGNORED:
      1 potential error(s) (suspected false positives)
         (details: C:\Users\XXAlexMasonXX\AppData\Roaming\Dr. Memory\DrMemory-main.exe.9448.000\potential_errors.txt)
      7 unique,     7 total,   1193 byte(s) of still-reachable allocation(s)
         (re-run with "-show_reachable" for details)
Details: C:\Users\XXAlexMasonXX\AppData\Roaming\Dr. Memory\DrMemory-main.exe.9448.000\results.txt
```