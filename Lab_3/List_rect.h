#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>


using namespace std;

struct Element_rect {
	int data = 0, row = 0, column = 0;
};

struct Node_rect {
	Element_rect info;
	Node_rect* next_right = NULL;
	Node_rect* prev_left = NULL;
	Node_rect* next_down = NULL;
	Node_rect* prev_up = NULL;
};

struct NodeList_rect {
	Node_rect* head = NULL;
	Node_rect* tail = NULL;

	void addLast(Element_rect i) {
		Node_rect* node = new Node_rect;
		node->info = i;
		node->next_right = NULL;
		node->next_down = NULL;
		if (head == NULL) {
			tail = node; head = node;
		}
		else {
			node->prev = tail;
			tail->next = node;
			tail = node;
		}
	}

	Node_rect* find(int key)
	{
		Node_rect* cur = head;
		while (cur)
		{
			if (cur->info.data == key)break;
			cur = cur->next;
		}
		return cur;
	}

	bool remove(int key)
	{
		if (Node_rect * pkey = find(key)) {
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
			Node_rect* cur = tail;
			tail = (tail)->prev;
			(tail)->next = NULL;
			delete cur;
			cout << "Successful!" << endl;
			return true;
		}

	}

	void Print()
	{
		Node_rect* cur = head;
		while (cur) {
			cout << cur->info.data << ' ';
			cur = cur->next;
		}
	}
};

