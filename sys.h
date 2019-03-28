#pragma once
#include"CCircleQueue.h"
#include"Link.h"
#include"stack.h"
class DSSystem
{
public:
	void run() // ϵͳ����������
	{
		// 1.�����ļ��е�����
		loading();
		// 2.��ʾ���˵�
		while(1)
		{
			cout << "-------------" << endl;
			cout << "1.������" << endl;
			cout << "2.ջ" << endl;
			cout << "3.����" << endl;
			cout << "4.�˳�ϵͳ" << endl;
			cout << "-------------" << endl;
			cout << "��ѡ��:";
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
				cout << "����������...";
				// �������ݣ�д���ļ�
				savedata();
				cout << "����ɹ�����ӭ�´�ʹ�ã�" << endl;
				system("pause");
				return;
			}
		}
	}

	void loading()//��������
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

	void savedata()//��������
	{
		// ��ʾ���ݽṹ���ص�����ĳ���
		int length = 0;

		// �����������ݽṹ link.dat  stack.dat  queue.dat
		FILE *pf1;
		 fopen_s(&pf1,"link.dat", "wb");
		if (pf1 == nullptr) return;

		int *p1 = mlink.getLinkDatas(length);
		fwrite(p1,sizeof(int),length,pf1);
		fclose(pf1);
		delete[]p1;

		//����stack
		int stacklength = 0;
		FILE *pf2;
		fopen_s(&pf2, "stack.dat", "wb");
		if (pf2 == nullptr) return;

		int *p2 = mstack.getStackDatas(stacklength);
		fwrite(p2, sizeof(int), stacklength, pf2);
		fclose(pf2);
		delete[]p2;

		//����queue
		int queuelength = 0;
		FILE *pf3;
		fopen_s(&pf3, "queue.dat", "wb");
		if (pf3 == nullptr) return;

		int *p3 = mqueue.getQueueDatas(queuelength);
		fwrite(p3, sizeof(int), queuelength, pf3);
		fclose(pf3);
		delete[]p3;
	}

	void runChild() // ��ӡ�����˵�
	{
		//int choice = 0;
		cout << "-------------" << endl;
		cout << "��ǰѡ������ݽṹ��:" << "xxx" << endl;
		cout << "1.�鿴" << endl;
		cout << "2.����" << endl;
		cout << "3.ɾ��" << endl;
		cout << "4.��ѯ" << endl;
		cout << "5.����" << endl;
		cout << "-------------" << endl;
		cout << "��ѡ��:";
		//cin >> choice;
		
	}

	void slink()//��������˵� ����
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
					cout << "ָ�����,���������룡����" << endl;
			}
			
		}
	}

	void scirclequeue()//�������
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
					cout << "ָ�����,���������룡����" << endl;				
			}			
		}
	}

	void sstack()//����ջ
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
					cout << "ָ�����,���������룡����" << endl;
			}
		}
	}

	void mlinkInseartHead()//����ͷ��
	{
		int tmp = 0;
		cin >> tmp;
		mlink.inseartHead(tmp);
	}

	void mlinkRemove()//����ɾ��
	{
		int tmp = 0;
		cin >> tmp;
		mlink.remove(tmp);
	}

	void mlinkselect()//�����ѯ
	{
		int val;
		cin >> val;
		mlink.select(val);
	}

	void mqueuepush()//���в���
	{
		int tmp = 0;
		cin >> tmp;
		mqueue.push(tmp);
	}
	
	void mqueueselect()//���в�ѯ
	{
		int val;
		cin >> val;
		mqueue.select(val);
	}

	void sstackpush()//ջ����
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

	int mDsChoice; // ��ʾ���˵�ѡ������ݽṹ
};
