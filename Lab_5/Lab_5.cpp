#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <fstream>
#include <conio.h>

//#include "List.h"
//#include "Header.h"
using namespace std;

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

	inline ~List()
	{
		DelAll();
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


struct Element
{
	char eng[64] = { "\0" }, ukr[64] = { "\0" };
	int request = 0;  //number of requests to this translation

	Element* left, * right, * parent;

	Element()
	{
		request = -1;
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	Element(char eng[64], char ukr[64], int req)
	{
		strcpy(this->eng, eng);
		strcpy(this->ukr, ukr);
		request = req;
		left = NULL;
		right = NULL;
		parent = NULL;
	}

	~Element()
	{

	}

	void operator = (const Element& el)
	{
		for (int i = 0; i < 64 && (el.eng[i] != '\0' || el.ukr[i] != '\0'); i++)
		{
			eng[i] = el.eng[i];
			ukr[i] = el.ukr[i];
		}
		request = el.request;
		left = el.left;
		right = el.right;
		parent = el.parent;
	}

	bool operator != (const Element& el)
	{
		for (int i = 0; i < 64 && (el.eng[i] != '\0' || el.ukr[i] != '\0'); i++)
		{
			if (eng[i] != el.eng[i] && ukr[i] != el.ukr[i])
				return true;
		}
		if (request = el.request)
			return true;

		return false;
	}

	bool operator ! ()
	{
		for (int i = 0; i < 64; i++)
		{
			if (eng[i] != '\0' && ukr[i] != '\0')
				return true;
		}

		return false;
	}
};

bool CompareStrByAlph(char str1[64], char str2[64])
{
	for (int i = 0; i < 64; i++)
	{
		if (strlen(str1) == i || strlen(str2) == i)
			if (strlen(str1) < strlen(str2))
				return true;
			else
				return false;

		if (str1[i] < str2[i])
			return true;
		else if (str1[i] != str2[i])
			return false;
	}

	return false;
}

bool CompareStr(char str1[64], char str2[64])
{
	for (int i = 0; str1[i] > 0 && str2[i] > 0; i++)
	{
		if (str1[i] != str2[i])
			return false;

		if (str1[i + 1] < 0 && str2[i + 1] > 0 || str2[i + 1] < 0 && str1[i + 1] > 0)
			return false;
	}

	return true;
}

struct Tree
{
	Element* root;
	int count = 0;
	Tree()
	{
		root = new Element();
	}

	~Tree()
	{
		Del(root);
	}

	void Print(Element* Node)
	{
		if (Node != 0)
		{
			Print(Node->left);
			cout << "Eng: " << Node->eng << endl << "Ukr: " << Node->ukr << endl << "Requests: " << Node->request << endl << endl;
			Print(Node->right);
		}
	}

	void GetElementByOrder(Element* Node, List& arrNodes)
	{
		if (Node != 0)
		{
			Element tmp = *Node;
			tmp.left = NULL;
			tmp.right = NULL;
			tmp.parent = NULL;
			GetElementByOrder(Node->left, arrNodes);
			int pos = 1;
			bool flag = true;
			if (arrNodes.GetCount() != 0)
			{
				for (int i = 0; i < arrNodes.GetCount(); i++)
				{
					if (Node->request < arrNodes.GetElem(i + 1)->data.request && Node->eng != arrNodes.GetElem(i + 1)->data.eng)
						pos++;
					else
					{
						flag = false;
						arrNodes.Insert(pos, tmp);
						break;
					}
				}
				if (flag)
					arrNodes.AddLast(tmp);
			}
			else
				arrNodes.AddFirst(tmp);
			GetElementByOrder(Node->right, arrNodes);
		}
	}

	Element* Search(Element* Node, char* key)
	{
		while (Node != 0)
		{
			if (CompareStr(key, Node->eng))
				break;
			if (CompareStrByAlph(key, Node->eng))
				Node = Node->left;
			else
				Node = Node->right;
		}

		Node->request++;
		cout << "Eng: " << endl
			<< Node->eng << endl << "Ukr: " << endl
			<< Node->ukr << endl << "Requests: " << endl
			<< Node->request << endl;

		return Node;
	}

	Element* Min(Element* Node)
	{
		if (Node != 0)
			while (Node->left != 0)
				Node = Node->left;
		return Node;
	}

	Element* Max(Element* Node)
	{
		if (Node != 0)
			while (Node->right != 0)
				Node = Node->right;
		return Node;
	}

	Element* Next(Element* Node)
	{
		Element* temp = 0;
		if (Node != 0)
		{
			if (Node->right != 0)
				return Min(Node->right);
			temp = Node->parent;
			while (temp != 0 && Node == temp->right)
			{
				Node = temp;
				temp = temp->parent;
			}
		}
		return temp;
	}

	Element* Previous(Element* Node)
	{
		Element* temp = 0;
		if (Node != 0)
		{
			if (Node->left != 0)
				return Max(Node->left);
			temp = Node->parent;
			while (temp != 0 && Node == temp->left)
			{
				Node = temp;
				temp = temp->parent;
			}
		}
		return temp;
	}

	Element* GetRoot()
	{
		return root;
	}

	void Insert(Element Elementent)
	{
		count++;
		Element* temp = NULL;
		Element* Node = root;

		if (root->request != -1)
			while (Node != 0)
			{
				temp = Node;
				if (CompareStrByAlph(Elementent.eng, Node->eng) > 0)
					Node = Node->left;
				else
					Node = Node->right;
			}

		Elementent.parent = temp;

		if (temp == 0)
			*root = Elementent;
		else if (CompareStrByAlph(Elementent.eng, temp->eng) > 0)
		{
			temp->left = new Element();
			*temp->left = Elementent;
		}
		else
		{
			temp->right = new Element();
			*temp->right = Elementent;
		}
	}

	void Del(Element* Elementent)
	{
		if (Elementent != 0)
		{
			count--;
			Element* Node, * temp;

			Elementent->left == 0 || Elementent->right == 0 ? temp = Elementent : temp = Next(Elementent);

			temp->left != 0 ? Node = temp->left : Node = temp->right;

			if (Node != 0)
				Node->parent = temp->parent;

			if (temp->parent == 0)
				root = Node;
			else if (temp == temp->parent->left)
				temp->parent->left = Node;
			else
				temp->parent->right = Node;

			if (temp != Elementent)
			{
				strcpy(Elementent->eng, temp->eng);
				strcpy(Elementent->ukr, temp->ukr);
				Elementent->request = temp->request;
			}
			delete temp;
		}
		else while (root != 0)
			Del(root);
	}
};



int main()
{

	return 0;
}
