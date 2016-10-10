/*SkipList.cpp : 定义控制台应用程序的入口点。
问题描述
如果用有序链表来表示一个含有n个元素的有序集S，则在最坏情况下，搜索S中一个元素需要O(n)计算时间。提高有序
链表效率的一个技巧是在有序链表的部分结点处增设附加指针以提高其搜索性能。在增设附加指针的有序链表中搜索一
个元素时，可借助于附加指针跳过链表中若干结点，加快搜索速度。这种增加了向前附加指针的有序链表称为跳跃表。
应在跳跃表的哪些结点增加附加指针以及在该结点处应增加多少指针完全采用随机化方法来确定。这使得跳跃表可在
O(logn)平均时间内支持关于有序集的搜索、插入和删除等运算。
在一个完全跳跃表中，具有i级指针的结点中有一半同时具有i+1级指针。为了维持跳跃表的平衡性，可以事先确定一个
实数0<p<1，并要求在跳跃表中维持在具有i级指针的结点中同时具有i+1级指针的结点所占比例约为p。为此目的，在
插入一个新结点时，先将其结点级别初始化为0，然后用随机数生成器反复地产生一个[0，1]间的随机实数q。如果q<p，
则使新结点级别增加1，直至q>=p。由此产生新结点级别的过程可知，所产生的新结点的级别为0的概率为1-p，级别为
1的概率为p(1-p)，…，级别为i的概率为p^i(1-p)。如此产生的新结点的级别有可能是一个很大的数，甚至远远超过表中
元素的个数。为了避免这种情况，用作为新结点级别的上界。其中n是当前跳跃表中结点个数。当前跳跃表中任一结点的级别不超过log(1/p)n 。
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
	EType data;//集合中的元素
	SkipNode<EType, EType>**next;//指针数组next[i]是第i级指针
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
	int MaxLevel;//跳跃表级别上界
	int Levels;//当前最大级别
	RandomNumber rnd;//随机数产生器
	float Prob;//用于分配节点级别
	KType TailKey;//元素键值上界
	SkipNode<EType, KType>*head;//头结点指针
	SkipNode<EType, KType>*NIL;//尾结点指针
	SkipNode<EType, KType>**last;//指针数组
};
//构造函数
template<class EType, class KType>SkipList<EType, KType>::SkipList(KType large, int MaxE, float p)
{
	Prob = p;
	MaxLevel = ceil(log(float(MaxE) / log(1 / p))) - 1;//初始化跳跃表的上界，cail() 返回大于或者等于指定表达式的最小整数
	TailKey = large;//元素键值上界
	Levels = 0;//初始化当前最大级别
	//创建头，尾节点和数组last
	head = new SkipNode<EType, KType>(MaxLevel + 1);
	NIL = new SkipNode<EType, KType>(0);
	last = new SkipNode<EType, KType>*[MaxLevel + 1];
	NIL->data = large;
	//将跳跃表初始化为空表
	for (int i = 0; i <= MaxLevel; i++)
	{
		head->next[i] = NIL;
	}
}
//析构函数
template<class EType, class KType>SkipList<EType, KType>::~SkipList()
{
	SkipNode<EType, KType>*next;
	//删除所有节点
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
//搜索指定元素K
template<class EType, class KType> bool SkipList<EType, KType>::Search(const KType&k, EType&e)const
{
	if (k >= TailKey)
	{
		return false;
	}
	//位置p恰好位于指定元素k之前
	SkipNode<EType,KType>*p = head;
	for (int i = Levels; i >= 0; i--)//逐渐向下搜索
	{
		while (p->next[i]->data < k)//在第i级链中搜索
		{
			p = p->next[i];//每次搜索尽可能滴接近要搜索的元素
		}
	}
	e = p->next[0]->data;
	return(e == k);
}
//搜索指定元素k，并将每一级中遇到的上一个节点存放在数组last中
template<class EType, class KType> SkipNode<EType, KType>* SkipList<EType, KType>::SaveSearch(const KType&k)
{
	//位置p恰好位于指定元素k之前
	SkipNode<EType, KType>*p = head;
	for (int i = Levels; i >= 0; i--)
	{
		while (p->next[i]->data < k)
		{
			p = p->next[i];
		}
		last[i] = p;//上一个第i级结点
	}
	return (p->next[0]);
}
//产生不超过MaxLevel的随机级别
template<class EType, class KType>int SkipList<EType, KType>::level()
{
	int lev = 0;
	while (rnd.fRandom() < Prob)
	{
		lev++;
	}
	return (lev <= MaxLevel) ? lev : MaxLevel;
}
//插入指定元素e
template<class EType, class KType>
SkipList<EType, KType>& SkipList<EType, KType>::Insert(const EType&e)
{
	KType k = e;//取得元素键值
	if (k >= TailKey)
	{
		cout << "元素键值超界！" << endl;
		return *this;
	}
	//检查元素是否已存在
	SkipNode<EType, KType>*p = SaveSearch(k);
	if (p->data == e)
	{
		cout << "元素已存在！" << endl;
		return *this;
	}
	//元素不存在，确定新的节点级别
	int lev = level();
	//调整个级别指针
	if (lev > Levels)
	{
		for (int i = Levels + 1; i <= lev; i++)
		{
			last[i] = head;
		}
		Levels = lev;
	}
	//产生新节点，并将新的节点插入p之后
	SkipNode<EType, KType>*y = new SkipNode<EType, KType>(lev + 1);
	y->data = e;
	for (int i = 0; i <= lev; i++)
	{
		//插入第i级链
		y->next[i] = last[i]->next[i];
		last[i]->next[i] = y;
	}
	return *this;
}
//删除键值为k的元素，并将所删除的元素存入e
template<class EType, class KType>SkipList<EType,KType>& SkipList<EType, KType>::Delete(const KType&k, EType&e)
{
	if (k >= TailKey)
	{
		cout << "元素键值超界！" << endl;
	}
	//搜索待删除元素
	SkipNode<EType, KType>*p = SaveSearch(k);
	if (p->data != k)
	{
		cout << "未找到待删除元素！" << endl;
	}
	//从跳跃表中删除节点
	for (int i = 0; i < Levels&&last[i]->next[i] == p; i++)
	{
		last[i]->next[i] = p->next[i];
	} 
	//更新当前级别
	while (Levels>0 && head->next[Levels]==NIL)
	{
		Levels--;
	}
	e = p->data;
	delete p;
	return *this;
}
//输出集合中的元素
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
	//创建
	cout << "==========创建==============" << endl;
	int a[] = { 5, 3, 2, 11, 7, 13, 19, 17, 23 };
	for (int i = 0; i < 9; i++)
	{
		s->Insert(a[i]);
	}
	s->Output();
	//搜索
	cout << "=============搜索============" << endl;
	int k = 17, e;
	cout << "搜索元素k=" << k << "如下：" << endl;
	if (s->Search(17, e))
	{
		cout << "位置搜索结果为：k=" << k << ",e=" << e;
	}
	cout << endl;
	//删除
	cout << "================删除=============" << endl;
	cout << "删除跳跃表元素k=" << k << "剩余元素如下：" << endl;
	s->Delete(k, e);
	s->Output();
	delete s;
	return 0;
}
