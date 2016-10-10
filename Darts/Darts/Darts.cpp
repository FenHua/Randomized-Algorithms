/*Darts.cpp : �������̨Ӧ�ó������ڵ㡣
�����ֵ
����һ�뾶Ϊr��Բ���������ı��Ρ���������������Ͷ��n���㡣������Բ�ڵĵ���Ϊk��
������Ͷ��ĵ����������Ͼ��ȷֲ��������Ͷ��ĵ�����Բ�ڵĸ���ΪP^2r^2/4r^2�����Ե�n�㹻��ʱ
k��n֮�Ⱦͱƽ���һ���ʡ��Ӷ�p=4k/n��
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include"iostream"
using namespace std;

double Darts(int n);


int main()
{
	int n1 = 100, n2 = 1000, n3 = 1000, n4 = 10000, n5 = 10000000;
	cout << "n1=" << n1 << ",��1=" << Darts(n1) << endl;
	cout << "n2=" << n2 << ",��2=" << Darts(n2) << endl;
	cout << "n3=" << n3 << ",��3=" << Darts(n3) << endl;
	cout << "n4=" << n4 << ",��4=" << Darts(n4) << endl;
	cout << "n5=" << n5 << ",��5=" << Darts(n5) << endl;
	return 0;
}

//�����Ͷ�㷨�����ֵ
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