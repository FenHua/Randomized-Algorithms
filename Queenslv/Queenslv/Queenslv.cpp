/* Queenslv.cpp : 定义控制台应用程序的入口点。
1、拉斯维加斯(Las Vegas)算法
拉斯维加斯算法不会得到不正确的解。一旦用拉斯维加斯算法找到一个解，这个解就一定是正确解。但有时用拉斯维加斯算
法找不到解。与蒙特卡罗算法类似，拉斯维加斯算法找到正确解的概率随着它所用的计算时间的增加而提高。对于所求解问
题的任一实例，用同一拉斯维加斯算法反复对该实例求解足够多次，可使求解失败的概率任意小。拉斯维加斯算法的一个显
著特征是它所作的随机性决策有可能导致算法找不到所需的解。
2、n后问题
问题描速：在n×n格的棋盘上放置彼此不受攻击的n个皇后。按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列
或同一斜线上的棋子。n后问题等价于在n×n格的棋盘上放置n个皇后，任何2个皇后不放在同一行或同一列或同一斜线上。
*/
//随机化算法 拉斯维加斯算法 n后问题
#include "stdafx.h"
#include"RandomNumber.h"
#include<cmath>
#include<iostream>
using namespace std;

class Queen
{
	friend void nQueen(int);
private:
	bool Place(int k);//测试皇后k置于x[k]列的合法性
	bool Queenslv(void);//随机放置n个皇后拉斯维加斯算法
	int n;//皇后个数
	int *x, *y;//解向量
};
//测试皇后k置于第x[k]列的合法性
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
//随机放置n个皇后的拉斯维加斯算法
bool Queen::Queenslv(void)
{
	RandomNumber rnd;//随机数产生器
	int k = 1;//下一个皇后编号
	int count = 1;//在一列中可放置皇后的个数
	while ((k <= n) && (count > 0))
	{
		count = 0;
		for (int i = 0; i <= n; i++)
		{
			x[k] = i;//位置
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
	return (count > 0);//count>0表示放置成功
}
//解n后问题的拉斯维加斯算法
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
	//反复调用随机放置n个皇后的拉斯维加斯算法，直到成功
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
	cout << n << "皇后问题的解为：" << endl;
	nQueen(n);
	return 0;
}

