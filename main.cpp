
#include<stdio.h>
#include <iostream>

/*
类  =》  描述实体类型的
类占不占空间   类 =》实例化=》对象《=》实体

类=》很多对象   都有自己的一份成员变量 栈  堆  .data   共享成员方法.text

成员方法调用 =》 用对象.成员方法（） this指针接收调用方法的对象  this->

C： 封装（隐藏） 类的访问限定符  public    private
struct Data{}  public
class Data{}   private
struct和class定义类的区别是？？？
C语言的空结构体  sizeof(Data)   0
C++的空类       sizeof(Data)   1
*/
// CGoods 描述 商品类型
// OOP实现一个顺序栈   实体  属性（成员变量）和行为（成员方法）
#include <iostream>
#include <time.h>
using namespace std;

/*
构造和析构函数
1.函数名字和类名相同
2.函数没有返回值
3.析构函数不能带参数，只能由一个析构函数
4.构造函数可以带任意参数，所以构造函数可以重载


空结构体 0  struct Data{} struct Data data;
空类  1
class Test

Test t;
开辟空间
构造函数

为什么面向对象使用过程中，扩容不能用realloc，memcpy这样的内存操作函数?
*/
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
	int top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop - 1];
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }
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
int main2()
{
	// 1.开闭内存  2.调用构造函数
	CStack stack;  // 
	// CStack(stack)  CStack(const CStack &src)
	CStack stack1 = stack;  // 结构体变量互相赋值，初始化

	// stack1.=(stack) void operator=(const CStack &src)
	stack1 = stack;

	//CStack stack2(20);  // CStack(int)
	//CStack stack3(); // C++ 仅仅定义了一个函数声明而已
	//“.push”的左边必须有类/结构/联合
	//stack3.push(20);
	/*
	srand(time(NULL));
	for (int i = 0; i < 10; ++i)
	{
		stack.push(rand()%100+1);
	}

	while (!stack.empty())
	{
		int top = stack.top();
		cout << top << " ";
		stack.pop();
	}
	cout << endl;
	*/
	return 0; // 栈上的对象需要自动调用析构函数
}

// 用OOP实现一个循环队列
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

	void addQue(int val) // 入队
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
	bool full() { return (mrear + 1) % msize == mfront; } // 判满
	bool empty() { return mrear == mfront; } // 判空

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
#if 0
int main()
{
	CCircleQueue queue;
	srand(time(NULL));
	for (int i = 0; i < 20; ++i)
	{
		queue.addQue(rand() % 100);
	}

	while (!queue.empty())
	{
		int front = queue.front();
		cout << front << " ";
		queue.delQue();
	}
	cout << endl;

	return 0;
}
#endif
// OOP实现一个链表结构
class Link
{
public:
	Link() // 构造函数
	{
		mphead = new Node(); // new Node;
	}
	~Link() // 析构函数
	{
		Node *pcur = mphead;
		while (pcur != nullptr)
		{
			mphead = mphead->mpnext;
			delete pcur;
			pcur = mphead;
		}
	}
	void insertHead(int val)
	{
		Node *ptmp = new Node(val); // Node node(val);
		ptmp->mpnext = mphead->mpnext;
		mphead->mpnext = ptmp;
	}
	void insertTail(int val)
	{
		Node *pcur = mphead;
		while (pcur->mpnext != nullptr)
		{
			pcur = pcur->mpnext;
		}
		pcur->mpnext = new Node(val);
	}
	void remove(int val) // 删除所有值为val的节点
	{
		Node *ppre = mphead;
		Node *pcur = mphead->mpnext;

		while (pcur != nullptr)
		{
			if (pcur->mdata == val)
			{
				ppre->mpnext = pcur->mpnext;
				delete pcur;
				pcur = ppre->mpnext;
			}
			else
			{
				ppre = pcur;
				pcur = pcur->mpnext;
			}
		}
	}
	void show()
	{
		Node *pcur = mphead->mpnext;
		while (pcur != nullptr)
		{
			cout << pcur->mdata << " ";
			pcur = pcur->mpnext;
		}
		cout << endl;
	}
private:
	// 节点类型
	struct Node
	{
		Node(int data = 0)
		{
			mdata = data;
			mpnext = nullptr;
		}
		int mdata;
		Node *mpnext;
	};

	// private化拷贝构造和赋值重载函数
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};

/*
软件运行如下：
加载数据当中...加载完成！
-------------
1.单链表
2.栈
3.队列
4.退出系统 => 保存内存数据
-------------
请选择：1

-------------
当前数据结构是：xxx
1.查看
2.增加
3.删除
4.查询
5.返回上一级菜单
-------------
请选择：
*/
// 数据结构系统类
class DSSystem
{
public:
	void run() // 系统的启动函数
	{
		// 1.加载文件中的数据
		
		// 2.显示主菜单
		cout << "-------------" << endl;
		cout << "1.单链表" << endl;
		cout << "2.栈" << endl;
		cout << "3.队列" << endl;
		cout << "4.退出系统" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> mDsChoice;

		switch (mDsChoice)
		{
		case 1:Link;
		case 2:CStack;
		case 3:CCircleQueue;
			runChild();
			break;
		case 4:
			cout << "保存数据中...";
			// 保存数据，写入文件
			cout << "保存成功！欢迎下次使用！" << endl;
			return;
		}
	}

	void runChild() // 系统二级菜单的启动函数
	{
		int choice = 0;

		cout << "-------------" << endl;
		cout << "当前选择的数据结构是:" << "xxx" << endl;
		cout << "1.查看" << endl;
		cout << "2.增加" << endl;
		cout << "3.删除" << endl;
		cout << "4.查询" << endl;
		cout << "5.返回" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		cin >> choice;
		switch (choice)
		{
		case1:void show();
		case2:void insertHead();
		case3:void remove(int val);
		case4:;
		case5:void run();
		}
	}
private:
	CStack mstack;
	CCircleQueue mqueue;
	Link mlink;

	int mDsChoice; // 表示主菜单选择的数据结构
};

int main()
{
	DSSystem sys;
	sys.run();

	return 0;
}
