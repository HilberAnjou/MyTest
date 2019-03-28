#pragma once
#include<iostream>
using namespace std;

class CCircleQueue
{
public:
	CCircleQueue(int size = 10) // ���캯��
	{
		msize = size;
		mfront = mrear = 0;
		mpQue = new int[msize];
	}
	~CCircleQueue() // ��������
	{
		delete[]mpQue;
		mpQue = nullptr;
	}
	CCircleQueue(const CCircleQueue &src) // �������캯��
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
	void operator=(const CCircleQueue &src) // ��ֵ���غ���
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

	void push(int val) // ���
	{
		if (full())
			resize();
		mpQue[mrear] = val;
		mrear = (mrear + 1) % msize;
	}
	void delQue() // ����
	{
		if (empty())
			return;
		mfront = (mfront + 1) % msize;
	}
	int front() // ���ض�ͷԪ��
	{
		return mpQue[mfront];
	}
	int back() // ���ض�βԪ��
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
				cout << "�������У�" << val << endl;
				return;
			}
		}
		cout << "���޴���" << endl;
	}
	bool full() { return (mrear + 1) % msize == mfront; } // ����
	bool empty() { return mrear == mfront; } // �п�
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
	int *mpQue; //�������Ԫ�ص����ݽṹ
	int mfront; //��ͷ�±�
	int mrear; //��β�±�
	int msize; //���ݵ��ܳ���

	void resize() // 2������ѭ������
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