/*RandomNumber.cpp : �������̨Ӧ�ó������ڵ㡣
�ü����������α�������ģ����Ӳ�����顣������10��Ӳ�ң�ÿ����Ӳ�ҵõ�����ͷ���������ġ�
��10��Ӳ�ҹ���һ���¼�������Random(2)����һ����ֵ��������������з������ú���TossCoinsģ
�⒁10��Ӳ����һ�¼�50000�Ρ���head[i](0<=i<=10)��¼��50000��ģ��ǡ�õõ�i������Ĵ��֡�
�������ģ����Ӳ���¼��õ��������¼��ĸ���ͼ��
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<iostream>
using namespace std;

int TossCoins(int numberCoins);


int main()
{
	//ģ�������Ӳ���¼�
	const int NCOINS= 10;
	const long NTOSSES = 5000L;
	//head[i]�õ�i������Ĵ���
	long j, heads[NCOINS + 1];
	int position;
	//��ʼ������heads
	for (int j = 0; j < NCOINS + 1; j++)
	{
		heads[j] = 0;
	}
	//�ظ�50000��ģ���¼�
	for (int i = 0; i < NTOSSES; i++)
	{
		heads[TossCoins(NCOINS)]++;
	}
	//���Ƶ��ͼ
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
	//�����Ӳ��
	static RandomNumber coinToss;
	int i, tosses = 0;
	for (int i = 0; i < numberCoins; i++)
	{
		tosses += coinToss.Random(2);//1��ʾ����
	}
	return tosses;
}