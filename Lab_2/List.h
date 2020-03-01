#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "Header.h"


using namespace std;

struct Rational {
	int number = 0, numerator = 0, denominator = 0;
};

struct Node {
	Rational info;
	Node* next;
	Node* prev;
};

struct NodeList {
	Node* head = NULL;
	Node* tail = NULL;

	void addLast(Rational i) {
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
			if (cur->info.number == key)break;
			cur = cur->next;
		}
		if (cur != NULL) { system("cls"); cout << cur->info.numerator << " / " << cur->info.denominator << endl; }
		else cout << "There is no element with this number in list!" << endl;
		return cur;
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
		Node* cur = new Node;
		cur = head;
		while (cur) {
			cout << "Number of element: " << cur->info.number << ": " << cur->info.numerator << " / " << cur->info.denominator << endl;
			cur = cur->next;
		}
		return;
	}
};