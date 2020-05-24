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

struct Node
{
	char* value = new char[100];
	double data = 0;
	Node* right = nullptr; Node* left = nullptr;
};

struct List {
	Node* head = NULL;
	Node* tail = NULL;

	void addLast(char* value) {
		Node* node = new Node;
		for (int i = 0; i < strlen(value); ++i)
		{
			node->value[i] = value[i];
		}
		node->value[strlen(value)] = '\0';
		node->right = NULL;
		if (head == NULL) {
			tail = node; head = node;
		}
		else {
			node->left = tail;
			tail->right = node;
			tail = node;
		}
	}

	Node* find(char* key)
	{
		Node* cur = head;
		while (cur)
		{
			if (strcmp(cur->value, key) == 0)break;
			cur = cur->right;
		}
		if (cur != NULL) { system("cls"); cout << "Here you are: " << cur->value << '\n'; }
		else cout << "There is no such element in list!" << endl;
		system("pause");
		system("cls");
		return cur;
	}

	bool remove(char* key)
	{
		if (Node* pkey = find(key)) {
			if (pkey == head) {
				head = (head)->right;
				(head)->left = NULL;
			}
			else if (pkey == tail) {
				tail = (tail)->left;
				(tail)->right = NULL;
			}
			else {
				(pkey->left)->right = pkey->right;
				(pkey->right)->left = pkey->left;
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
			tail = (tail)->left;
			(tail)->right = NULL;
			delete cur;
			//cout << "Successful!" << endl;
			return true;
		}

	}
	void Print()
	{
		Node* cur = new Node;
		cur = head;
		while (cur) {
			cout << "Element: " << cur->value << endl;
			cur = cur->right;
		}
		return;
	}
};

struct Stack {
	Node* head = nullptr;
	Node* tail = nullptr;

	Node* peek()
	{
		return tail;
	};

	void push(char* value)
	{
		Node* node = new Node;
		for (int i = 0; i < strlen(value); ++i)
		{
			node->value[i] = value[i];
		}
		node->value[strlen(value)] = '\0';
		if (tail == nullptr) {
			tail = node; head = node;
		}
		else {
			node->left = tail;
			tail->right = node;
			tail = node;
		}
	};

	Node* pop()
	{
		if (tail != nullptr) {
			Node* cur = tail;
			if (tail != head) {
				tail = (tail)->left;
				(tail)->right = nullptr;
			}
			else {
				tail = nullptr; head = nullptr;
			}
			return cur;
		}
	};
};

struct Tree
{
	Node* root = nullptr;

	Node* first(char* value) {
		root = new Node;
		for (int i = 0; i < strlen(value); ++i)
		{
			root->value[i] = value[i];
		}
		root->value[strlen(value)] = '\0';
		root->left = nullptr;
		root->right = nullptr;
		return root;
	}

	void print_tree(Node* p, int level)
	{
		if (p) {
			print_tree(p->left, level + 1);
			for (int i = 0; i < level; ++i)cout << "    ";
			cout << p->value << endl;
			print_tree(p->right, level + 1);
		}
	}
	void printPostorder(Node* node)
	{
		if (node == NULL)
			return;

		// first recur on left subtree 
		printPostorder(node->left);

		// then recur on right subtree 
		printPostorder(node->right);

		// now deal with the node 
		cout << node->value << " ";
	}
	void variable_redefiner(Node* p, char* v, float ins)
	{
		if (p) {
			variable_redefiner(p->left, v, ins);
			if (strcmp(p->value, v) == 0) {
				int ret = snprintf(p->value, sizeof p->value, "%f", ins);
				if (ret < 0) {
					cout << "Something went wrong!\n";
					system("pause");
					return;
				}
				if (ret >= sizeof p->value) {
					//Result was truncated - resize the buffer and retry.
				}
			}
			variable_redefiner(p->right, v, ins);
		}
	}
};



int main()
{
    std::cout << "Hello World!\n";
}
