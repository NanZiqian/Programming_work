#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include<cmath>
#include<iostream>
#include<vector>
using namespace std;

//FibonacciNode class

//���캯��: 0 ���� �� 1 ����

//***********���ⲿ�ӿ�******************
// void GetElement( )  --> ���ؽڵ�Ԫ��
//***************************************

 //FibonacciHeap class

 //���캯��: 0 ����

 //***********************���ⲿ�ӿ�***********************
 //bool Empty( )                 --> �ж϶��Ƿ�Ϊ��
 //FibonacciNode<T>* Insert( d ) --> ����Ԫ��d���ؽڵ�ָ��
 //void Merge( h )               --> �ϲ����õĶѺͶ�h
 //FibonacciNode<T>* DeleteMin( )--> ɾ����С�ڵ㲢����
 //void DecreaseKey( x,d )       --> ���ͽڵ�x��ֵΪd
 //FibonacciNode* GetMin( )      --> ������С�ڵ�ָ��
 //*************************����***************************
 //DecreaseKey�е��µ�ֵ��ԭ�е�ֵ��ʱ����


//FibonacciHeap������
template<typename T>
class FibonacciHeap;

//�ڵ��ඨ��
template<typename T>
class FibonacciNode
{
private:
	//�ڵ��Ա����
	T element;
	FibonacciNode* parent;//���ڵ�
	FibonacciNode* left;//��ڵ�
	FibonacciNode* right;//�ҽڵ�
	FibonacciNode* child;//�ӽڵ�
	int degree;//�ڵ�Ķȣ������Ӹ���
	int mark;//1������deletemin������ֻʧȥ��һ������

	//��Ԫ������
	friend class FibonacciHeap<T>;

public:
	//���ι��������ֵ����ֵ�汾
	FibonacciNode(const T& d = T{ })
		:element{ d }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, child{ nullptr }, degree{ 0 }, mark{ 0 } {}
	FibonacciNode(T&& d = T{ })
		:element{ move(d) }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, child{ nullptr }, degree{ 0 }, mark{ 0 } {}
	//��������
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
	//�ѵĳ�Ա����
	FibonacciNode<T>* min;//ָ�����С�ڵ�
	int num;//��¼�ѽڵ���

	//˽�г�Ա��������deletemin���ã����ںϲ����ڵ�����
	void consolidate()
	{
		int max = ceil(log(this->num) / log(1.5)) + 1;
		vector<FibonacciNode<T>*> arr(max, nullptr);
		//�������ڵ�����
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
			//������ͬʱ�ϲ�������
			while (arr[d] != nullptr)
			{
				FibonacciNode<T>* y = arr[d];
				//yԪ�ر�xСʱ������x��y
				if (y->element < x->element)
				{
					FibonacciNode<T>* t = x;
					x = y;
					y = t;
				}
				//�Ӹ��ڵ�������ɾ��y
				y->left->right = y->right;
				y->right->left = y->left;
				//��y����x���ӽڵ�������
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
				//����x�Ķ�
				x->degree++;
				//����y�ı��
				y->mark = 0;
				arr[d] = nullptr;
				d = d + 1;
			}
			arr[d] = x;
		}
		//final�����һ��ѭ��
		FibonacciNode<T>* x = i;
		int d = x->degree;
		//������ͬʱ�ϲ�������
		if (arr[d] != x)
		{
			while (arr[d] != nullptr)
			{
				FibonacciNode<T>* y = arr[d];
				//yԪ�ر�xСʱ������x��y�ڸ��ڵ������е�λ��
				if (y->element < x->element)
				{
					FibonacciNode<T>* t = x;
					x = y;
					y = t;
				}
				//�Ӹ��ڵ�������ɾ��y
				y->left->right = y->right;
				y->right->left = y->left;
				//��y����x���ӽڵ�������
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
				//����x�Ķ�
				x->degree++;
				//����y�ı��
				y->mark = 0;
				arr[d] = nullptr;
				d = d + 1;
			}
			arr[d] = x;
		}
		//�������ڵ�����Ѱ����С�ڵ�
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

