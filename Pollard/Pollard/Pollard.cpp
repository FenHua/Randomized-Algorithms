/*Pollard.cpp : �������̨Ӧ�ó������ڵ㡣
��������
��n>1��һ����������������n�����ӷֽ��������ҳ�n��������ʽ��Ψһ�ֽ�ʽ��
���У�p1<p2<��<pk��k��������m1,m2,��,mk��k�������������n��һ��������
��n����һ����ƽ������x��1<x<n��ʹ��x��������n������һ������n����n��һ��
��ƽ�����ӵ������Ϊ����n�����ӷָ����⡣
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
Pollard p - 1 ������Pollard ��1974 ������������ҵ���������n��һ������d��Pollard�㷨����Split(n)��ͬ
�������Ϳ��Եõ���1��x^4��Χ�����������ӷָ����������£��ڿ�ʼʱѡȡ0��n-1��Χ�ڵ��������Ȼ
��ݹ���ɲ����������ж���i=2^k���Լ�2^k<j<=2^(k+1)���㷨�����xj-xi��n���������d=gcd(xj-xi��
n)�����d��n�ķ�ƽ�����ӣ���ʵ�ֶ�n��һ�ηָ�㷨���n������d��
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<iostream>
using namespace std;
//������a��b�����������ŷ������㷨
int gcd(int a, int b)
{
	if (b == 0)
		return a;
	else
		return gcd(b, a%b);
}
//������n���ӷָ����˹ά��˹�㷨
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
			cout << d << endl;//���ӷָ����⣬��n��1���Ƿ����ӵ�����
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
	cout << n << "�ķǷ����ӣ�" << endl;
	Pollard(n);
	return 0;
}

