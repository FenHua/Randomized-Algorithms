/*QueenBLV.cpp : �������̨Ӧ�ó������ڵ㡣
2)����ݷ���ϵ���˹ά��˹����㷨���˼·
���������������ò�������ݷ����ϣ����ܻ��ø��õ�Ч���������������̵�������������ط��ûʺ�
Ȼ���ں�������û��ݷ��������ã�ֱ���ҵ�һ���������ʧ�ܡ�������õĻʺ�Խ�࣬��̻������������ʱ
���Խ�٣���ʧ�ܵĸ���Ҳ��Խ��
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<cmath>
#include"iostream"
using namespace std;

class Queen
{
	friend bool nQueen(int);
private:
	bool Place(int k);//���Իʺ�k����x[k]�ĺϷ���
	bool Backtrack(int t);//��n������Ļ��ݷ�
	bool QueenBLV(int stopVegas);//�������n���ʺ���˹ά��˹�㷨
	int n, *x, *y;
};
//���Իʺ�k����x[k]�еĺϷ���
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
//��n������Ļ��ݷ�
bool Queen::Backtrack(int t)
{
	if (t > n)
	{
		for (int i = 1; i <= n; i++)
		{
			y[i] = x[i];//����ԵĽ�
		}
		return true;
	}
	else
	{
		for (int i = 1; i <= n; i++)
		{
			x[t] = i;
			if (Place(t) && Backtrack(t + 1))
			{
				return true;
			}
		}
	}
	return false;
}
//�������n���ʺ���˹ά��˹�㷨
bool Queen::QueenBLV(int stopVegas)
{
	RandomNumber rnd;
	int k = 1;
	int count = 1;
	while ((k <= stopVegas) && (count > 0))
	{
		count = 0;
		for (int i = 1; i <= n; i++)
		{
			x[k] = i;
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
	return(count > 0);//count>0��ʾ���óɹ�
}
//����ݷ����ϵĽ�n���������˹ά��˹�㷨
bool nQueen(int n)
{
	Queen X;
	X.n = n;//��ʼ��X
	int *p = new int[n + 1];
	int *q = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
		q[i] = 0;
	}
	X.y = p;
	X.x = q;
	int stop = 3;
	if (n > 15)
	{
		stop = n - 15;
	}
	bool found = false;
	while (!X.QueenBLV(stop));
	//�㷨�Ļ��ݲ���
	if (X.Backtrack(stop + 1))
	{
		for (int i = 1; i <= n; i++)
		{
			cout << p[i] << " ";
		}
		found = true;
		cout << endl;
	}
	delete[]p;
	delete[]q;
	return found;
}

int main()
{
	int n = 8;
	cout << "�ʺ�����Ľ�Ϊ��" << endl;
	while (!nQueen(n));
	return 0;
}

