/*QueenBLV.cpp : 定义控制台应用程序的入口点。
2)与回溯法结合的拉斯维加斯随机算法求解思路
如果将上述随机放置策略与回溯法相结合，可能会获得更好的效果。可以先在棋盘的若干行中随机地放置皇后，
然后在后继行中用回溯法继续放置，直至找到一个解或宣告失败。随机放置的皇后越多，后继回溯搜索所需的时
间就越少，但失败的概率也就越大。
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
	bool Place(int k);//测试皇后k置于x[k]的合法性
	bool Backtrack(int t);//解n后问题的回溯法
	bool QueenBLV(int stopVegas);//随机放置n个皇后拉斯维加斯算法
	int n, *x, *y;
};
//测试皇后k置于x[k]列的合法性
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
//解n后问题的回溯法
bool Queen::Backtrack(int t)
{
	if (t > n)
	{
		for (int i = 1; i <= n; i++)
		{
			y[i] = x[i];//问题对的解
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
//随机放置n个皇后拉斯维加斯算法
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
			x[k++] = y[rnd.Random(count)];//随机位置
		}
	}
	return(count > 0);//count>0表示放置成功
}
//与回溯法相结合的解n后问题的拉斯维加斯算法
bool nQueen(int n)
{
	Queen X;
	X.n = n;//初始化X
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
	//算法的回溯部分
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
	cout << "皇后问题的解为：" << endl;
	while (!nQueen(n));
	return 0;
}

