/*Pollard.cpp : 定义控制台应用程序的入口点。
问题描述
设n>1是一个整数。关于整数n的因子分解问题是找出n的如下形式的唯一分解式：
其中，p1<p2<…<pk是k个素数，m1,m2,…,mk是k个正整数。如果n是一个合数，
则n必有一个非平凡因子x，1<x<n，使得x可以整除n。给定一个合数n，求n的一个
非平凡因子的问题称为整数n的因子分割问题。
int Split(int n)
{
int m = floor(sqrt(double(n)));
for (int i=2; i<=m; i++)
{
if (n%i==0)
{
return i;
}
}
return 1;
}
Pollard p - 1 方法由Pollard 于1974 年提出，用来找到给定合数n的一个因子d。Pollard算法用于Split(n)相同
工作量就可以得到在1～x^4范围内整数的因子分割。具体过程如下：在开始时选取0～n-1范围内的随机数，然
后递归地由产生无穷序列对于i=2^k，以及2^k<j<=2^(k+1)，算法计算出xj-xi与n的最大公因子d=gcd(xj-xi，
n)。如果d是n的非平凡因子，则实现对n的一次分割，算法输出n的因子d。
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<iostream>
using namespace std;
//求整数a和b的最大公因数的欧几里德算法
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}
//求整数n因子分割的拉斯维加斯算法
void Pollard(int n)
{
	RandomNumber rnd;
	int i = 1; int x = rnd.Random(n);
	int y = x;
	int k = 2;
	while (true)
	{
		i++;
		x = (x*x - 1) % n;//x[i]=(x[i-1]^2-1)mod n
		int d = gcd(y - x, n);
		if ((d > 1) && (d < n))
		{
			cout << d << endl;//因子分割问题，求n的1个非凡因子的问题
			return;
		}
		if (i == k)
		{
			y = x;
			k *= 2;
		}
	}
}
int main()
{
	int n = 1024;
	cout << n << "的非凡因子：" << endl;
	Pollard(n);
	return 0;
}

