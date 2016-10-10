/*PrimeMC.cpp : �������̨Ӧ�ó������ڵ㡣
3��������������
��ѧԭ��
Wilson�������ڸ�����������n���ж�n��һ�������ĳ�Ҫ������(n-1)! -1(mod n)��
�Ѷ���С�������p��һ����������0<a<p����a^(p-1)(mod p)��
����̽�ⶨ�����p��һ����������0<x<p���򷽳�x^21(mod p)�Ľ�Ϊx=1��p-1��
Carmichael�����Ѷ���С�����������ж���һ����Ҫ����������Ѷ���С��������������nδ��ȫ��������
��Щ����Ҳ����Ѷ���С�������������Щ������ΪCarmichael����ǰ3��Carmichael����561,1105��1729��
Carmichael���Ƿǳ��ٵģ���1~100000000�������У�ֻ��255��Carmichael����
��a^m(mod n)���㷨
��m�Ķ����Ʊ�ʾΪbkbk-1��b1b0��bk=1����
����m=41=101001(2)��bkbk-1��b1b0=101001����k=5����
������������a^m����ʼC��1��
b5=1��C��C^2(=1)����bk=1����C��a*C(=a)��
b5b4=10��C��C^2(=a^2)����bk-1=0������������
b5b4b3=101��C��C^2(=a^4)����bk-2=1����C��a*C(=a^5)��
b5b4b3b2=1010��C��C^2(=a^10)����bk-3= b2=0������������
b5b4b3b2b1=10100��C��C^2(=a^20)����bk-4= b1=0������������
b5b4b3b2b1b0=101001��C��C^2(=a^40)����bk-5= b0=1����C��a*C(=a^41)��
����Ҫ��am��ģ������ģ�������뵽�����е�ÿһ����
�������C2��a*C֮������žͶ�������ֵ��ģ��Ȼ���ٴ���C��
�������ĺô��Ǵ洢��C�е����ֵ������n-1��
���Ǽ�������ֵ������max{(n-1)^2,a(n-1)}��
��ˣ�����am�ܴ���am(mod n)ʱҲ����ռ�úܶ�ռ䡣
*/
//������㷨���ؿ����㷨 ������������
#include "stdafx.h"
#include"RandomNumber.h"
#include<cmath>
#include<iostream>
using namespace std;
//����a^p mod n,��ʵʩ��n�Ķ���̽��
void power(unsigned int a, unsigned int p, unsigned int n, unsigned int&result, bool &composite)
{
	unsigned int x;
	if (p == 0)
	{
		result = 1;
	}
	else
	{
		power(a, p / 2, n, x, composite);//�ݹ����
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
//�ظ�����k��Prime�㷨�����ؿ����㷨
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
		cout << i << "���������Խ��Ϊ��" << PrimeMC(i, k) <<endl;
	}
	return 0;
}

