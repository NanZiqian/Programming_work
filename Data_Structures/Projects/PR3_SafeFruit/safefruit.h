#ifndef SAFE_FRUIT
#define SAFE_FRUIT
#include<stdio.h>
#include<time.h>

//ˮ���ṹ�嶨��
typedef struct fruit
{
	int id;
	int price;
	int unsafenum;//��¼��ͻˮ������
	int unsafefruit[100];//��¼��ͻˮ��id
}fruit;

//��ͻ��¼�ṹ�嶨��
typedef struct tip
{
	int fid1;
	int fid2;
}tip;

int n, m;
tip tips[100];//n����ͻˮ����¼
fruit fruits[100];//m��ˮ��
int safelistnum = 0;//��¼��ȫˮ������
fruit safefruitlist[100];//��ȫˮ������
int solutionnum = 0;
fruit solutionlist[100];

//����������Ϣ
void input()
{
	scanf_s("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d %d", &tips[i].fid1, &tips[i].fid2);
	}
	for (int i = 0; i < m; i++)
	{
		scanf_s("%d %d", &fruits[i].id, &fruits[i].price);
		fruits[i].unsafenum = 0;
		//������ͻˮ����¼������¼�����Ӧˮ���ṹ��ĳ�Ա������
		for (int j = 0; j < n; j++)
		{
			if (tips[j].fid1 == fruits[i].id)
			{
				fruits[i].unsafefruit[fruits[i].unsafenum] = tips[j].fid2;
				fruits[i].unsafenum++;
			}
			if (tips[j].fid2 == fruits[i].id)
			{
				fruits[i].unsafefruit[fruits[i].unsafenum] = tips[j].fid1;
				fruits[i].unsafenum++;
			}
		}
	}
	return;
}

//������ˮ�����۸���������
void sortfruitsbyprice()
{
	fruit t;
	//��������
	for (int i = 1; i < m; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (fruits[i].price < fruits[j].price)
			{
				t = fruits[i];
				for (int k = i; k > j; k--)
				{
					fruits[k] = fruits[k - 1];
				}
				fruits[j] = t;
			}
		}
	}
	return;
}

//�������ˮ����id��������
void sortsolutionbyid()
{
	fruit t;
	//��������
	for (int i = 1; i < solutionnum; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (solutionlist[i].id < solutionlist[j].id)
			{
				t = solutionlist[i];
				for (int k = i; k > j; k--)
				{
					solutionlist[k] = solutionlist[k - 1];
				}
				solutionlist[j] = t;
			}
		}
	}
	return;
}

//��鵱ǰˮ��������ˮ���Ƿ��ͻ���޳�ͻ����1����ͻ����0
int checksafe()
{
	//������ȫˮ������
	for (int i = 0; i < safelistnum; i++)
	{
		//����ˮ���ĳ�ͻˮ��
		for (int j = 0; j < safefruitlist[i].unsafenum; j++)
		{
			//������ȫˮ������
			for (int k = 0; k < safelistnum; k++)
			{
				//�����ͻ
				if (safefruitlist[i].unsafefruit[j] == safefruitlist[k].id)
				{
					return 0;
				}
			}
		}
	}
	return 1;
}

//����������������������index�ǲ���ָ��
void dfs(int index)
{
	//��֦�������ˮ�������϶��޷�����ʱ�˳������֧
	
	if (safelistnum + m - index <= solutionnum)
		return;
	//��m+1�㣬�ݹ����
	if (index == m)
	{
		//����ͻ�򷵻�
		// if (checksafe() == 0)
		// {
		// 	return;
		// }
		//���޳�ͻ������½�
		//else
		{
			solutionnum = safelistnum;
			for (int i = 0; i < safelistnum; i++)
			{
				solutionlist[i] = safefruitlist[i];
			}
			return;
		}
	}
	else
	{
		//��Ϊ�۸����������ȷ���ͼ۵�ˮ�����ȵõ��Ľ���ͬ�������¼۸�϶��Ⱥ�õ��Ľ���ͣ����Ժ���������ļ۸��С
		//���費��ͻ
		safefruitlist[safelistnum++] = fruits[index];
		if (checksafe())//safe
		{
			dfs(index + 1);
		}
		safelistnum--;
		//�����ͻ
		dfs(index + 1);
		return;
	}
}

//������ĿҪ�������
void print()
{
	int first = 1, totalprice = 0;
	printf("%d\n", solutionnum);
	for (int i = 0; i < solutionnum; i++)
	{
		if (first)
		{
			printf("%03d", solutionlist[i].id);
			first = 0;
		}
		else
		{
			printf(" %03d", solutionlist[i].id);
		}
		//����ȫ��ˮ���۸��ܺ�
		totalprice += solutionlist[i].price;
	}
	printf("\n%d\n", totalprice);
	return;
}

//���ú����ҵ���
void findsolution()
{
	clock_t start_1,end_1;
	input();//�������룬����Ϣ����ṹ��
	sortfruitsbyprice();//��ˮ�����鰴�۸���������
	
	start_1=clock();
	dfs(0);//���������Ѱ�����������
	end_1=clock();
	
	sortsolutionbyid();//�������鰴ˮ��id��������
	print();//�����
	double time=1.0*(end_1-start_1)/CLOCKS_PER_SEC;
	printf("time: %lf\n",time);
	return;
}
#endif