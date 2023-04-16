#include "time.h"
#include <random>
using namespace std;
#define INF 0x7fffffff

//************************************
// Method:    RandomCreatFunc
// FullName:  RandomCreatFunc
// Access:    public 
// Returns:   int
// Qualifier: 根据区间生成随机数，随机数范围：[interval_min,interval_max]
// Parameter: int interval_min 区间左值
// Parameter: int interval_max 区间右值
//************************************
int RandomCreatFunc(int interval_min, int interval_max){
	if (interval_min >= interval_max)
		return INF;
	//种子值是通过 random_device 类型的函数对象 rd 获得的。
	//每一个 rd() 调用都会返回不同的值，而且如果我们实现的 random_devic 是非确定性的，程序每次执行连续调用 rd() 都会产生不同的序列。
	random_device rd;
	default_random_engine e{ rd() };
	//部分环境中random_device不可用，原因尚不知，笔者在测试过程中发现，如果不可用该用以下方式
	 // unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // default_random_engine e{seed};
	int random_num = 0;
	//分情况产生随机数，考虑3种情况：min<0&&max>0 、max<0和min>0
	if (interval_min >= 0)//min>0的情况
	{
		uniform_int_distribution<unsigned> a(interval_min, interval_max);
		random_num = a(e);
	}
	else if (interval_max > 0)//min<0&&max>0 的情况
	{
		uniform_int_distribution<unsigned> a(0, -interval_min);
		random_num = a(e);
		random_num = -random_num;
		uniform_int_distribution<unsigned> b(0, 10);
		if (b(e) % 2 == 0)
		{
			uniform_int_distribution<unsigned> c(0, interval_max);
			random_num = c(e);
		}
	}
	else//max<0的情况
	{
		uniform_int_distribution<unsigned> a(-interval_max, -interval_min);
		random_num = a(e);
		random_num = -random_num;
	}
	return random_num;

}

//************************************
// Method:    RandomArray
// FullName:  RandomArray
// Access:    public 
// Returns:   void
// Qualifier:生成随机序列 输入的数组将被改变为1—Amounts的随机序列
// Parameter: int * arr 输入的数组
// Parameter: int Amounts 数组大小
//************************************
void RandomArray(int *arr,int Amounts)
{
	for (int i = 0; i < Amounts; i++)
		arr[i] = 0;
	int count = 0;		//计数，同时为数组元素的序号
	while (count < Amounts)
	{
		int val = RandomCreatFunc(0,Amounts-1);//随机确定下标
		if (!arr[val])
		{
			arr[val] = count + 1;
			++count;
		}
	}
}