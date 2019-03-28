
#include<stdio.h>
#include <iostream>

/*
��  =��  ����ʵ�����͵�
��ռ��ռ�ռ�   �� =��ʵ����=������=��ʵ��

��=���ܶ����   �����Լ���һ�ݳ�Ա���� ջ  ��  .data   �����Ա����.text

��Ա�������� =�� �ö���.��Ա�������� thisָ����յ��÷����Ķ���  this->

C�� ��װ�����أ� ��ķ����޶���  public    private
struct Data{}  public
class Data{}   private
struct��class������������ǣ�����
C���ԵĿսṹ��  sizeof(Data)   0
C++�Ŀ���       sizeof(Data)   1
*/
// CGoods ���� ��Ʒ����
// OOPʵ��һ��˳��ջ   ʵ��  ���ԣ���Ա����������Ϊ����Ա������
#include <iostream>
#include <time.h>
using namespace std;

/*
�������������
1.�������ֺ�������ͬ
2.����û�з���ֵ
3.�����������ܴ�������ֻ����һ����������
4.���캯�����Դ�������������Թ��캯����������


�սṹ�� 0  struct Data{} struct Data data;
����  1
class Test

Test t;
���ٿռ�
���캯��

Ϊʲô�������ʹ�ù����У����ݲ�����realloc��memcpy�������ڴ��������?
*/
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
	int top()
	{
		if (empty())
			throw "stack is empty!";
		return mpstack[mtop - 1];
	}
	bool full() { return mtop == msize; }
	bool empty() { return mtop == 0; }
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
int main2()
{
	// 1.�����ڴ�  2.���ù��캯��
	CStack stack;  // 
	// CStack(stack)  CStack(const CStack &src)
	CStack stack1 = stack;  // �ṹ��������ำֵ����ʼ��

	// stack1.=(stack) void operator=(const CStack &src)
	stack1 = stack;

	//CStack stack2(20);  // CStack(int)
	//CStack stack3(); // C++ ����������һ��������������
	//��.push������߱�������/�ṹ/����
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
	return 0; // ջ�ϵĶ�����Ҫ�Զ�������������
}

// ��OOPʵ��һ��ѭ������
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

	void addQue(int val) // ���
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
	bool full() { return (mrear + 1) % msize == mfront; } // ����
	bool empty() { return mrear == mfront; } // �п�

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
// OOPʵ��һ������ṹ
class Link
{
public:
	Link() // ���캯��
	{
		mphead = new Node(); // new Node;
	}
	~Link() // ��������
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
	void remove(int val) // ɾ������ֵΪval�Ľڵ�
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
	// �ڵ�����
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

	// private����������͸�ֵ���غ���
	Link(const Link&);
	void operator=(const Link&);

	Node *mphead;
};

/*
����������£�
�������ݵ���...������ɣ�
-------------
1.������
2.ջ
3.����
4.�˳�ϵͳ => �����ڴ�����
-------------
��ѡ��1

-------------
��ǰ���ݽṹ�ǣ�xxx
1.�鿴
2.����
3.ɾ��
4.��ѯ
5.������һ���˵�
-------------
��ѡ��
*/
// ���ݽṹϵͳ��
class DSSystem
{
public:
	void run() // ϵͳ����������
	{
		// 1.�����ļ��е�����
		
		// 2.��ʾ���˵�
		cout << "-------------" << endl;
		cout << "1.������" << endl;
		cout << "2.ջ" << endl;
		cout << "3.����" << endl;
		cout << "4.�˳�ϵͳ" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
		cin >> mDsChoice;

		switch (mDsChoice)
		{
		case 1:Link;
		case 2:CStack;
		case 3:CCircleQueue;
			runChild();
			break;
		case 4:
			cout << "����������...";
			// �������ݣ�д���ļ�
			cout << "����ɹ�����ӭ�´�ʹ�ã�" << endl;
			return;
		}
	}

	void runChild() // ϵͳ�����˵�����������
	{
		int choice = 0;

		cout << "-------------" << endl;
		cout << "��ǰѡ������ݽṹ��:" << "xxx" << endl;
		cout << "1.�鿴" << endl;
		cout << "2.����" << endl;
		cout << "3.ɾ��" << endl;
		cout << "4.��ѯ" << endl;
		cout << "5.����" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
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

	int mDsChoice; // ��ʾ���˵�ѡ������ݽṹ
};

int main()
{
	DSSystem sys;
	sys.run();

	return 0;
}
