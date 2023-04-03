#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include<cmath>
#include<iostream>
#include<vector>
using namespace std;

//FibonacciNode class

//构造函数: 0 参数 或 1 参数

//***********类外部接口******************
// void GetElement( )  --> 返回节点元素
//***************************************

 //FibonacciHeap class

 //构造函数: 0 参数

 //***********************类外部接口***********************
 //bool Empty( )                 --> 判断堆是否为空
 //FibonacciNode<T>* Insert( d ) --> 插入元素d返回节点指针
 //void Merge( h )               --> 合并调用的堆和堆h
 //FibonacciNode<T>* DeleteMin( )--> 删除最小节点并返回
 //void DecreaseKey( x,d )       --> 降低节点x的值为d
 //FibonacciNode* GetMin( )      --> 返回最小节点指针
 //*************************错误***************************
 //DecreaseKey中当新的值比原有的值大时报错


//FibonacciHeap的声明
template<typename T>
class FibonacciHeap;

//节点类定义
template<typename T>
class FibonacciNode
{
private:
	//节点成员属性
	T element;
	FibonacciNode* parent;//父节点
	FibonacciNode* left;//左节点
	FibonacciNode* right;//右节点
	FibonacciNode* child;//子节点
	int degree;//节点的度，即孩子个数
	int mark;//1代表在deletemin过程中只失去过一个孩子

	//友元类声明
	friend class FibonacciHeap<T>;

public:
	//含参构造包括左值和右值版本
	FibonacciNode(const T& d = T{ })
		:element{ d }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, child{ nullptr }, degree{ 0 }, mark{ 0 } {}
	FibonacciNode(T&& d = T{ })
		:element{ move(d) }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, child{ nullptr }, degree{ 0 }, mark{ 0 } {}
	//析构函数
	~FibonacciNode()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		child = nullptr;
	}

	T GetElement()const
	{
		return this->element;
	}
};

template<typename T>
class FibonacciHeap
{
private:
	//堆的成员属性
	FibonacciNode<T>* min;//指向堆最小节点
	int num;//记录堆节点数

	//私有成员函数，被deletemin调用，用于合并根节点链表
	void consolidate()
	{
		int max = ceil(log(this->num) / log(1.5)) + 1;
		vector<FibonacciNode<T>*> arr(max, nullptr);
		//遍历根节点链表
		FibonacciNode<T>* i = this->min;
		FibonacciNode<T>* final = i->left;
		while (i != final)
		{
			FibonacciNode<T>* x = i;
			i = i->right;
			int d = x->degree;
			if (arr[d] == x)
			{
				continue;
			}
			//当度相同时合并两个树
			while (arr[d] != nullptr)
			{
				FibonacciNode<T>* y = arr[d];
				//y元素比x小时，交换x和y
				if (y->element < x->element)
				{
					FibonacciNode<T>* t = x;
					x = y;
					y = t;
				}
				//从根节点链表中删除y
				y->left->right = y->right;
				y->right->left = y->left;
				//将y插入x的子节点链表中
				y->parent = x;
				if (x->child == nullptr)
				{
					x->child = y;
					y->right = y;
					y->left = y;
				}
				else
				{
					y->left = x->child;
					x->child->right->left = y;
					y->right = x->child->right;
					x->child->right = y;
				}
				//更新x的度
				x->degree++;
				//更新y的标记
				y->mark = 0;
				arr[d] = nullptr;
				d = d + 1;
			}
			arr[d] = x;
		}
		//final的最后一遍循环
		FibonacciNode<T>* x = i;
		int d = x->degree;
		//当度相同时合并两个树
		if (arr[d] != x)
		{
			while (arr[d] != nullptr)
			{
				FibonacciNode<T>* y = arr[d];
				//y元素比x小时，交换x和y在根节点链表中的位置
				if (y->element < x->element)
				{
					FibonacciNode<T>* t = x;
					x = y;
					y = t;
				}
				//从根节点链表中删除y
				y->left->right = y->right;
				y->right->left = y->left;
				//将y插入x的子节点链表中
				y->parent = x;
				if (x->child == nullptr)
				{
					x->child = y;
					y->right = y;
					y->left = y;
				}
				else
				{
					y->left = x->child;
					x->child->right->left = y;
					y->right = x->child->right;
					x->child->right = y;
				}
				//更新x的度
				x->degree++;
				//更新y的标记
				y->mark = 0;
				arr[d] = nullptr;
				d = d + 1;
			}
			arr[d] = x;
		}
		//遍历根节点链表寻找最小节点
		final = x;
		i = final->right;
		while (i != final)
		{
			if (i->element < this->min->element)
			{
				this->min = i;
			}
			i = i->right;
		}
		if (i->element < this->min->element)
		{
			this->min = i;
		}
	}

