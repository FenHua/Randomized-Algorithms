/*LinearSelect.cpp : �������̨Ӧ�ó������ڵ㡣
����ʱ��ѡ���㷨
1)�������ѡ���׼
����ѡ���������,������λ����Ϊ���ֻ�׼���Ա�֤����������������ʱ�����ѡ��
���ֻ�򵥵��ô���������ĵ�һ��Ԫ����Ϊ���ֻ�׼�����㷨��ƽ�����ܽϺã������
���������ҪO(n^2)����ʱ�䡣�����ѡ���㷨�������ѡ��һ������Ԫ����Ϊ���ֻ�׼��
�����ȱ�֤�㷨������ʱ��ƽ�����ܣ��ֱ����˼�������λ�����鷳��
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include"iostream"
using namespace std;

template<class Type>Type select(Type a[], int l, int r, int k);
template<class Type>Type select(Type a[], int n, int k);
template<class Type>inline void Swap(Type&a, Type&b);


int main()
{
	int a[] = { 5, 7, 3, 4, 8, 6, 9, 1, 2 };
	cout << "ԭ����Ϊ��" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "���������7СԪ��Ϊ��" << select(a, 9, 7) << endl;
	return 0;
}

//����a[0:n-1]�е�kСԪ�أ�����a[n]��һ����ֵ������Ԫ��
template<class Type>Type select(Type a[], int n, int k)
{
	if (k<1 || k>n)
	{
		cout << "��������ȷ��k��" << endl;
		return 0;
	}
	return select(a, 0, n - 1, k);
}
//����a[1:r]�е�kСԪ��
template<class Type>Type select(Type a[], int l, int r, int k)
{
	static RandomNumber rnd;
	while (true)
	{
		if (l >= r)
			return a[l];
		int i = l, j = l + rnd.Random(r - l + 1);//���ѡ�񻮷ֻ�׼
		Swap(a[i], a[j]);
		j = r + 1;
		Type pivot = a[l];
		//�Ի��ֻ�׼Ϊ����Ԫ�ؽ��� 
		while (true)
		{
			while (a[++i] < pivot);
			while (a[--j]>pivot);
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
		//a[j]��ȻС��pivort,�����һ�ν�������������pivotС���Ҳ��pivot��
		a[l] = a[j];
		a[j] = pivot;
		//���������ظ����ֹ���
		if (j - l + 1 < k)
		{
			k = k - j + l - 1;//�Ҳࣺk-(j-l+1)=k-j+l-1
			l = j + 1;
		}
		else
		{
			r = j - 1;
		}
	}
}
template<class Type>inline void Swap(Type&a, Type&b)
{
	Type temp = a;
	a = b;
	b = temp;
}