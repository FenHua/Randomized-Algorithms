/*PrimeMC.cpp : 定义控制台应用程序的入口点。
3、素数测试问题
数学原理
Wilson定理：对于给定的正整数n，判定n是一个素数的充要条件是(n-1)! -1(mod n)。
费尔马小定理：如果p是一个素数，且0<a<p，则a^(p-1)(mod p)。
二次探测定理：如果p是一个素数，且0<x<p，则方程x^21(mod p)的解为x=1，p-1。
Carmichael数：费尔马小定理是素数判定的一个必要条件。满足费尔马小定理条件的整数n未必全是素数。
有些合数也满足费尔马小定理的条件，这些合数称为Carmichael数。前3个Carmichael数是561,1105，1729。
Carmichael数是非常少的，在1~100000000的整数中，只有255个Carmichael数。
求a^m(mod n)的算法
设m的二进制表示为bkbk-1…b1b0（bk=1）。
例：m=41=101001(2)，bkbk-1…b1b0=101001，（k=5）。
可以这样来求a^m：初始C←1。
b5=1：C←C^2(=1)，∵bk=1，做C←a*C(=a)；
b5b4=10：C←C^2(=a^2)，∵bk-1=0，不做动作；
b5b4b3=101：C←C^2(=a^4)，∵bk-2=1，做C←a*C(=a^5)；
b5b4b3b2=1010：C←C^2(=a^10)，∵bk-3= b2=0，不做动作；
b5b4b3b2b1=10100：C←C^2(=a^20)，∵bk-4= b1=0，不做动作；
b5b4b3b2b1b0=101001：C←C^2(=a^40)，∵bk-5= b0=1，做C←a*C(=a^41)。
最终要对am求模，而求模可以引入到计算中的每一步：
即在求得C2及a*C之后紧接着就对这两个值求模，然后再存入C。
这样做的好处是存储在C中的最大值不超过n-1，
于是计算的最大值不超过max{(n-1)^2,a(n-1)}。
因此，即便am很大，求am(mod n)时也不会占用很多空间。
*/
//随机化算法蒙特卡罗算法 素数测试问题
#include "stdafx.h"
#include"RandomNumber.h"
#include<cmath>
#include<iostream>
using namespace std;
//计算a^p mod n,并实施对n的二次探测
void power(unsigned int a, unsigned int p, unsigned int n, unsigned int&result, bool &composite)
{
	unsigned int x;
	if (p == 0)
	{
		result = 1;
	}
	else
	{
		power(a, p / 2, n, x, composite);//递归计算
		result = (x*x) % n;
		if ((result == 1) && (x != 1) && (x != n - 1))
		{
			composite = true;
		}
		if ((p % 2) == 1)
		{
			result = (result*a) % n;
		}
	}
}
//重复调用k次Prime算法的蒙特卡罗算法
bool PrimeMC(unsigned int n, unsigned int k)
{
	RandomNumber rnd;
	unsigned int a, result;
	bool composite = false;
	for (int i = 1; i <= k; i++)
	{
		a = rnd.Random(n - 3) + 2;
		power(a, n - 1, n, result, composite);
		if (composite || (result != 1))
		{
			return false;
		}
	}
	return true;
}

int main()
{
	int k = 10;
	for (int i = 1010; i < 1025; i++)
	{
		cout << i << "的素数测试结果为：" << PrimeMC(i, k) <<endl;
	}
	return 0;
}

