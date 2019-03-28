#pragma once
#include<iostream>
using namespace std;
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
	void inseartHead(int val)
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
	void select(int val)
	{
		Node *ppre = mphead;
		Node *pcur = mphead->mpnext;
		while (pcur != nullptr)
		{
			if (pcur->mdata == val)
			{
				cout << "�����д��У�" << val << endl;
				return;
			}
			else
			{
				ppre = pcur;
				pcur = pcur->mpnext;
			}
		}
		cout << "���޴���" << endl;
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
	int getSize()
	{
		Node *pcur = mphead;
		int len = -1;
		while (pcur != nullptr)
		{
			pcur = pcur->mpnext;
			++len;
		}
		return len;
	}
	int* getLinkDatas(int &length)
	{
		length = getSize();
		int *p = new int[length];
		int k = length-1;
		Node *pcur = mphead->mpnext;
		while (pcur != nullptr)
		{
			p[k--] = pcur->mdata;
			pcur = pcur->mpnext;
		}
		return p;
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