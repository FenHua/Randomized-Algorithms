/*LinearSelect.cpp : 定义控制台应用程序的入口点。
线性时间选择算法
1)随机划分选择基准
对于选择问题而言,用拟中位数作为划分基准可以保证在最坏的情况下用线性时间完成选择。
如果只简单地用待划分数组的第一个元素作为划分基准，则算法的平均性能较好，而在最坏
的情况下需要O(n^2)计算时间。舍伍德选择算法则随机地选择一个数组元素作为划分基准，
这样既保证算法的线性时间平均性能，又避免了计算拟中位数的麻烦。
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
	cout << "原数组为：" << endl;
	for (int i = 0; i < 9; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "所给数组第7小元素为：" << select(a, 9, 7) << endl;
	return 0;
}

//计算a[0:n-1]中第k小元素，假设a[n]是一个键值无穷大的元素
template<class Type>Type select(Type a[], int n, int k)
{
	if (k<1 || k>n)
	{
		cout << "请输入正确的k！" << endl;
		return 0;
	}
	return select(a, 0, n - 1, k);
}
//计算a[1:r]中第k小元素
template<class Type>Type select(Type a[], int l, int r, int k)
{
	static RandomNumber rnd;
	while (true)
	{
		if (l >= r)
			return a[l];
		int i = l, j = l + rnd.Random(r - l + 1);//随机选择划分基准
		Swap(a[i], a[j]);
		j = r + 1;
		Type pivot = a[l];
		//以划分基准为轴做元素交换 
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
		if (j - l + 1 == k)//第k小
		{
			return pivot;
		}
		//a[j]必然小于pivort,做最后一次交换，满足左侧比pivot小，右侧比pivot大
		a[l] = a[j];
		a[j] = pivot;
		//对子数组重复划分过程
		if (j - l + 1 < k)
		{
			k = k - j + l - 1;//右侧：k-(j-l+1)=k-j+l-1
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