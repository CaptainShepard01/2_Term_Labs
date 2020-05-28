#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Element.h"

bool CompareStrByAlph(char str1[64], char str2[64]);
bool CompareStr(char str1[64], char str2[64]);

struct Elem
{
	Element data;
	Elem* next, * prev;
};

struct List
{
	Elem* Head, * Tail;

	int Count; //number of List nodes

	inline List()
	{
		Head = NULL; Tail = NULL; Count = 0;
	}

	inline List(const List& L)
	{
		Head = Tail = NULL;
		Count = 0;

		Elem* temp = new Elem;
		temp = L.Head;

		while (temp != 0)
		{
			AddLast(temp->data);
			temp = temp->next;
		}
	}

	inline void AddFirst(Element n)
	{
		Elem* temp = new Elem;

		temp->prev = 0;

		temp->data = n;

		temp->next = Head;

		if (Head != 0)
			Head->prev = temp;

		if (Count == 0)
			Head = Tail = temp;
		else
			Head = temp;

		Count++;
	}
	inline void AddLast(Element n)
	{
		Elem* temp = new Elem;

		temp->next = 0;

		temp->data = n;

		temp->prev = Tail;

		if (Tail != 0)
			Tail->next = temp;

		if (Count == 0)
			Head = Tail = temp;
		else
			Tail = temp;

		Count++;
	}

	bool IsCorrectPosition(int pos, int Count)
	{
		if (pos<1 || pos>Count + 1)return 0;
		return 1;
	}

	inline void Insert(int pos, Element data)
	{
		if (pos == 0)
		{
			cout << "Input position: ";
			cin >> pos;
		}

		if (!IsCorrectPosition(pos, Count))
		{
			cout << "Incorrect position !!!\n";
			return;
		}

		if (pos == Count + 1)
		{
			AddLast(data);
			return;
		}
		else if (pos == 1)
		{
			AddFirst(data);
			return;
		}

		int i = 1;

		Elem* Ins = Head;
		while (i < pos)
		{
			Ins = Ins->next;
			i++;
		}

		Elem* PrevIns = Ins->prev;

		Elem* temp = new Elem;

		temp->data = data;

		if (PrevIns != 0 && Count != 1)
			PrevIns->next = temp;
		temp->next = Ins;
		temp->prev = PrevIns;
		Ins->prev = temp;
		Count++;
	}
	inline void Del(int pos)
	{
		if (pos == 0)
		{
			cout << "Input position: ";
			cin >> pos;
		}

		if (!IsCorrectPosition(pos, Count))
		{
			cout << "Incorrect position !!!\n";
			return;
		}

		int i = 1;
		Elem* Del = Head;
		while (i < pos)
		{
			Del = Del->next;
			i++;
		}

		Elem* PrevDel = Del->prev;

		Elem* AfterDel = Del->next;

		if (PrevDel != 0 && Count != 1)	PrevDel->next = AfterDel;

		if (AfterDel != 0 && Count != 1) AfterDel->prev = PrevDel;

		if (pos == 1)	Head = AfterDel;
		if (pos == Count)	Tail = PrevDel;

		delete Del;
		Count--;
	}

	inline void DelAll()
	{
		while (Count != 0)
			Del(1);
	}
	inline int GetCount()
	{
		return Count;
	}
	inline Elem* GetElem(int pos)
	{
		Elem* temp = Head;

		if (!IsCorrectPosition(pos, Count))
		{
			cout << "Incorrect position !!!\n";
			return 0;
		}
		int i = 1;

		while (i < pos && temp != 0)
		{
			temp = temp->next;
			i++;
		}
		if (temp == 0)
			return 0;
		else
			return temp;
	}
	inline List& operator = (const List& L)
	{
		if (this == &L)
			return *this;

		this->~List();
		Elem* temp = L.Head;

		while (temp != 0)
		{
			AddLast(temp->data);
			temp = temp->next;
		}
		return *this;
	}
};
