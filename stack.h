#pragma once
#include<iostream>
using namespace std;

class CStack
{
public:
	// CStack() CStack(int)
	CStack(int size = 3) // ���캯�����������Ա�������г�ʼ��
	{
		cout << this << " CStack(int)" << endl;
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	// ����������� Ĭ��������ǳ����
	CStack(const CStack &src)
	{
		cout << this << "CStack(const CStack&)" << endl;
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	// ��ֵ���غ���  stack1 = stack1
	void operator=(const CStack &src)
	{
		cout << "operator=" << endl;

		// ��ֹ�Ը�ֵ
		if (this == &src)
			return;

		// ���ͷ�thisָ��������е��ⲿ��Դ
		delete[]mpstack;

		// ����src���õĶ�����Դ�ߴ磬���¿��ٿռ䣬��������
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	~CStack() // �����������ͷŶ���
	{
		cout << this << " ~CStack()" << endl;
		delete[]mpstack;
		mpstack = nullptr;
	}
	void push(int val) // ��ջ
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // ��ջ
	{
		if (empty())
			return;
		--mtop;
	}
	void show()
	{
		for (int i = 0; i < mtop; i++)
		{
			cout << mpstack[i] << " ";
		}
		cout << endl;
	}
	void select(int val)
	{
		for (int i = 0; i < mtop; i++)
		{
			if (mpstack[i] == val)
			{
				cout << "ջ�д��У�" << val << endl;
				return;
			}	
		}
		cout << "���޴���" << endl;
	}
	int top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop - 1];
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }

	int *getStackDatas(int &stacklength)
	{
		stacklength = mtop;
		int *p = new int[stacklength];
		int k = stacklength -1;
		for (int k = 0; k < stacklength; k++)
		{
			p[k] = mpstack[k];
		}
		return p;
	}
private:
	int *mpstack; // �洢ջ������
	int mtop; // ��ʾջ���±�
	int msize; // ��ʾջ���ܳ���

	void resize()
	{
		int *ptmp = new int[msize * 2];
		//memcpy(ptmp, mpstack, sizeof(int)*msize);
		//realloc  �������ݽ�ֹʹ��realloc/memcpy��Щ����!!!
		for (int i = 0; i < msize; ++i)
		{
			ptmp[i] = mpstack[i];
		}
		delete[]mpstack;
		mpstack = ptmp;
		msize *= 2;
	}
};
//class CStack
//{
//public:
//	// CStack() CStack(int)
//	CStack(int size = 3) // ���캯�����������Ա�������г�ʼ��
//	{
//		cout << this << " CStack(int)" << endl;
//		mtop = 0;
//		msize = size;
//		mpstack = new int[msize];
//	}
//	// ����������� Ĭ��������ǳ����
//	CStack(const CStack &src)
//	{
//		cout << this << "CStack(const CStack&)" << endl;
//		mpstack = new int[src.msize];
//		for (int i = 0; i < src.msize; ++i)
//		{
//			mpstack[i] = src.mpstack[i];
//		}
//		mtop = src.mtop;
//		msize = src.msize;
//	}
//	// ��ֵ���غ���  stack1 = stack1
//	void operator=(const CStack &src)
//	{
//		cout << "operator=" << endl;
//
//		// ��ֹ�Ը�ֵ
//		if (this == &src)
//			return;
//
//		// ���ͷ�thisָ��������е��ⲿ��Դ
//		delete[]mpstack;
//
//		// ����src���õĶ�����Դ�ߴ磬���¿��ٿռ䣬��������
//		mpstack = new int[src.msize];
//		for (int i = 0; i < src.msize; ++i)
//		{
//			mpstack[i] = src.mpstack[i];
//		}
//		mtop = src.mtop;
//		msize = src.msize;
//	}
//	~CStack() // �����������ͷŶ���
//	{
//		cout << this << " ~CStack()" << endl;
//		delete[]mpstack;
//		mpstack = nullptr;
//	}
//	void push(int val) // ��ջ
//	{
//		if (full())
//			resize();
//		mpstack[mtop++] = val;
//	}
//	void pop() // ��ջ
//	{
//		if (empty())
//			return;
//		--mtop;
//	}
//	int top()
//	{
//		if (empty())
//			throw "stack is empty!";
//		return mpstack[mtop - 1];
//	}
//	bool full() { return mtop == msize; }
//	bool empty() { return mtop == 0; }
//private:
//	int *mpstack; // �洢ջ������
//	int mtop; // ��ʾջ���±�
//	int msize; // ��ʾջ���ܳ���
//
//	void resize()
//	{
//		int *ptmp = new int[msize * 2];
//		//memcpy(ptmp, mpstack, sizeof(int)*msize);
//		//realloc  �������ݽ�ֹʹ��realloc/memcpy��Щ����!!!
//		for (int i = 0; i < msize; ++i)
//		{
//			ptmp[i] = mpstack[i];
//		}
//		delete[]mpstack;
//		mpstack = ptmp;
//		msize *= 2;
//	}
//};