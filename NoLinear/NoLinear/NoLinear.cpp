/*NoLinear.cpp : �������̨Ӧ�ó������ڵ㡣
������Է�����
��ָ���������D�ڣ�ѡ��һ�������x0��Ϊ��������ĳ����㡣���㷨�����������У������j�������
���õ������������Ϊxj���ڵ�j+1�����������һ���������������dxj���ӵ�ǰ��xj��dxj�õ���j+1����
��������㡣��x<epsilonʱ��ȡΪ��������Է�����Ľ��ƽ⡣���������һ���µ�����������̡�
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
	double*x0,//����ֵ
		*x,//��
		*dx0,//������ֵ
		a0 = 0.0001,//����
		epsilon = 0.01,//����
		k = 1.1;//�������
	int n = 2,//���̵ĸ���
		Steps = 10000,//ִ�д���
		M = 1000;//ʧ�ܴ���
	x0 = new double[n + 1];
	dx0 = new double[n + 1];
	x = new double[n + 1];
	x0[1] = 0.0;
	x0[2] = 0.0;//����ֵ
	dx0[1] = 0.01;
	dx0[2] = 0.01;//������ֵ
	cout << "ԭ������Ϊ" << endl;
	cout << "x1-x2=1" << endl;
	cout << "x1+x2=3" << endl;
	cout << "�˷��̵ĸ�Ϊ��" << endl;
	bool flag = NonLinear(x0, dx0, x, a0, epsilon, k, n, Steps, M);
	while (!flag)//ֱ��������epsilonʱֹͣ
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

//������Է������������㷨
bool NonLinear(double*x0, double*dx0, double *x, double a0,
	double epsilon, double k, int n, int Steps, int M)
{
	static RandomNumber rnd;
	bool success;//�����ɹ���־
	double *dx, *r;
	dx = new double[n + 1];//������������
	r = new double[n + 1];//������������
	int mm = 0;//��ǰ����ʧ�ܵĴ���
	int j = 0;//�����Ĵ���
	double a = a0;//��������
	for (int i = 1; i <= n; i++)
	{
		x[i] = x0[i];
		dx[i] = dx0[i];
	}
	double fx = f(x, n);//����Ŀ�꺯��ֵ
	double min = fx;//��ǰ����ֵ
	while (j<Steps)
	{
		if (fx < min)//�����ɹ�
		{
			min = fx;
			a *= k;//�����ı�
			success = true;
		}
		else//����ʧ��
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
		//��������������������
		for (int i = 0; i <= n; i++)
		{
			r[i] = 2.0*rnd.fRandom() - 1;
		}
		if (success)//���������Ĵ�С
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
				dx[i] = a*r[i] - dx[i];//����ı�����
			}
		}
		//����������Ĵ�С
		for (int i = 1; i <= n; i++)
		{
			x[i] += dx[i];
		}
		//����Ŀ�꺯��ֵ
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