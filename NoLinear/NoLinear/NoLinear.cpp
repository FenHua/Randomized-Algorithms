/*NoLinear.cpp : 定义控制台应用程序的入口点。
解非线性方程组
在指定求根区域D内，选定一个随机点x0作为随机搜索的出发点。在算法的搜索过程中，假设第j步随机搜
索得到的随机搜索点为xj。在第j+1步，计算出下一步的随机搜索增量dxj。从当前点xj依dxj得到第j+1步的
随机搜索点。当x<epsilon时，取为所求非线性方程组的近似解。否则进行下一步新的随机搜索过程。
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<iostream>
using namespace std;

bool NonLinear(double *x0, double*dx0, double *x, double a0,
	double epsilon, double k, int n, int Steps, int M);
double f(double*x, int n);


int main()
{
	double*x0,//根初值
		*x,//根
		*dx0,//增量初值
		a0 = 0.0001,//步长
		epsilon = 0.01,//精度
		k = 1.1;//步长变参
	int n = 2,//方程的个数
		Steps = 10000,//执行次数
		M = 1000;//失败次数
	x0 = new double[n + 1];
	dx0 = new double[n + 1];
	x = new double[n + 1];
	x0[1] = 0.0;
	x0[2] = 0.0;//根初值
	dx0[1] = 0.01;
	dx0[2] = 0.01;//增量初值
	cout << "原方程组为" << endl;
	cout << "x1-x2=1" << endl;
	cout << "x1+x2=3" << endl;
	cout << "此方程的根为：" << endl;
	bool flag = NonLinear(x0, dx0, x, a0, epsilon, k, n, Steps, M);
	while (!flag)//直到解满足epsilon时停止
	{
		bool flag = NonLinear(x0, dx0, x, a0, epsilon, k, n, Steps, M);
	}
	for (int i = 1; i <= n; i++)
	{
		cout << "x" << i << "=" << x[i] << " ";
	}
	cout << endl;
	return 0;
}

//解非线性方程组的随机化算法
bool NonLinear(double*x0, double*dx0, double *x, double a0,
	double epsilon, double k, int n, int Steps, int M)
{
	static RandomNumber rnd;
	bool success;//搜索成功标志
	double *dx, *r;
	dx = new double[n + 1];//步进增量向量
	r = new double[n + 1];//搜索方向向量
	int mm = 0;//当前搜索失败的次数
	int j = 0;//迭代的次数
	double a = a0;//步长因子
	for (int i = 1; i <= n; i++)
	{
		x[i] = x0[i];
		dx[i] = dx0[i];
	}
	double fx = f(x, n);//计算目标函数值
	double min = fx;//当前最优值
	while (j<Steps)
	{
		if (fx < min)//搜索成功
		{
			min = fx;
			a *= k;//步长改变
			success = true;
		}
		else//搜索失败
		{
			mm++;
			if (mm>M)
			{
				a /= k;
			}
			success = false;
		}
		if (min < epsilon)
		{
			break;
		}
		//计算随机搜索方向和增量
		for (int i = 0; i <= n; i++)
		{
			r[i] = 2.0*rnd.fRandom() - 1;
		}
		if (success)//更新增量的大小
		{
			for (int i = 1; i <= n; i++)
			{
				dx[i] = a*r[i];
			}
		}
		else
		{
			for (int i = 1; i <= n; i++)
			{
				dx[i] = a*r[i] - dx[i];//反向改变增量
			}
		}
		//计算搜索点的大小
		for (int i = 1; i <= n; i++)
		{
			x[i] += dx[i];
		}
		//计算目标函数值
		fx = f(x, n);
		j++;
	}
	if (fx <= epsilon)
	{
		return true;
	}
	else
	{
		return false;
	}
}
double f(double*x, int n)
{
	return (x[1] - x[2] - 1)*(x[1] - x[2] - 1) + (x[1] + x[2] - 3)*(x[1] + x[2] - 3);
}