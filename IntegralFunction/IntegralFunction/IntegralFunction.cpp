/*IntegralFunction.cpp : 定义控制台应用程序的入口点。
1)随机投点法计算定积分
基本思想是在矩形区域上随机均匀的投点实现。本算法的基本思想是在积分区间上随机均匀的产生
点, 即在[a,b]上随机均匀的取点, 求出由这些点产生的函数值的算术平均值, 再乘以区间宽度
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<iostream>
using namespace std;

//double Darts(int n, double a, double b);
double Darts(int n, double a, double b, double d);
double f(double x);

int main()
{
	int n1 = 100, n2 = 1000, n3 = 1000, n4 = 10000, n5 = 10000000;
	double a = 2.0, b = 3.0;
	double d = f(b);
	/*
	cout << "n1=" << n1 << ",r1=" << Darts(n1, a, b) << endl;
	cout << "n2=" << n2 << ",r2=" << Darts(n2, a, b) << endl;
	cout << "n3=" << n3 << ",r3=" << Darts(n3, a, b) << endl;
	cout << "n4=" << n4 << ",r4=" << Darts(n4, a, b) << endl;
	cout << "n5=" << n5 << ",r5=" << Darts(n5, a, b) << endl;
	*/
	cout << "n1=" << n1 << ",r1=" << Darts(n1, a, b, d) << endl;
	cout << "n2=" << n2 << ",r2=" << Darts(n2, a, b, d) << endl;
	cout << "n3=" << n3 << ",r3=" << Darts(n3, a, b, d) << endl;
	cout << "n4=" << n4 << ",r4=" << Darts(n4, a, b, d) << endl;
	cout << "n5=" << n5 << ",r5=" << Darts(n5, a, b, d) << endl;
	return 0;
}

/*
基本思想是在矩形区域内随机均匀投点，求出由这些点产生的函数的算术平均值
再乘以区间宽度，即可得出定积分的近似解
*/
/*
double Darts(int n, double a, double b)
{
	static RandomNumber dart;
	double sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		double x = (b - a)*dart.fRandom() + a;//产生[a,b)之间的随机数
		sum = sum + f(x);
	}
	return (b - a)*sum / n;
}
*/
double f(double x)
{
	return x*x;
}
/*
f为积分函数，n为投票总数，a,b为积分区间，c,d为函数f的值域的端点值
*/
double Darts(int n, double a, double b, double d)
{
	static RandomNumber dart;
	int k = 0;
	for (int i = 0; i < n; i++)
	{
		double x = (b - a)*dart.fRandom() + a;
		double y = d*dart.fRandom();
		if (y <= f(x))
		{
			k++;
		}
	}
	return d*(b - a)*k / n;//d为右端点
}
