#pragma once
#include<iostream>
using namespace std;

class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // 构造函数
	{
		msize = size;
		mfront = mrear = 0;
		mpQue = new int[msize];
	}
	~CCircleQueue() // 析构函数
	{
		delete[]mpQue;
		mpQue = nullptr;
	}
	CCircleQueue(const CCircleQueue &src) // 拷贝构造函数
	{
		this->mpQue = new int[src.msize];
		for (int i = src.mfront;
			i != src.mrear;
			i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}
	void operator=(const CCircleQueue &src) // 赋值重载函数
	{
		if (this == &src)
			return;

		delete[]mpQue;

		this->mpQue = new int[src.msize];
		for (int i = src.mfront;
			i != src.mrear;
			i = (i + 1) % src.msize)
		{
			mpQue[i] = src.mpQue[i];
		}
		mfront = src.mfront;
		mrear = src.mrear;
		msize = src.msize;
	}

	void push(int val) // 入队
	{
		if (full())
			resize();
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;
	}
	void delQue() // 出队
	{
		if (empty())
			return;
		mfront = (mfront + 1) % msize;
	}
	int front() // 返回队头元素
	{
		return mpQue[mfront];
	}
	int back() // 返回队尾元素
	{
		return mpQue[(mrear - 1 + msize) % msize];
	}
	void show()
	{
		for (int i = mfront;
			i != mrear;
			i = (i + 1) % msize)
		{
			cout << mpQue[i] << " ";
		}
		cout << endl;
	}
	void select(int val)
	{
		for (int i = mfront;
			i != mrear;
			i = (i + 1) % msize)
		{
			if (mpQue[i] == val)
			{
				cout << "队列中有：" << val << endl;
				return;
			}
		}
		cout << "查无此数" << endl;
	}
	bool full() { return (mrear + 1) % msize == mfront; } // 判满
	bool empty() { return mrear == mfront; } // 判空
	int getlength()
	{
		int sum = 0;
		for (int i = mfront; i != mrear; i = (i + 1) % msize)
		{
			sum++;
		}
		return sum;
	}
	int *getQueueDatas(int &queuelength)
	{
		queuelength = getlength();
		int *p = new int[queuelength];
		for (int i = mfront; i != mrear; i = (i + 1) % msize)
		{
			p[i] = mpQue[i];
		}
		return p;
	}
private:
	int *mpQue; //保存队列元素的数据结构
	int mfront; //队头下标
	int mrear; //队尾下标
	int msize; //扩容的总长度

	void resize() // 2倍扩容循环队列
	{
		int *ptmp = new int[msize * 2];
		int j = 0;
		for (int i = mfront;
			i != mrear;
			i = (i + 1) % msize, j++)
		{
			ptmp[j] = mpQue[i];
		}
		delete[]mpQue;
		mpQue = ptmp;
		mfront = 0;
		mrear = j;
		msize *= 2;
	}
};