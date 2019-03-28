#pragma once
#include<iostream>
using namespace std;

class CStack
{
public:
	// CStack() CStack(int)
	CStack(int size = 3) // 构造函数，给对象成员变量进行初始化
	{
		cout << this << " CStack(int)" << endl;
		mtop = 0;
		msize = size;
		mpstack = new int[msize];
	}
	// 拷贝构造对象 默认做的是浅拷贝
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
	// 赋值重载函数  stack1 = stack1
	void operator=(const CStack &src)
	{
		cout << "operator=" << endl;

		// 防止自赋值
		if (this == &src)
			return;

		// 先释放this指向对象现有的外部资源
		delete[]mpstack;

		// 根据src引用的对象资源尺寸，重新开辟空间，拷贝数据
		mpstack = new int[src.msize];
		for (int i = 0; i < src.msize; ++i)
		{
			mpstack[i] = src.mpstack[i];
		}
		mtop = src.mtop;
		msize = src.msize;
	}
	~CStack() // 析构函数，释放对象
	{
		cout << this << " ~CStack()" << endl;
		delete[]mpstack;
		mpstack = nullptr;
	}
	void push(int val) // 入栈
	{
		if (full())
			resize();
		mpstack[mtop++] = val;
	}
	void pop() // 出栈
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
				cout << "栈中存有：" << val << endl;
				return;
			}	
		}
		cout << "查无此数" << endl;
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
	int *mpstack; // 存储栈的数据
	int mtop; // 表示栈顶下标
	int msize; // 表示栈的总长度

	void resize()
	{
		int *ptmp = new int[msize * 2];
		//memcpy(ptmp, mpstack, sizeof(int)*msize);
		//realloc  对象扩容禁止使用realloc/memcpy这些函数!!!
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
//	CStack(int size = 3) // 构造函数，给对象成员变量进行初始化
//	{
//		cout << this << " CStack(int)" << endl;
//		mtop = 0;
//		msize = size;
//		mpstack = new int[msize];
//	}
//	// 拷贝构造对象 默认做的是浅拷贝
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
//	// 赋值重载函数  stack1 = stack1
//	void operator=(const CStack &src)
//	{
//		cout << "operator=" << endl;
//
//		// 防止自赋值
//		if (this == &src)
//			return;
//
//		// 先释放this指向对象现有的外部资源
//		delete[]mpstack;
//
//		// 根据src引用的对象资源尺寸，重新开辟空间，拷贝数据
//		mpstack = new int[src.msize];
//		for (int i = 0; i < src.msize; ++i)
//		{
//			mpstack[i] = src.mpstack[i];
//		}
//		mtop = src.mtop;
//		msize = src.msize;
//	}
//	~CStack() // 析构函数，释放对象
//	{
//		cout << this << " ~CStack()" << endl;
//		delete[]mpstack;
//		mpstack = nullptr;
//	}
//	void push(int val) // 入栈
//	{
//		if (full())
//			resize();
//		mpstack[mtop++] = val;
//	}
//	void pop() // 出栈
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
//	int *mpstack; // 存储栈的数据
//	int mtop; // 表示栈顶下标
//	int msize; // 表示栈的总长度
//
//	void resize()
//	{
//		int *ptmp = new int[msize * 2];
//		//memcpy(ptmp, mpstack, sizeof(int)*msize);
//		//realloc  对象扩容禁止使用realloc/memcpy这些函数!!!
//		for (int i = 0; i < msize; ++i)
//		{
//			ptmp[i] = mpstack[i];
//		}
//		delete[]mpstack;
//		mpstack = ptmp;
//		msize *= 2;
//	}
//};