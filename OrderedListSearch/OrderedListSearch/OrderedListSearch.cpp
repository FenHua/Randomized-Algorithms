/*OrderedListSearch.cpp : �������̨Ӧ�ó������ڵ㡣
�������������������
��������
��������������ʾ�����ĺ���n��Ԫ�ص�����S����value[0:n]�洢�����е�Ԫ�أ�link[0:n]�洢��
����Ԫ��������value��λ�õ�ָ��(ʵ����ʹ������ģ������)��link[0]ָ�������еĵ�һ��Ԫ�أ�
��value[link[0]]�Ǽ����е���СԪ�ء�һ��أ����value[i]����������S�еĵ�k��Ԫ�أ���value[link[i]]
��S�е�k+1��Ԫ�ء�S��Ԫ�ص������Ա���Ϊ����������1<=i<=n��value[i]<=value[link[i]]�����ڼ���S��
�����Ԫ��value[k]�У�link[k]=0��value[0]��һ��������
����˼��
�������������ɲ���˳�������ķ�ʽ������������S������ֵΪx��Ԫ�ء��������S�к���n��Ԫ�أ�
�����������£�˳�������㷨����ļ���ʱ��ΪO(n)�����������±���������ʣ��������һ�������
�����㷨��һ�Ľ��㷨������ʱ�临���ԡ��㷨�Ļ���˼���ǣ������ȡ����Ԫ�����ɴΣ��ӽϽӽ�����Ԫ
��x��λ�ÿ�ʼ��˳����������������������Ԫ��k�Σ������˳�����������ƽ���Ƚϴ���ΪO(n/k+1)��
��ˣ����ȥk=|sqrt(n)|�����㷨�����ƽ������ʱ��Ϊ(Osqrt(n))��
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include"math.h"
#include<iostream>
using namespace std;

template<class Type>class OrderedList
{
	friend int main();
public:
	OrderedList(Type Small, Type Large, int MaxL);
	~OrderedList();
	bool Search(Type x, int&index);//����ָ��Ԫ��
	int SearchLast(void);//�������Ԫ��
	void Insert(Type k);//����ָ��Ԫ��
	void Delete(Type k);//ɾ��ָ��Ԫ��
	void Output();//���������Ԫ��
private:
	int n;//��ǰ������Ԫ�صĸ���
	int MaxLength;//���������Ԫ�صĸ���
	Type*value;//�洢������Ԫ�ص�����
	int *Link;//ָ������
	RandomNumber rnd;//���������
	Type Small;//������Ԫ�صĶ��½�
	Type TailKey;//������Ԫ�ص��Ͻ�
};
template<class Type>OrderedList<Type>::OrderedList(Type small, Type Large, int MaxL)
{
	MaxLength = MaxL;
	value = new Type[MaxLength+1];
	Link = new int[MaxLength + 1];
	TailKey =Large;
	n = 0;
	Link[0] = 0;
	value[0] = TailKey;
	Small = small;
}
template<class Type>OrderedList<Type>::~OrderedList()
{
	delete value;
	delete Link;
}
//���������е�ָ��Ԫ��k
template<class Type>bool OrderedList<Type>::Search(Type x, int&index)
{
	index = 0;
	Type max = Small;
	int m = floor(sqrt(double(n)));//�����ȡ����Ԫ�ش�����Floor(x)���书���ǡ�����ȡ����
	for (int i = 1; i <= m; i++)
	{
		int j = rnd.Random(n) + 1;//�����������Ԫ�ص�λ��
		Type y = value[j];
		if ((max < y) && (y < x))
		{
			max = y;
			index = j;
		}
	}
	//˳������
	while (value[Link[index]] < x)
	{
		index =Link[index];
	}
	return (value[Link[index]] == x);
}
//����ָ��Ԫ��
template<class Type>void OrderedList<Type>::Insert(Type k)
{
	if ((n == MaxLength) || (k >= TailKey))
	{
		return;
	}
	int index;
	if (!Search(k, index))
	{
		value[++n] = k;
		Link[n] =Link[index];
		Link[index] = n;
	}
}
//��������������Ԫ��
template<class Type>int OrderedList<Type>::SearchLast(void)
{
	int  index = 0;
	Type x = value[n];
	Type max = Small;
	int m = floor(sqrt(double(n)));//�����ȡ����Ԫ�ش���
	for (int i = 1; i <= m; i++)
	{
		int j = rnd.Random(n) + 1;//�����������Ԫ��λ��
		Type y = value[j];
		if ((max < y) && (y < x))
		{
			max = y;
			index = j;
		}
	}
	//˳������
	while (Link[index] != n)
	{
		index = Link[index];
	}
	return index;
}
//ɾ��������ָ����Ԫ��
template<class Type>void OrderedList<Type>::Delete(Type k)
{
	if ((n == 0) && (k >= TailKey))
		return;
	int index;
	if (Search(k, index))
	{
		int p = Link[index];
		if (p == n)
		{
			Link[index] =Link[p];
		}
		else
		{
			if (Link[p] != n)
			{
				int q = SearchLast();
				Link[q] = p;
				Link[index] =Link[p];
			}
			value[p] = value[n];//ɾ��Ԫ�������Ԫ�����
			Link[p] =Link[n];
		}
		n--;
	}
}
//������������е�Ԫ��
template<class Type>void OrderedList<Type>::Output()
{
	int index = 0, i = 0;
	while (i < n)
	{
		index =Link[index];
		cout << value[index] << " ";
		i++;
	}
	cout << endl;
	cout << "value:";
	for (i = 0; i <= n; i++)
	{
		cout.width(4);
		cout << value[i];
	}
	cout << endl;
	cout << "link:";
	for (i = 0; i <= n; i++)
	{
		cout.width(4);
		cout <<Link[i];
	}
	cout << endl;
}

int main()
{
	static RandomNumber rnd;
	OrderedList<int>*ol = new OrderedList<int>(0, 100, 100);
	//����
	cout << "============����===========" << endl;
	while (ol->n < 10)
	{
		int e = rnd.Random(99);
		ol->Insert(e);
	}
	ol->Output();
	cout << endl;
	//����
	cout << "===========����=============" << endl;
	int index;
	cout << "���������value�����е�5��Ԫ�����£�" << endl;
	cout << "value[5]=" << ol->value[5] << endl;
	ol->Search(ol->value[5], index);
	cout << "λ���������Ϊ��" << ol->Link[index] << endl;
	cout << endl;
	//ɾ��
	cout << "============ɾ��=============" << endl;
	cout << "ɾ�������value�����еĵ�5��Ԫ�����£�" << endl;
	cout << "value[5]=" << ol->value[5] << endl;
	ol->Delete(ol->value[5]);
	ol->Output();
	delete ol;
	return 0;
}