	//˽�г�Ա��������decreasekey���ã����ڽ�y���ӽڵ�x�ƶ������ڵ�����
	void Cut(FibonacciNode<T>* x, FibonacciNode<T>* y)
	{
		//��y���ӽڵ�������ɾ��x
		x->left->right = x->right;
		x->right->left = x->left;
		//����y���ӽڵ�
		if (x->right == x)
		{
			y->child = nullptr;
		}
		else
		{
			y->child = x->right;
		}
		//����y�Ķ�
		y->degree--;
		//����x�ĸ��ڵ�
		x->parent = nullptr;
		//����x�ı��
		x->mark = 0;
		//��x���������
		x->left = this->min;
		this->min->right->left = x;
		x->right = this->min->right;
		this->min->right = x;
		return;
	}

	//˽�г�Ա��������decreasekey���ã����ڵݹ����mark�������ݱ�Ǿ����Ƿ�cut
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
	//Ĭ�Ϲ��죬��ʼ����
	FibonacciHeap() :min{ nullptr }, num{ 0 } {};
	//��������
	~FibonacciHeap()
	{
		while (!Empty())
		{
			delete this->DeleteMin();
		}
	}

	//�ն��жϣ���Ϊ�նѷ���true�����򷵻�false
	bool Empty()
	{
		return this->num == 0;
	}

	//����в���Ԫ��,ͬʱ�����½ڵ��ָ��
	FibonacciNode<T>* Insert(const T& d)
	{
		//����ռ䣬�����ڵ�
		FibonacciNode<T>* x = new FibonacciNode<T>{ d };
		if (this->min == nullptr)
		{
			//�ն���һ�����ڵ��˫��ѭ��������
			x->left = x;
			x->right = x;
			this->min = x;
		}
		else
		{
			//���½ڵ����˫��ѭ��������
			x->left = this->min;
			this->min->right->left = x;
			x->right = this->min->right;
			this->min->right = x;
			//��������С�ڵ�
			if (x->element < this->min->element)
			{
				this->min = x;
			}
		}
		//���½ڵ���
		this->num++;
		return x;
	}

	//�ϲ���
	void Merge(const FibonacciHeap& h)
	{
		//����ն�
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
			//�ϲ������ѵ�˫��ѭ��������
			this->min->right->left = h->min;
			h.min->right->left = this->min;
			FibonacciNode<T>* x = this->min->right;
			this->min->right = h.min->right;
			h.min->right = x;
			//���¶���С�ڵ�
			if (h.min->element < this->min)
			{
				this->min = h.min;
			}
		}
		//���½ڵ���
		this->num = this->num + h.num;
		return;
	}

	//ɾ������С�ڵ㲢����
	FibonacciNode<T>* DeleteMin()
	{
		FibonacciNode<T>* z = this->min;
		if (z != nullptr)
		{
			if (z->child != nullptr)
			{
				//����С�ڵ���ӽڵ������ڵ�����
				z->right->left = z->child;
				z->child->right->left = z;
				FibonacciNode<T>* x = z->right;
				z->right = z->child->right;
				z->child->right = x;
				//���������µĸ��ڵ�ĸ��ڵ�
				x = x->left;
				while (x != z)
				{
					x->parent = nullptr;
					x = x->left;
				}
			}
			//�Ӹ��ڵ�������ɾ����С�ڵ�
			z->left->right = z->right;
			z->right->left = z->left;
			//���¶ѵ���С�ڵ�
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
				//�Ը��ڵ������������
				this->consolidate();
			}
			//���½ڵ���
			this->num--;
		}
		//������С�ڵ�
		return z;
	}

	//���ͽڵ�ֵ
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
		//������С�ڵ�
		if (x->element < this->min->element)
		{
			this->min = x;
		}
		return;
	}

	//������С�ڵ�
	FibonacciNode<T>* GetMin()const
	{
		return this->min;
	}
};

#endif