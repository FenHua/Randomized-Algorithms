/* Queenslv.cpp : �������̨Ӧ�ó������ڵ㡣
1����˹ά��˹(Las Vegas)�㷨
��˹ά��˹�㷨����õ�����ȷ�Ľ⡣һ������˹ά��˹�㷨�ҵ�һ���⣬������һ������ȷ�⡣����ʱ����˹ά��˹��
���Ҳ����⡣�����ؿ����㷨���ƣ���˹ά��˹�㷨�ҵ���ȷ��ĸ������������õļ���ʱ������Ӷ���ߡ������������
�����һʵ������ͬһ��˹ά��˹�㷨�����Ը�ʵ������㹻��Σ���ʹ���ʧ�ܵĸ�������С����˹ά��˹�㷨��һ����
��������������������Ծ����п��ܵ����㷨�Ҳ�������Ľ⡣
2��n������
�������٣���n��n��������Ϸ��ñ˴˲��ܹ�����n���ʺ󡣰��չ�������Ĺ��򣬻ʺ���Թ�����֮����ͬһ�л�ͬһ��
��ͬһб���ϵ����ӡ�n������ȼ�����n��n��������Ϸ���n���ʺ��κ�2���ʺ󲻷���ͬһ�л�ͬһ�л�ͬһб���ϡ�
*/
//������㷨 ��˹ά��˹�㷨 n������
#include "stdafx.h"
#include"RandomNumber.h"
#include<cmath>
#include<iostream>
using namespace std;

class Queen
{
	friend void nQueen(int);
private:
	bool Place(int k);//���Իʺ�k����x[k]�еĺϷ���
	bool Queenslv(void);//�������n���ʺ���˹ά��˹�㷨
	int n;//�ʺ����
	int *x, *y;//������
};
//���Իʺ�k���ڵ�x[k]�еĺϷ���
bool Queen::Place(int k)
{
	for (int j = 1; j < k; j++)
	{
		if ((abs(k - j) == abs(x[j] - x[k])) || (x[j] == x[k]))
		{
			return false;
		}
	}
	return true;
}
//�������n���ʺ����˹ά��˹�㷨
bool Queen::Queenslv(void)
{
	RandomNumber rnd;//�����������
	int k = 1;//��һ���ʺ���
	int count = 1;//��һ���пɷ��ûʺ�ĸ���
	while ((k <= n) && (count > 0))
	{
		count = 0;
		for (int i = 0; i <= n; i++)
		{
			x[k] = i;//λ��
			if (Place(k))
			{
				y[count++] = i;
			}
		}
		if (count > 0)
		{
			x[k++] = y[rnd.Random(count)];//���λ��
		}
	}
	return (count > 0);//count>0��ʾ���óɹ�
}
//��n���������˹ά��˹�㷨
void nQueen(int n)
{
	Queen X;
	X.n = n;
	int*p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	X.y = new int[n + 1];
	//���������������n���ʺ����˹ά��˹�㷨��ֱ���ɹ�
	while (!X.Queenslv());
	for (int i = 1; i <= n; i++)
	{
		cout << p[i] << " ";
	}
	cout << endl;
	delete[]p;
}

int main()
{
	int n = 8;
	cout << n << "�ʺ�����Ľ�Ϊ��" << endl;
	nQueen(n);
	return 0;
}

