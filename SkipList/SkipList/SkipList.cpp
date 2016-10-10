/*SkipList.cpp : �������̨Ӧ�ó������ڵ㡣
��������
�����������������ʾһ������n��Ԫ�ص�����S�����������£�����S��һ��Ԫ����ҪO(n)����ʱ�䡣�������
����Ч�ʵ�һ������������������Ĳ��ֽ�㴦���踽��ָ����������������ܡ������踽��ָ�����������������һ
��Ԫ��ʱ���ɽ����ڸ���ָ���������������ɽ�㣬�ӿ������ٶȡ�������������ǰ����ָ������������Ϊ��Ծ��
Ӧ����Ծ�����Щ������Ӹ���ָ���Լ��ڸý�㴦Ӧ���Ӷ���ָ����ȫ���������������ȷ������ʹ����Ծ�����
O(logn)ƽ��ʱ����֧�ֹ������򼯵������������ɾ�������㡣
��һ����ȫ��Ծ���У�����i��ָ��Ľ������һ��ͬʱ����i+1��ָ�롣Ϊ��ά����Ծ���ƽ���ԣ���������ȷ��һ��
ʵ��0<p<1����Ҫ������Ծ����ά���ھ���i��ָ��Ľ����ͬʱ����i+1��ָ��Ľ����ռ����ԼΪp��Ϊ��Ŀ�ģ���
����һ���½��ʱ���Ƚ����㼶���ʼ��Ϊ0��Ȼ��������������������ز���һ��[0��1]������ʵ��q�����q<p��
��ʹ�½�㼶������1��ֱ��q>=p���ɴ˲����½�㼶��Ĺ��̿�֪�����������½��ļ���Ϊ0�ĸ���Ϊ1-p������Ϊ
1�ĸ���Ϊp(1-p)����������Ϊi�ĸ���Ϊp^i(1-p)����˲������½��ļ����п�����һ���ܴ����������ԶԶ��������
Ԫ�صĸ�����Ϊ�˱����������������Ϊ�½�㼶����Ͻ硣����n�ǵ�ǰ��Ծ���н���������ǰ��Ծ������һ���ļ��𲻳���log(1/p)n ��
*/

#include "stdafx.h"
#include"RandomNumber.h"
#include<cmath>
#include"iostream"
using namespace std;

