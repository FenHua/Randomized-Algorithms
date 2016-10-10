/*ShuffleSelect.cpp : �������̨Ӧ�ó������ڵ㡣
2)���ϴ��Ԥ����
��ʱҲ�������������������������ȷ�����㷨�޷�ֱ�Ӹ������������㷨����ʱ�ɽ��������Ԥ������
�����ı�ԭ�е�ȷ�����㷨������������������ϴ�ƣ�ͬ�����յ�������㷨��Ч�������磬����ȷ����ѡ
���㷨�������������ϴ���㷨shuffle������a��Ԫ��������У�Ȼ����ȷ����ѡ���㷨��⡣���������յ�
��Ч������������㷨��Ч����һ���ġ�
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include"iostream"
using namespace std;

template<class Type>Type select(Type a[], int l, int r, int k);
template<class Type>Type select(Type a[], int n, int k);
template<class Type>void Shuffle(Type a[], int n);
template<class Type>inline void Swap(Type&a, Type&b);

int main()
{
	int a[] = { 5, 7, 3, 4, 8, 6, 9, 1, 2 };
	cout << "ԭ����Ϊ��" << endl;
	for (int i = 0; i<9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	Shuffle(a, 9);
	cout << "ϴ�ƺ�����Ϊ��" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "��������ĵ�7СԪ��Ϊ��" << select(a, 9, 7) << endl;
	return 0;
}

//����a[0:n-1]�е�kСԪ�أ�����a[n]��һ����ֵ������Ԫ��
template<class Type>Type select(Type a[], int n, int k)
{
	if (k<1 || k>n)
	{
		cout << "��������ȷ��K��" << endl;
		return 0;
	}
	return select(a, 0, n - 1, k);
}
//����a[1:r]�еĵ�kС��Ԫ��
template<class Type>Type select(Type a[], int l, int r, int k)
{
	while (true)
	{
		if (l >= r)
		{
			return a[l];
		}
		int i = l; int j = r + 1;
		Type pivot = a[l];
		//�Ի��ֻ�׼Ϊ����Ԫ�ؽ���
		while (true)
		{
			while (a[++i] < pivot);
			while (a[j--]>pivot);
			if (i >= j)
			{
				break;
			}
			Swap(a[i], a[j]);
		}
		if (j - l + 1 == k)//��kС
		{
			return pivot;
		}
		//a[j]��ȻС��pivot�������һ�ν�������������pivotС���Ҳ��pivot��
		a[l] = a[j];
		a[j] = pivot;
		//�������������ظ����ֹ���
		if (j - l + 1 < k)
		{
			k = k - j + l - 1;//k-(j-l+1)=k-j+l-1
			l = j + 1;
		}
		else
		{
			r = j - 1;
		}
	}
}
template<class Type>inline void Swap(Type &a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}
//���ϴ���㷨
template<class Type>void Shuffle(Type a[], int n)
{
	static RandomNumber rnd;
	for (int i = 0; i < n; i++)
	{
		int j = rnd.Random(n - i) + i;
		Swap(a[i], a[j]);
	}
}