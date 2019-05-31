#pragma once
#include<iostream>
#include<memory>
using namespace std;

#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
template <typename ElemType>
struct SeqList {
	ElemType *items;		//��ַ
	int length;
	int capacity;

	SeqList(int c = LIST_INIT_SIZE)
	{
		items = NULL;
		length = 0;
		resize(c);			//����ռ�
	}
	~SeqList()
	{
		//����
	}
	void resize(int c)
	{
		capacity = c;
		ElemType *newdata = new ElemType[capacity];
		if (items != NULL)
		{
			memcpy(newdata, items, length * sizeof(ElemType));
			delete[] items;
		}
		items = newdata;
	}
	void output()				//���
	{
		printf("List: ");
		for (int i = 0; i < length; i++)
			cout << items[i] ;
		cout<< endl;
	}
	void outputWithoutLenth() {		//���   ����length
		ElemType * p = items;
		while (*p >= 0 && (int)*p <= 126)
		{
			cout << *p;
			p++;
		}
		cout << endl;
	}
	void addpend(ElemType e)	
	{
		if (length == capacity)
			resize(capacity + LISTINCREMENT);
		items[length++] =e;
	}
	void deleteAt(int index)	//ɾ��index����Ԫ��
	{
		for (int i = index; i < length - 1; i++)
		{
			items[i] = items[i + 1];
		}
		length--;
	}
	void insertAt(int index, ElemType e)
	{
		for (int i = length; i > index; i--)
			items[i] = items[i - 1];
		items[index] = e;
		length++;
	}

	ElemType getElem(int index)
	{
		return items[index];
	}

	void setElem(int index, ElemType e)
	{
		items[index] = e;
	}
	void clear()		//��ղ����·���ռ�
	{
		length = 0;
		resize(LIST_INIT_SIZE);
	}
	ElemType &operator[](int index)
	{
		return items[index];
	}
};