template<class EType, class KType>class SkipList;
template<class EType, class KType>class SkipNode
{
	friend  class SkipList<EType, KType>;
private:
	SkipNode(int size)
	{
		next = new SkipNode<EType, KType>*[size];
	}
	~SkipNode()
	{
		delete[]next;
	}
	EType data;//�����е�Ԫ��
	SkipNode<EType, EType>**next;//ָ������next[i]�ǵ�i��ָ��
};
template<class EType, class KType>class SkipList
{
public:
	SkipList(KType large, int MaxE = 10000, float p = 0.5);
	~SkipList();
	bool Search(const KType&k, EType&e)const;
	SkipList<EType, KType>& Insert(const EType&e);
	SkipList<EType, KType>& Delete(const KType&k, EType&e);
	void Output();
private:
	int level();
	SkipNode<EType, KType>*SaveSearch(const KType&k);
	int MaxLevel;//��Ծ�����Ͻ�
	int Levels;//��ǰ��󼶱�
	RandomNumber rnd;//�����������
	float Prob;//���ڷ���ڵ㼶��
	KType TailKey;//Ԫ�ؼ�ֵ�Ͻ�
	SkipNode<EType, KType>*head;//ͷ���ָ��
	SkipNode<EType, KType>*NIL;//β���ָ��
	SkipNode<EType, KType>**last;//ָ������
};
//���캯��
template<class EType, class KType>SkipList<EType, KType>::SkipList(KType large, int MaxE, float p)
{
	Prob = p;
	MaxLevel = ceil(log(float(MaxE) / log(1 / p))) - 1;//��ʼ����Ծ����Ͻ磬cail() ���ش��ڻ��ߵ���ָ�����ʽ����С����
	TailKey = large;//Ԫ�ؼ�ֵ�Ͻ�
	Levels = 0;//��ʼ����ǰ��󼶱�
	//����ͷ��β�ڵ������last
	head = new SkipNode<EType, KType>(MaxLevel + 1);
	NIL = new SkipNode<EType, KType>(0);
	last = new SkipNode<EType, KType>*[MaxLevel + 1];
	NIL->data = large;
	//����Ծ���ʼ��Ϊ�ձ�
	for (int i = 0; i <= MaxLevel; i++)
	{
		head->next[i] = NIL;
	}
}
//��������
template<class EType, class KType>SkipList<EType, KType>::~SkipList()
{
	SkipNode<EType, KType>*next;
	//ɾ�����нڵ�
	while (head != NIL)
	{
		next = head->next[0];
		delete head;
		head = next;
	}
	delete NIL;
	delete[]last;
}
class element
{
	friend int main(void);
public:
	operator long()const
	{
		return key;
	}
	element&operator=(long y)
	{
		key = y;
		return *this;
	}
private:
	int data;
	long key;
};
//����ָ��Ԫ��K
template<class EType, class KType> bool SkipList<EType, KType>::Search(const KType&k, EType&e)const
{
	if (k >= TailKey)
	{
		return false;
	}
	//λ��pǡ��λ��ָ��Ԫ��k֮ǰ
	SkipNode<EType,KType>*p = head;
	for (int i = Levels; i >= 0; i--)//����������
	{
		while (p->next[i]->data < k)//�ڵ�i����������
		{
			p = p->next[i];//ÿ�����������ܵνӽ�Ҫ������Ԫ��
		}
	}
	e = p->next[0]->data;
	return(e == k);
}
//����ָ��Ԫ��k������ÿһ������������һ���ڵ���������last��
template<class EType, class KType> SkipNode<EType, KType>* SkipList<EType, KType>::SaveSearch(const KType&k)
{
	//λ��pǡ��λ��ָ��Ԫ��k֮ǰ
	SkipNode<EType, KType>*p = head;
	for (int i = Levels; i >= 0; i--)
	{
		while (p->next[i]->data < k)
		{
			p = p->next[i];
		}
		last[i] = p;//��һ����i�����
	}
	return (p->next[0]);
}
//����������MaxLevel���������
template<class EType, class KType>int SkipList<EType, KType>::level()
{
	int lev = 0;
	while (rnd.fRandom() < Prob)
	{
		lev++;
	}
	return (lev <= MaxLevel) ? lev : MaxLevel;
}
//����ָ��Ԫ��e
template<class EType, class KType>
SkipList<EType, KType>& SkipList<EType, KType>::Insert(const EType&e)
{
	KType k = e;//ȡ��Ԫ�ؼ�ֵ
	if (k >= TailKey)
	{
		cout << "Ԫ�ؼ�ֵ���磡" << endl;
		return *this;
	}
	//���Ԫ���Ƿ��Ѵ���
	SkipNode<EType, KType>*p = SaveSearch(k);
	if (p->data == e)
	{
		cout << "Ԫ���Ѵ��ڣ�" << endl;
		return *this;
	}
	//Ԫ�ز����ڣ�ȷ���µĽڵ㼶��
	int lev = level();
	//����������ָ��
	if (lev > Levels)
	{
		for (int i = Levels + 1; i <= lev; i++)
		{
			last[i] = head;
		}
		Levels = lev;
	}
	//�����½ڵ㣬�����µĽڵ����p֮��
	SkipNode<EType, KType>*y = new SkipNode<EType, KType>(lev + 1);
	y->data = e;
	for (int i = 0; i <= lev; i++)
	{
		//�����i����
		y->next[i] = last[i]->next[i];
		last[i]->next[i] = y;
	}
	return *this;
}
//ɾ����ֵΪk��Ԫ�أ�������ɾ����Ԫ�ش���e
template<class EType, class KType>SkipList<EType,KType>& SkipList<EType, KType>::Delete(const KType&k, EType&e)
{
	if (k >= TailKey)
	{
		cout << "Ԫ�ؼ�ֵ���磡" << endl;
	}
	//������ɾ��Ԫ��
	SkipNode<EType, KType>*p = SaveSearch(k);
	if (p->data != k)
	{
		cout << "δ�ҵ���ɾ��Ԫ�أ�" << endl;
	}
	//����Ծ����ɾ���ڵ�
	for (int i = 0; i < Levels&&last[i]->next[i] == p; i++)
	{
		last[i]->next[i] = p->next[i];
	} 
	//���µ�ǰ����
	while (Levels>0 && head->next[Levels]==NIL)
	{
		Levels--;
	}
	e = p->data;
	delete p;
	return *this;
}
//��������е�Ԫ��
template<class EType, class KType>void SkipList<EType, KType>::Output()
{
	SkipNode<EType, KType>*y = head->next[0];
	for (; y != NIL; y = y->next[0])
	{
		cout << y->data<<" ";
	}
	cout << endl;
}
int main()
{
	SkipList<int, int>*s = new SkipList<int, int>(100, 10, 0.5);
	//����
	cout << "==========����==============" << endl;
	int a[] = { 5, 3, 2, 11, 7, 13, 19, 17, 23 };
	for (int i = 0; i < 9; i++)
	{
		s->Insert(a[i]);
	}
	s->Output();
	//����
	cout << "=============����============" << endl;
	int k = 17, e;
	cout << "����Ԫ��k=" << k << "���£�" << endl;
	if (s->Search(17, e))
	{
		cout << "λ���������Ϊ��k=" << k << ",e=" << e;
	}
	cout << endl;
	//ɾ��
	cout << "================ɾ��=============" << endl;
	cout << "ɾ����Ծ��Ԫ��k=" << k << "ʣ��Ԫ�����£�" << endl;
	s->Delete(k, e);
	s->Output();
	delete s;
	return 0;
}
