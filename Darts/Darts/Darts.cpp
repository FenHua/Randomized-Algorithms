/*Darts.cpp : 定义控制台应用程序的入口点。
计算π值
设有一半径为r的圆及其外切四边形。向该正方形随机地投掷n个点。设落入圆内的点数为k。
由于所投入的点在正方形上均匀分布，因而所投入的点落入圆内的概率为P^2r^2/4r^2。所以当n足够大时
k与n之比就逼近这一概率。从而p=4k/n。
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include"iostream"
using namespace std;

double Darts(int n);


int main()
{
	int n1 = 100, n2 = 1000, n3 = 1000, n4 = 10000, n5 = 10000000;
	cout << "n1=" << n1 << ",π1=" << Darts(n1) << endl;
	cout << "n2=" << n2 << ",π2=" << Darts(n2) << endl;
	cout << "n3=" << n3 << ",π3=" << Darts(n3) << endl;
	cout << "n4=" << n4 << ",π4=" << Darts(n4) << endl;
	cout << "n5=" << n5 << ",π5=" << Darts(n5) << endl;
	return 0;
}

//用随机投点法计算π值
double Darts(int n)
{
	static RandomNumber dart;
	int k = 0;
	for (int i = 1; i <= n; i++)
	{
		double x = dart.fRandom();
		double y = dart.fRandom();
		if ((x*x + y*y) <= 1)
		{
			k++;
		}
	}
	return 4 * k / double(n);
}