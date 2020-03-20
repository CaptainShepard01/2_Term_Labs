#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>


using namespace std;

struct Element {
	int data = 0, row = 0, column = 0;
};

struct Node {
	Element info;
	Node* next;
	Node* prev;
};

struct NodeList {
	Node* head = NULL;
	Node* tail = NULL;

	void addLast(Element i) {
		Node* node = new Node;
		node->info = i;
		node->next = NULL;
		if (head == NULL) {
			tail = node; head = node;
		}
		else {
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
	}

	Node* find(int key)
	{
		Node* cur = head;
		while (cur)
		{
			if (cur->info.data == key)break;
			cur = cur->next;
		}
		return cur;
	}

	bool remove(int key)
	{
		if (Node* pkey = find(key)) {
			if (pkey == head) {
				head = (head)->next;
				(head)->prev = 0;
			}
			else if (pkey == tail) {
				tail = (tail)->prev;
				(tail)->next = 0;
			}
			else {
				(pkey->prev)->next = pkey->next;
				(pkey->next)->prev = pkey->prev;
			}
			delete pkey;
			return true;
		}
		return false;
	}

	bool RemoveLast()
	{
		if (head == NULL) {
			cout << "There are no elements!" << endl << endl;
			return false;
		}
		else {
			Node* cur = tail;
			tail = (tail)->prev;
			(tail)->next = NULL;
			delete cur;
			cout << "Successful!" << endl;
			return true;
		}

	}

	void Print()
	{
		Node* cur = head;
		while (cur) {
			cout << cur->info.data << ' ';
			cur = cur->next;
		}
	}
	void Print_sequential(int n)
	{
		Node* cur = head;
		while(cur){
			cout << cur->info.data << " ";
			cur = cur->next;
		}
		cout << endl;
		/*for (int i = 0; i < cur->info.column;++i)cout << "0";
		cout << cur->info.data;
		for (int i = cur->info.column + 1; i < n; ++i)cout << "0";
		cout << endl;*/
		system("pause");
		return;
	}
};
