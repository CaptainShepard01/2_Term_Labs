#define _USE_CRT_NO_SECURE_WARNINGS
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>
//#include "Header.h"
//#include "List.h"

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
			cout << "Number of element: " << cur->info.number << ":\n";
			cout << cur->info.numerator << " / " << cur->info.denominator << endl;
			cur = cur->next;
		}
		return;
	}
};

void ListCreator(int n, NodeList*& Kantor);
void Add(NodeList nodelist);

void Delete();

void Find();

void Summ();


int menu();

int main()
{
	int n = 0;
	cout << "How many elements?\n";
	cin >> n;
	NodeList* Kantor = new NodeList;
	ListCreator(n, Kantor);
	delete Kantor;
	return 0;
	/*bool isRunning = true;
	while (isRunning)
	{
		int answer = 0;
		setlocale(LC_ALL, "Russian");
		answer = menu();
		switch (answer)
		{
		case 0:Find(); break;
		case 1:Delete(); break;
		case 2:Summ(); break;
		case 3:Add(); break;
		case 4:isRunning = false; return 0;
		}

	}*/
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 5) % 5;
		if (key == 0) cout << "-> Find element with a number" << endl;
		else  cout << "   Find element with a number" << endl;
		if (key == 1) cout << "-> Delete element with a number" << endl;
		else  cout << "   Delete element with a number" << endl;
		if (key == 2) cout << "-> Show summ of list's elements" << endl;
		else  cout << "   Show summ of list's elements" << endl;
		if (key == 3) cout << "-> Add element" << endl;
		else  cout << "   Add element" << endl;
		if (key == 4) cout << "-> Exit" << endl;
		else  cout << "   Exit" << endl;
		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}
	} while (code != 13);
	system("cls");
	return key;
}

void ListCreator(int n, NodeList*& Kantor)
{
	int str = 0;
	int stlb = 0, stlbincr = 1;
	bool s = 0;
	int tmp = 0;
	int tmp_str = 0;
	Rational current;
	int current_element = 1;
	for (current_element; current_element <= n;) {
		current.number = current_element;
		current.numerator = stlb;
		current.denominator = str;
		tmp_str = str;
		Kantor->addLast(current);
		while (tmp_str != 0)
		{
			current_element++;
			tmp_str--;
			switch (s) {
			case 0: {
				stlb = stlb - stlbincr;
				stlbincr++;
				s = 1;
				break;
			}
			case 1: {
				stlb = stlb + stlbincr;
				stlbincr++;
				s = 0;
				break;
			}
			}
			current.number = current_element;
			current.numerator = stlb;
			current.denominator = tmp_str;
			Kantor->addLast(current);
		}
		str++;
		current_element++;
	}
	Kantor->Print();
}

void Add(NodeList nodelist)
{
	nodelist.tail;
}

void Delete() {};

void Find() {};

void Summ() {};


