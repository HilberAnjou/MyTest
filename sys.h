#pragma once
#include"CCircleQueue.h"
#include"Link.h"
#include"stack.h"
class DSSystem
{
public:
	void run() // 系统的启动函数
	{
		// 1.加载文件中的数据
		loading();
		// 2.显示主菜单
		while(1)
		{
			cout << "-------------" << endl;
			cout << "1.单链表" << endl;
			cout << "2.栈" << endl;
			cout << "3.队列" << endl;
			cout << "4.退出系统" << endl;
			cout << "-------------" << endl;
			cout << "请选择:";
			int mDsChoice;
			cin >> mDsChoice;
			switch (mDsChoice)
			{
			case 1:slink();
				break;
			case 2:sstack();
				break;
			case 3:scirclequeue();
				break;
			case 4:
				cout << "保存数据中...";
				// 保存数据，写入文件
				savedata();
				cout << "保存成功！欢迎下次使用！" << endl;
				system("pause");
				return;
			}
		}
	}

	void loading()//加载数据
	{
		FILE *pf1;
		fopen_s(&pf1, "link.dat", "rb");
		if (pf1 != nullptr)
		{
			fseek(pf1, 0, SEEK_END);
			int size = ftell(pf1);
			int number = size / sizeof(int);
			int *p = new int[number];
			fseek(pf1, 0, SEEK_SET);
			fread(p, sizeof(int),number,pf1);
			fclose(pf1);

			for (int i = 0; i <number; ++i)
			{
				mlink.inseartHead(p[i]);
			}
			delete[]p;
		}

		FILE *pf2;
		fopen_s(&pf2, "stack.dat", "rb");
		if (pf2 != nullptr)
		{
			fseek(pf2, 0, SEEK_END);
			int size = ftell(pf2);
			int number = size / sizeof(int);
			int *p2 = new int[number];
			fseek(pf2, 0, SEEK_SET);
			fread(p2, sizeof(int), number, pf2);
			fclose(pf2);

			for (int i = 0; i < number; ++i)
			{
				mstack.push(p2[i]);
			}
			delete[]p2;
		}

		FILE *pf3;
		fopen_s(&pf3, "queue.dat", "rb");
		if (pf3 != nullptr)
		{
			fseek(pf3, 0, SEEK_END);
			int size = ftell(pf3);
			int number = size / sizeof(int);
			int *p3 = new int[number];
			fseek(pf3, 0, SEEK_SET);
			fread(p3, sizeof(int), number, pf3);
			fclose(pf3);

			for (int i = 0; i < number; ++i)
			{
				mqueue.push(p3[i]);
			}
			delete[]p3;
		}
	}

	void savedata()//保存数据
	{
		// 表示数据结构返回的数组的长度
		int length = 0;

		// 保存三个数据结构 link.dat  stack.dat  queue.dat
		FILE *pf1;
		 fopen_s(&pf1,"link.dat", "wb");
		if (pf1 == nullptr) return;

		int *p1 = mlink.getLinkDatas(length);
		fwrite(p1,sizeof(int),length,pf1);
		fclose(pf1);
		delete[]p1;

		//保存stack
		int stacklength = 0;
		FILE *pf2;
		fopen_s(&pf2, "stack.dat", "wb");
		if (pf2 == nullptr) return;

		int *p2 = mstack.getStackDatas(stacklength);
		fwrite(p2, sizeof(int), stacklength, pf2);
		fclose(pf2);
		delete[]p2;

		//保存queue
		int queuelength = 0;
		FILE *pf3;
		fopen_s(&pf3, "queue.dat", "wb");
		if (pf3 == nullptr) return;

		int *p3 = mqueue.getQueueDatas(queuelength);
		fwrite(p3, sizeof(int), queuelength, pf3);
		fclose(pf3);
		delete[]p3;
	}

	void runChild() // 打印二级菜单
	{
		//int choice = 0;
		cout << "-------------" << endl;
		cout << "当前选择的数据结构是:" << "xxx" << endl;
		cout << "1.查看" << endl;
		cout << "2.增加" << endl;
		cout << "3.删除" << endl;
		cout << "4.查询" << endl;
		cout << "5.返回" << endl;
		cout << "-------------" << endl;
		cout << "请选择:";
		//cin >> choice;
		
	}

	void slink()//进入二级菜单 链表
	{
		while (1)
		{
			runChild(); //oudput list
			int choice = 0;
			cin >> choice;
			switch (choice)
			{
				case 1: mlink.show();
					break;
				case 2: mlinkInseartHead();
					break;
				case 3: mlinkRemove();
					break;
				case 4: mlinkselect();
					break;
				case 5: return;
				default:
					cout << "指令错误,请重新输入！！！" << endl;
			}
			
		}
	}

	void scirclequeue()//进入队列
	{
		while (1)
		{
			runChild();
			int choice = 0;
			cin >> choice;
			switch (choice)
			{
				case 1: mqueue.show();
					break;
				case 2: mqueuepush();
					break;
				case 3: mqueue.delQue();
					break;
				case 4: mqueueselect();
					break;
				case 5: return;
				default:
					cout << "指令错误,请重新输入！！！" << endl;				
			}			
		}
	}

	void sstack()//进入栈
	{
		while (1)
		{
			runChild();
			int choice = 0;
			cin >> choice;
			switch (choice)
			{
				case 1: mstack.show();
					break;
				case 2: sstackpush();
					break;
				case 3: mstack.pop();
					break;
				case 4: mstackselect();
					break;
				case 5: return;
				default:
					cout << "指令错误,请重新输入！！！" << endl;
			}
		}
	}

	void mlinkInseartHead()//链表头插
	{
		int tmp = 0;
		cin >> tmp;
		mlink.inseartHead(tmp);
	}

	void mlinkRemove()//链表删除
	{
		int tmp = 0;
		cin >> tmp;
		mlink.remove(tmp);
	}

	void mlinkselect()//链表查询
	{
		int val;
		cin >> val;
		mlink.select(val);
	}

	void mqueuepush()//队列插入
	{
		int tmp = 0;
		cin >> tmp;
		mqueue.push(tmp);
	}
	
	void mqueueselect()//队列查询
	{
		int val;
		cin >> val;
		mqueue.select(val);
	}

	void sstackpush()//栈插入
	{
		int tmp = 0;
		cin >> tmp;
		mstack.push(tmp);
	}

	void mstackselect()
	{
		int val;
		cin >> val;
		mstack.select(val);
	}
private:
	CStack mstack;
	CCircleQueue mqueue;
	Link mlink;

	int mDsChoice; // 表示主菜单选择的数据结构
};
