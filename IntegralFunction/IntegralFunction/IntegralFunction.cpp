/*IntegralFunction.cpp : �������̨Ӧ�ó������ڵ㡣
1)���Ͷ�㷨���㶨����
����˼�����ھ���������������ȵ�Ͷ��ʵ�֡����㷨�Ļ���˼�����ڻ���������������ȵĲ���
��, ����[a,b]��������ȵ�ȡ��, �������Щ������ĺ���ֵ������ƽ��ֵ, �ٳ���������
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
����˼�����ھ����������������Ͷ�㣬�������Щ������ĺ���������ƽ��ֵ
�ٳ��������ȣ����ɵó������ֵĽ��ƽ�
*/
/*
double Darts(int n, double a, double b)
{
	static RandomNumber dart;
	double sum = 0.0;
	for (int i = 0; i < n; i++)
	{
		double x = (b - a)*dart.fRandom() + a;//����[a,b)֮��������
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
fΪ���ֺ�����nΪͶƱ������a,bΪ�������䣬c,dΪ����f��ֵ��Ķ˵�ֵ
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
	return d*(b - a)*k / n;//dΪ�Ҷ˵�
}
