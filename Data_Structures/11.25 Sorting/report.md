# 排序算法类的实现 11.25

南子谦 3210104676 信息与计算科学
## 我的测试程序
```
#include"Sorting.h"
#include<time.h>

void printVector(vector<int>& v) {
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		cout << *it << " ";
	}
	cout << endl;
}

void CreateArray(vector<int> &temp,int Num,double p)//以p的比例有序，共有Num个元素
{
    int i,x,y,size1,size2;
    
    temp.clear();
        size1=0;
        size2=0;
        for (i = 0; i < (int)(10*Num*p); i+=10){
            temp.push_back(i + 1);//下标从0到(int)(Num*p)为从1开始公差为10的等差数列
        }
    
        for (; i < Num; i++){
        //在有序数列之间随机插入10*Num以内的数
        temp.insert(temp.begin()+rand() % temp.size() ,rand() % (10*Num)+1);
        }
}

int main(){
    time_t begin,end;
    double ret;
    vector<int> temp1,temp2;
    

	cout<<"Num=200000;p=0.01"<<endl;
    for(int i=1;i<=5;i++){
    cout<<"times:"<< i <<endl;
    CreateArray(temp1,200000,0.01);
    
    temp2=temp1;
    begin=clock();
    heapsort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"heapsort runtime:   "<<ret<<endl;

    temp2=temp1;
    begin=clock();
    quicksort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"quicksort runtime:   "<<ret<<endl;
    }
    




    cout<<"Num=200000;p=0.1"<<endl;
    for(int i=1;i<=5;i++){
    cout<<"times:"<< i <<endl;
    CreateArray(temp1,200000,0.1);
    
    temp2=temp1;
    begin=clock();
    heapsort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"heapsort runtime:   "<<ret<<endl;

    temp2=temp1;
    begin=clock();
    quicksort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"quicksort runtime:   "<<ret<<endl;
    }





    cout<<"Num=200000;p=0.9"<<endl;
    for(int i=1;i<=5;i++){
    cout<<"times:"<< i <<endl;
    CreateArray(temp1,200000,0.9);
    
    temp2=temp1;
    begin=clock();
    heapsort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"heapsort runtime:   "<<ret<<endl;

    temp2=temp1;
    begin=clock();
    quicksort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"quicksort runtime:   "<<ret<<endl;
    }





    cout<<"Num=200000;p=0.99"<<endl;
    for(int i=1;i<=5;i++){
    cout<<"times:"<< i <<endl;
    CreateArray(temp1,200000,0.99);
    
    temp2=temp1;
    begin=clock();
    heapsort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"heapsort runtime:   "<<ret<<endl;

    temp2=temp1;
    begin=clock();
    quicksort(temp2);
    end=clock();
    ret=double(end-begin)/CLOCKS_PER_SEC;
    cout<<"quicksort runtime:   "<<ret<<endl;
    }


    system("pause");
    return 0;
}
```

## 我的测试思路
### 得到目标有序度的数组
    我通过先向数组通过for函数插入 数据总量Num*有序率p 个数，然后通过``temp.insert(temp.begin()+rand() % temp.size() ,rand() % (10*Num)+1);``利用rand函数向剩下 Num（1-p）个空位插入最大值小于数据总量×公差的随机数，这便形成了一个有序度至少有 $$(1-p)^2-1+p$$ 的数组，最后根据do while循环筛选与目标有序率相差过大的数组，即可得到目标有序度的数组。
    由于do while循环可能在大量的数据下占用了过多资源，在上方代码中我没有展示出来。
### 得到排序时间
    生成目标数组后用time.h中的clock函数，在heapsort和quicksort前后进行计时，每一组不同的p重复进行5次实验，取时间平均值。

## 测试数据
```
Num=200000;p=0.01
times:1
heapsort runtime:   0.062
quicksort runtime:   0.025
times:2
heapsort runtime:   0.055
quicksort runtime:   0.042
times:3
heapsort runtime:   0.061
quicksort runtime:   0.024
times:4
heapsort runtime:   0.068
quicksort runtime:   0.03
times:5
heapsort runtime:   0.055
quicksort runtime:   0.026


Num=200000;p=0.1
times:1
heapsort runtime:   0.008
quicksort runtime:   0.002
times:2
heapsort runtime:   0.007
quicksort runtime:   0
times:3
heapsort runtime:   0.01
quicksort runtime:   0.001
times:4
heapsort runtime:   0.008
quicksort runtime:   0.001
times:5
heapsort runtime:   0.009
quicksort runtime:   0.001
Num=200000;p=0.9


times:1
heapsort runtime:   0.062
quicksort runtime:   0.008
times:2
heapsort runtime:   0.064
quicksort runtime:   0.015
times:3
heapsort runtime:   0.069
quicksort runtime:   0.007
times:4
heapsort runtime:   0.058
quicksort runtime:   0.008
times:5
heapsort runtime:   0.052
quicksort runtime:   0.013


Num=200000;p=0.99
times:1
heapsort runtime:   0.077
quicksort runtime:   0.008
times:2
heapsort runtime:   0.065
quicksort runtime:   0.008
times:3
heapsort runtime:   0.052
quicksort runtime:   0.016
times:4
heapsort runtime:   0.074
quicksort runtime:   0.009
times:5
heapsort runtime:   0.057
quicksort runtime:   0.018
```

## 关于quicksort的改进
课本中的quicksort已经考虑到取的pivot可能是数组中最大数或最小数的情况，最终导致quicksort与冒泡排序失去差别；于是它在认定pivot之前写了median3函数。而我能想到的改进方法便是不仅与最左边与最右边进行换位，加大换位的数量，进一步避免left,right与center是最大的三个数与最小的三个数的情况。因为五个数同时是数组中最小或最大的五个数概率更加渺小。
### 测试后的结果
```
Num=200000;p=0.01
times:1
heapsort runtime:   0.069
quicksort runtime:   0.035
times:2
heapsort runtime:   0.069
quicksort runtime:   0.031
times:3
heapsort runtime:   0.057
quicksort runtime:   0.03
times:4
heapsort runtime:   0.063
quicksort runtime:   0.035
times:5
heapsort runtime:   0.061
quicksort runtime:   0.035



Num=200000;p=0.1
times:1
heapsort runtime:   0.005
quicksort runtime:   0.003
times:2
heapsort runtime:   0.005
quicksort runtime:   0.006
times:3
heapsort runtime:   0.007
quicksort runtime:   0.005
times:4
heapsort runtime:   0.007
quicksort runtime:   0.003
times:5
heapsort runtime:   0.005
quicksort runtime:   0.003



Num=200000;p=0.9
times:1
heapsort runtime:   0.07
quicksort runtime:   0.118
times:2
heapsort runtime:   0.063
quicksort runtime:   0.1
times:3
heapsort runtime:   0.06
quicksort runtime:   0.083
times:4
heapsort runtime:   0.051
quicksort runtime:   0.088
times:5
heapsort runtime:   0.058
quicksort runtime:   0.087



Num=200000;p=0.99
times:1
heapsort runtime:   0.059
quicksort runtime:   0.101
times:2
heapsort runtime:   0.062
quicksort runtime:   0.112
times:3
heapsort runtime:   0.063
quicksort runtime:   0.104
times:4
heapsort runtime:   0.077
quicksort runtime:   0.116
times:5
heapsort runtime:   0.065
quicksort runtime:   0.112
```
事实上我多进行的判断比原本的排序更花时间。。。
## 小结
堆排序由于需要建堆运行时间普遍会比快速排序更慢，但是堆排序更加稳定。


