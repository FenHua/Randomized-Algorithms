/*ShuffleSelect.cpp : 定义控制台应用程序的入口点。
2)随机洗牌预处理
有时也会遇到这样的情况，即所给的确定性算法无法直接改造成舍伍德型算法。此时可借助于随机预处理技术
，不改变原有的确定性算法，仅对其输入进行随机洗牌，同样可收到舍伍德算法的效果。例如，对于确定性选
择算法，可以用下面的洗牌算法shuffle将数组a中元素随机排列，然后用确定性选择算法求解。这样做所收到
的效果与舍伍德型算法的效果是一样的。
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
	cout << "原数组为：" << endl;
	for (int i = 0; i<9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	Shuffle(a, 9);
	cout << "洗牌后数组为：" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "所给数组的第7小元素为：" << select(a, 9, 7) << endl;
	return 0;
}

//计算a[0:n-1]中第k小元素，假设a[n]是一个键值无穷大的元素
template<class Type>Type select(Type a[], int n, int k)
{
	if (k<1 || k>n)
	{
		cout << "请输入正确的K！" << endl;
		return 0;
	}
	return select(a, 0, n - 1, k);
}
//计算a[1:r]中的第k小的元素
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
		//以划分基准为轴做元素交换
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
		if (j - l + 1 == k)//第k小
		{
			return pivot;
		}
		//a[j]必然小于pivot，做最后一次交换，满足左侧比pivot小，右侧比pivot大
		a[l] = a[j];
		a[j] = pivot;
		//对子数组重新重复划分过程
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
//随机洗牌算法
template<class Type>void Shuffle(Type a[], int n)
{
	static RandomNumber rnd;
	for (int i = 0; i < n; i++)
	{
		int j = rnd.Random(n - i) + i;
		Swap(a[i], a[j]);
	}
}