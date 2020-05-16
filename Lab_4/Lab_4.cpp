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

char* substringLeft = new char[100];
char* substringRight = new char[100];

struct Node
{
	char* value = new char[10];
	double data = 0;
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
	void PostorderString(Node* node, int& i, char* str)
	{
		if (node == NULL)return;

		PostorderString(node->left, i, str);
		PostorderString(node->right, i, str);
		for (int j = 0; j < strlen(node->value); ++j) { str[i] = node->value[j]; i++; }
		str[i] = ' ';
		str[i + 1] = '\0';
		i++;

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

bool isFloat(char* v, double& ins)
{
	int i = 0;
	char* c = new char[strlen(v)];
	for (i; i < strlen(v); ++i)c[i] = v[i];
	i = 0;
	bool isMinus = 0;
	if (v[0] == '~') {
		isMinus = 1;
		for (i + 1; i < strlen(v); ++i)c[i - 1] = v[i];
		c[strlen(v) - 1] = '\0';
	}
	i = 0;
	for (i; i < strlen(v); ++i) {
		if ((c[i] < '0' || c[i]>'9') && c[i] != '.')return false;
	}
	ins = strtod(c, NULL);
	delete[] c;
	if (isMinus)ins = ins * (-1);
	return true;
}

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
			if ((isMinus && i == 0) || (isMinus && !isdigit(c[i - 1]) && !isalpha(c[i - 1]))) c[i] = '~';

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
			node->value[0] = 'c'; node->value[1] = 'o'; node->value[2] = 's'; node->value[3] = '\0';
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
			node->value[0] = 's'; node->value[1] = 'i'; node->value[2] = 'n'; node->value[3] = '\0';
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

	Node* node = new Node;
	i = 0;
	if (c[0] == '~' || isdigit(c[0])) {
		double ins = 0;
		isFloat(c, ins);
		node->data = ins;
	}
	for (i; i < strlen(c); ++i) node->value[i] = c[i];
	node->value[strlen(c)] = '\0';

	return node;
}

char* getString()
{
	char* string = new char[100];
	cin.getline(string, 100);
	return string;
}

void variableToDouble(char*& v, double& ins, Tree* tree)
{
	system("cls");
	cin.clear();
	cout << "Which variable vould you like to insert float into?\n";
	cin.getline(v, 10);
	cout << "Ok, now, with what float?\n";
	cin >> ins;
	tree->variable_redefiner(tree->root, v, ins);
	tree->printPostorder(tree->root); cout << endl << endl;
	int level = 0;
	tree->print_tree(tree->root, level);
	system("pause");
}

double Result(Tree* tree)
{
	Stack* exprstk = new Stack;
	double res = 0;
	int i = 0;
	char* string = new char[100]; tree->PostorderString(tree->root, i, string);
	//cout << strlen(string) << endl;
	//cout << string;
	int doublecounter = 0;
	exprstk->push();   //TODO
	while()
	delete exprstk, string;
	return res;
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
	tree->printPostorder(tree->root); cout << endl;
	cout << "Tree itself: \n\n";
	tree->print_tree(tree->root, level);
	system("pause");
	tree->printPostorder(tree->root); cout << endl << endl;
	char* v = new char[10];
	double ins = 0;
	Result(tree);
	//variableToDouble(v, ins, tree);

	delete[] tree, stringstack, expr, v;
	return 0;
}