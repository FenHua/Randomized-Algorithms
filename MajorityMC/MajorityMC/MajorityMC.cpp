/*MajorityMC.cpp : 定义控制台应用程序的入口点。
1、蒙特卡罗算法
基本概述
蒙特卡罗（Monte Carlo）方法，又称随机抽样或统计试验方法。传统的经验方法由于不能逼近真实的物理过
程，很难得到满意的结果，而蒙特卡罗方法由于能够真实地模拟实际物理过程，故解决问题与实际非常符合，可
以得到很圆满的结果。在实际应用中常会遇到一些问题，不论采用确定性算法或随机化算法都无法保证每次都
能得到正确的解答。蒙特卡罗算法则在一般情况下可以保证对问题的所有实例都以高概率给出正确解，但是通
常无法判定一个具体解是否正确。
原理思想
当所要求解的问题是某种事件出现的概率，或者是某个随机变量的期望值时，它们可以通过某种“试验”的方法，得
到这种事件出现的频率，或者这个随机变数的平均值，并用它们作为问题的解。这就是蒙特卡罗方法的基本思想。蒙特
卡罗方法通过抓住事物运动的几何数量和几何特征，利用数学方法来加以模拟，即进行一种数字模拟实验。它是以一个
概率模型为基础，按照这个模型所描绘的过程，通过模拟实验的结果，作为问题的近似解。
主要步骤：1.构造或者描述概率过程 2.实现从已知概率分布抽样3.建立各种估计量
2、主元素问题
问题描述
设T[1:n]是一个含有n个元素的数组。当|{i|T[i]=x}|>n/2时，称元素x是数组T的主元素。 例如：数组T[]={5,5,5,5,5,5,1,3,4,6}
中，元素T[0:5]为数组T[]的主元素。
问题求解
算法随机选择数组元素x,由于数组T的非主元素个数小于n/2，所以，x不为主元素的概率小于1/2。因此判定数组T的主元素存
在性的算法是一个偏真1/2正确的算法。50%的错误概率是不可容忍的，利用重复调用技术将错误概率降低到任何可接受的范
围内。对于任何给定的>0，算法majorityMC重复调用次算法majority。
*/
#include "stdafx.h"
#include"RandomNumber.h"
#include<cmath>
#include<iostream>
using namespace std;

//判定主元素的蒙特卡罗算法
template<class Type>bool Majority(Type*T, int n)
{
	RandomNumber rnd;
	int i = rnd.Random(n);
	Type x = T[i];//随机选择数组元素
	int k = 0;
	for (int j = 0; j < n; j++)
	{
		if (T[j] == x)
		{
			k++;
		}
	}
	return (k>n / 2);//k>n/2时，T含有主元素
}
//重复k次调用算法Majority
template<class Type>bool MajorityMC(Type*T, int n, double e)
{
	int k = ceil(log(1 / e) / log((float)2));
	for (int i = 1; i <= k; i++)
	{
		if (Majority(T, n))
			return true;
	}
	return false;
}
int main()
{
	int n = 10;
	float e = 0.001;
	int a[] = { 5, 5, 5, 5, 5, 5, 1, 3, 4, 6 };
	cout << "数组a的元素如下：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	cout << "调用MajorityMC判断数组是否含有主元素结果是：" << MajorityMC(a, n, e) << endl;
	return 0;
}