	//私有成员函数，被decreasekey调用，用于将y的子节点x移动到根节点链表
	void Cut(FibonacciNode<T>* x, FibonacciNode<T>* y)
	{
		//从y的子节点链表中删除x
		x->left->right = x->right;
		x->right->left = x->left;
		//更新y的子节点
		if (x->right == x)
		{
			y->child = nullptr;
		}
		else
		{
			y->child = x->right;
		}
		//更新y的度
		y->degree--;
		//更新x的父节点
		x->parent = nullptr;
		//更新x的标记
		x->mark = 0;
		//将x插入根链表
		x->left = this->min;
		this->min->right->left = x;
		x->right = this->min->right;
		this->min->right = x;
		return;
	}

	//私有成员函数，被decreasekey调用，用于递归更新mark，并根据标记决定是否cut
	void CascadingCut(FibonacciNode<T>* y)
	{
		FibonacciNode<T>* z = y->parent;
		if (z != nullptr)
		{
			if (y->mark == 0)
			{
				y->mark = 1;
			}
			else
			{
				this->Cut(y, z);
				this->CascadingCut(z);
			}
		}
		return;
	}

public:
	//默认构造，初始化堆
	FibonacciHeap() :min{ nullptr }, num{ 0 } {};
	//析构函数
	~FibonacciHeap()
	{
		while (!Empty())
		{
			delete this->DeleteMin();
		}
	}

	//空堆判断，若为空堆返回true，否则返回false
	bool Empty()
	{
		return this->num == 0;
	}

	//向堆中插入元素,同时返回新节点的指针
	FibonacciNode<T>* Insert(const T& d)
	{
		//分配空间，创建节点
		FibonacciNode<T>* x = new FibonacciNode<T>{ d };
		if (this->min == nullptr)
		{
			//空堆则建一个单节点的双向循环根链表
			x->left = x;
			x->right = x;
			this->min = x;
		}
		else
		{
			//将新节点插入双向循环根链表
			x->left = this->min;
			this->min->right->left = x;
			x->right = this->min->right;
			this->min->right = x;
			//调整堆最小节点
			if (x->element < this->min->element)
			{
				this->min = x;
			}
		}
		//更新节点数
		this->num++;
		return x;
	}

	//合并堆
	void Merge(const FibonacciHeap& h)
	{
		//处理空堆
		if (h.min == nullptr)
		{
			return;
		}
		else if (this->min == nullptr)
		{
			this->min = h->min;
		}
		else
		{
			//合并两个堆的双向循环根链表
			this->min->right->left = h->min;
			h.min->right->left = this->min;
			FibonacciNode<T>* x = this->min->right;
			this->min->right = h.min->right;
			h.min->right = x;
			//更新堆最小节点
			if (h.min->element < this->min)
			{
				this->min = h.min;
			}
		}
		//更新节点数
		this->num = this->num + h.num;
		return;
	}

	//删除堆最小节点并返回
	FibonacciNode<T>* DeleteMin()
	{
		FibonacciNode<T>* z = this->min;
		if (z != nullptr)
		{
			if (z->child != nullptr)
			{
				//将最小节点的子节点加入根节点链表
				z->right->left = z->child;
				z->child->right->left = z;
				FibonacciNode<T>* x = z->right;
				z->right = z->child->right;
				z->child->right = x;
				//遍历更新新的根节点的父节点
				x = x->left;
				while (x != z)
				{
					x->parent = nullptr;
					x = x->left;
				}
			}
			//从根节点链表中删除最小节点
			z->left->right = z->right;
			z->right->left = z->left;
			//更新堆的最小节点
			if (z == z->right)
			{
				this->min = nullptr;
				if (z->child != nullptr)
				{
					this->min = z->child;
					FibonacciNode<T>* x = z->child->right;
					while (x != z->child)
					{
						if (x->element < this->min->element)
						{
							this->min = x;
						}
						x = x->right;
					}
					if (x->element < this->min->element)
					{
						this->min = x;
					}
				}
			}
			else
			{
				this->min = z->right;
				//对根节点链表进行联合
				this->consolidate();
			}
			//更新节点数
			this->num--;
		}
		//返回最小节点
		return z;
	}

	//降低节点值
	void DecreaseKey(FibonacciNode<T>* x, const T& d)
	{
		if (x->element < d)
		{
			cerr << "new key is greater than current key" << endl;
			return;
		}
		x->element = d;
		FibonacciNode<T>* y = x->parent;
		if (y != nullptr && x->element < y->element)
		{
			this->Cut(x, y);
			this->CascadingCut(y);
		}
		//更新最小节点
		if (x->element < this->min->element)
		{
			this->min = x;
		}
		return;
	}

	//返回最小节点
	FibonacciNode<T>* GetMin()const
	{
		return this->min;
	}
};

#endif