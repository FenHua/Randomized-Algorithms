/*OrderedListSearch.cpp : 定义控制台应用程序的入口点。
舍伍德随机化搜索有序表
问题描述
用两个数组来表示所给的含有n个元素的有序集S。用value[0:n]存储有序集中的元素，link[0:n]存储有
序集中元素在数组value中位置的指针(实际上使用数组模拟链表)。link[0]指向有序集中的第一个元素，
集value[link[0]]是集合中的最小元素。一般地，如果value[i]是所给有序集S中的第k个元素，则value[link[i]]
是S中第k+1个元素。S中元素的有序性表现为，对于任意1<=i<=n有value[i]<=value[link[i]]。对于集合S中
的最大元素value[k]有，link[k]=0且value[0]是一个大数。
搜索思想
对于有序链表，可采用顺序搜索的方式在所给的有序集S中搜索值为x的元素。如果有序集S中含有n个元素，
则在最坏的情况下，顺序搜索算法所需的计算时间为O(n)。利用数组下标的索引性质，可以设计一个随机化
搜索算法，一改进算法的搜索时间复杂性。算法的基本思想是，随机抽取数组元素若干次，从较接近搜索元
素x的位置开始做顺序搜索。如果随机搜索数组元素k次，则其后顺序搜索所需的平均比较次数为O(n/k+1)。
因此，如果去k=|sqrt(n)|，则算法所需的平均计算时间为(Osqrt(n))。
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
	bool Search(Type x, int&index);//搜索指定元素
	int SearchLast(void);//搜索最大元素
	void Insert(Type k);//插入指定元素
	void Delete(Type k);//删除指定元素
	void Output();//输出集合中元素
private:
	int n;//当前集合中元素的个数
	int MaxLength;//集合中最大元素的个数
	Type*value;//存储集合中元素的数组
	int *Link;//指针数组
	RandomNumber rnd;//随机产生器
	Type Small;//集合中元素的额下界
	Type TailKey;//集合中元素的上界
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
//搜索集合中的指定元素k
template<class Type>bool OrderedList<Type>::Search(Type x, int&index)
{
	index = 0;
	Type max = Small;
	int m = floor(sqrt(double(n)));//随机抽取数组元素次数，Floor(x)，其功能是“向下取整”
	for (int i = 1; i <= m; i++)
	{
		int j = rnd.Random(n) + 1;//随机产生数组元素的位置
		Type y = value[j];
		if ((max < y) && (y < x))
		{
			max = y;
			index = j;
		}
	}
	//顺序搜索
	while (value[Link[index]] < x)
	{
		index =Link[index];
	}
	return (value[Link[index]] == x);
}
//插入指定元素
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
//搜索集合中最大的元素
template<class Type>int OrderedList<Type>::SearchLast(void)
{
	int  index = 0;
	Type x = value[n];
	Type max = Small;
	int m = floor(sqrt(double(n)));//随机抽取数组元素次数
	for (int i = 1; i <= m; i++)
	{
		int j = rnd.Random(n) + 1;//随机产生数组元素位置
		Type y = value[j];
		if ((max < y) && (y < x))
		{
			max = y;
			index = j;
		}
	}
	//顺序搜索
	while (Link[index] != n)
	{
		index = Link[index];
	}
	return index;
}
//删除集合中指定的元素
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
			value[p] = value[n];//删除元素由最大元素来填补
			Link[p] =Link[n];
		}
		n--;
	}
}
//输出集合中所有的元素
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
	//创建
	cout << "============创建===========" << endl;
	while (ol->n < 10)
	{
		int e = rnd.Random(99);
		ol->Insert(e);
	}
	ol->Output();
	cout << endl;
	//搜索
	cout << "===========搜索=============" << endl;
	int index;
	cout << "搜索有序表value数组中第5个元素如下：" << endl;
	cout << "value[5]=" << ol->value[5] << endl;
	ol->Search(ol->value[5], index);
	cout << "位置搜索结果为：" << ol->Link[index] << endl;
	cout << endl;
	//删除
	cout << "============删除=============" << endl;
	cout << "删除有序表value数组中的第5个元素如下：" << endl;
	cout << "value[5]=" << ol->value[5] << endl;
	ol->Delete(ol->value[5]);
	ol->Output();
	delete ol;
	return 0;
}

