#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <fstream>
#include <conio.h>

//#include "List.h"
#include "Header.h"
using namespace std;

struct Node
{
	char* value = new char[3];
	Node* right = nullptr; Node* left = nullptr;
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
};

struct Expression
{
	enum OperatorType { PLUS, MINUS, MULTIPL, DIVISION, UNARY_MINUS, SIN, COS, NUMBER } type = NUMBER;
	int value = 0;

	void print()
	{
		switch (type)
		{
		case Expression::PLUS:
			std::cout << "+";
			break;
		case Expression::MINUS:
			std::cout << "-";
			break;
		case Expression::MULTIPL:
			std::cout << "*";
			break;
		case Expression::DIVISION:
			std::cout << "/";
			break;
		case Expression::UNARY_MINUS:
			std::cout << "~";
			break;
		case Expression::SIN:
			std::cout << "sin";
			break;
		case Expression::COS:
			std::cout << "cos";
			break;
		case Expression::NUMBER:
			std::cout << value;
			break;
		default:
			break;
		}
	}
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

char* substringLeft = new char[100];
char* substringRight = new char[100];

Stack* skobki = new Stack;

Node* ExpressionTree(char* c, Stack*& stack)
{
	int cnt = 0;
	int i = 0;
	int iter = 0;
	while (c[i] != '\0') {
		if (c[i] == '(') {
			iter = i;
			cnt++; i++; while (c[i] != '\0') {
				if (c[i] == '(')cnt++;
				if (c[i] == ')')cnt--;
				if (cnt == 0 && i == strlen(c) - 1 && iter == 0) {
					for (int j = 0; j < strlen(c) - 2; ++j)c[j] = c[j + 1];
					c[strlen(c) - 2] = '\0';
					break;
				}
				if (cnt == 0)break;
				if (cnt != 0 && i == strlen(c) - 1) {
					cout << "Wrong string!\n";
					return NULL;
				}
				i++;
			}
			break;
		}
		i++;
	}
	i = 0;
	cnt = 0;
	if (strlen(c) == 1) {
		Node* node = new Node; node->value[0] = c[0]; node->value[1] = '\0'; return node;
	}

	while (c[i] != '\0') {

		if (c[i] == '(') {
			cnt++;
		}
		while (cnt != 0) {
			i++;
			if (c[i] == '(')cnt++;
			if (c[i] == ')')cnt--;
		}
		if (c[i] == '+' || c[i] == '-') {
			Node* node = new Node;
			bool isMinus = 0;
			if (c[i] == '-')isMinus = 1;

			if (isMinus) { node->value[0] = 45; node->value[1] = '\0'; }
			else { node->value[0] = 43; node->value[1] = '\0'; }
			if ((isMinus && i == 0) || (isMinus && !isdigit(c[i - 1]) && !isalpha(c[i - 1]))) {
				int j = 0;
				for (j = i + 1; j < strlen(c); ++j) substringRight[j - (i + 1)] = c[j];
				substringRight[strlen(c) - (i + 1)] = '\0';

				substringRight[strlen(stack->peek()->value)] = '\0';

				node->right = ExpressionTree(substringRight, stack);
				return node;
			}
			else {
				char* temp = new char[20];
				for (int k = 0; k < strlen(c); ++k)temp[k] = c[k]; temp[strlen(c)] = '\0';
				int j = 0;
				for (j = 0; j < i; j++) {
					substringLeft[j] = c[j];
				}
				substringLeft[j] = '\0';

				for (j = i + 1; j < strlen(temp); ++j) substringRight[j - (i + 1)] = c[j];
				substringRight[strlen(temp) - (i + 1)] = '\0';

				stack->push(substringRight);
				node->left = ExpressionTree(substringLeft, stack);

				for (int h = 0; h < strlen(stack->peek()->value); ++h) substringRight[h] = stack->peek()->value[h];
				substringRight[strlen(stack->peek()->value)] = '\0';
				stack->pop();

				node->right = ExpressionTree(substringRight, stack);
				return node;
			}
		}
		i++;
	}

	cnt = 0;
	i = 0;
	while (c[i] != '\0') {
		if (c[i] == '(') {
			cnt++;
		}
		while (cnt != 0) {
			i++;
			if (c[i] == '(')cnt++;
			if (c[i] == ')')cnt--;
		}
		if (c[i] == '*' || c[i] == '/') {
			Node* node = new Node;
			bool isDivide = 0;
			if (c[i] == '/')isDivide = 1;

			if (isDivide) { node->value[0] = 47; node->value[1] = '\0'; }
			else { node->value[0] = 42; node->value[1] = '\0'; }

			int j = 0;
			char* temp = new char[20];
			for (int k = 0; k < strlen(c); ++k)temp[k] = c[k]; temp[strlen(c)] = '\0';
			for (j = 0; j < i; j++) {
				substringLeft[j] = c[j];
			}
			substringLeft[j] = '\0';

			for (j = i + 1; j < strlen(temp); ++j) substringRight[j - (i + 1)] = c[j];
			substringRight[strlen(temp) - (i + 1)] = '\0';

			stack->push(substringRight);
			node->left = ExpressionTree(substringLeft, stack);

			for (int h = 0; h < strlen(stack->peek()->value); ++h) substringRight[h] = stack->peek()->value[h];
			substringRight[strlen(stack->peek()->value)] = '\0';
			stack->pop();

			node->right = ExpressionTree(substringRight, stack);

			return node;
		}
		i++;
	}

	cnt = 0;
	i = 0;
	while (c[i] != '\0') {
		if (c[i] == '(') {
			cnt++;
		}
		while (cnt != 0) {
			i++;
			if (c[i] == '(')cnt++;
			if (c[i] == ')')cnt--;
		}

		if (c[i] == 'c' && c[i + 1] == 'o' && c[i + 2] == 's') {
			int k = i + 3;
			Node* node = new Node;
			node->value[0] = 'c'; node->value[1] = 'o'; node->value[2] = 's';
			for (k; k < strlen(c); ++k)
			{
				substringRight[k - (i + 3)] = c[k];
			}
			substringRight[strlen(c) - (i + 3)] = '\0';
			node->right = ExpressionTree(substringRight, stack);
			return node;
		}
		i++;
	}

	cnt = 0;
	i = 0;
	while (c[i] != '\0') {
		if (c[i] == '(') {
			cnt++;
		}
		while (cnt != 0) {
			i++;
			if (c[i] == '(')cnt++;
			if (c[i] == ')')cnt--;
		}

		if (c[i] == 's' && c[i + 1] == 'i' && c[i + 2] == 'n') {
			int k = i + 3;
			Node* node = new Node;
			node->value[0] = 's'; node->value[1] = 'i'; node->value[2] = 'n';
			for (k; k < strlen(c); ++k)
			{
				substringRight[k - (i + 3)] = c[k];
			}
			substringRight[strlen(c) - (i + 3)] = '\0';
			node->right = ExpressionTree(substringRight, stack);
			return node;
		}
		i++;
	}
}

char* getString()
{
	char* string = new char[100];
	cin.getline(string, 100);
	return string;
}

int main()
{
	//cout << cursubstringLeft << cursubstringRight << substringLeft << substringRight;
	cout << "Expression: ";
	Tree* tree = new Tree;
	Stack* stringstack = new Stack;
	char* expr = getString();
	tree->root = ExpressionTree(expr, stringstack);
	int level = 0;
	tree->printPostorder(tree->root); cout << endl << endl;
	tree->print_tree(tree->root, level);
	delete[] tree, stringstack;
	return 0;
}