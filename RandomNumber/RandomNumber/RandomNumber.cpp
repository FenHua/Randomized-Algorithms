/*RandomNumber.cpp : 定义控制台应用程序的入口点。
用计算机产生的伪随机数来模拟抛硬币试验。假设抛10次硬币，每次抛硬币得到正面和反面是随机的。
拋10次硬币构成一个事件。调用Random(2)返回一个二值结果。在主程序中反复调用函数TossCoins模
拟拋10次硬币这一事件50000次。用head[i](0<=i<=10)记录这50000次模拟恰好得到i次正面的刺手。
最终输出模拟抛硬币事件得到的正面事件的概率图。
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<iostream>
using namespace std;

int TossCoins(int numberCoins);


int main()
{
	//模拟随机抛硬币事件
	const int NCOINS= 10;
	const long NTOSSES = 5000L;
	//head[i]得到i次正面的次数
	long j, heads[NCOINS + 1];
	int position;
	//初始化数组heads
	for (int j = 0; j < NCOINS + 1; j++)
	{
		heads[j] = 0;
	}
	//重复50000次模拟事件
	for (int i = 0; i < NTOSSES; i++)
	{
		heads[TossCoins(NCOINS)]++;
	}
	//输出频率图
	for (int i = 0; i <= NCOINS; i++)
	{
		position = int(float(heads[i]) / NTOSSES * 72);
		cout << i << " ";
		for (int j = 0; j < position - 1; j++)
		{
			cout << " ";
		}
		cout << "*" << endl;
	}
	return 0;
}

int TossCoins(int numberCoins)
{
	//随机抛硬币
	static RandomNumber coinToss;
	int i, tosses = 0;
	for (int i = 0; i < numberCoins; i++)
	{
		tosses += coinToss.Random(2);//1表示正面
	}
	return tosses;
}