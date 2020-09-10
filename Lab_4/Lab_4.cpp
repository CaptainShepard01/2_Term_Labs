#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <stack>
#include <fstream>
#include <conio.h>

#include "Structures.h"
#include "Header.h"
using namespace std;

char* substringLeft = new char[100];
char* substringRight = new char[100];

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
		Node* node = new Node; node->value[0] = c[0]; node->value[1] = '\0';
		if (isdigit(c[0]))node->data = atof(c);
		return node;
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
		if (i == 0) {
			if (c[i] == '-') {
				Node* node = new Node;
				node->value[0] = '~'; node->value[1] = '\0';
				for (int j = i + 1; j < strlen(c); ++j) substringRight[j - (i + 1)] = c[j];
				substringRight[strlen(c) - (i + 1)] = '\0';

				node->right = ExpressionTree(substringRight, stack);
				return node;
			}
		}
		if (i != 0) {
			if (c[i] == '-' && c[i - 1] == '(') {
				Node* node = new Node;
				node->value[0] = '~'; node->value[1] = '\0';
				for (int j = i + 1; j < strlen(c); ++j) substringRight[j - (i + 1)] = c[j];
				substringRight[strlen(c) - (i + 1)] = '\0';

				node->right = ExpressionTree(substringRight, stack);
				return node;
			}
			if ((c[i] == '+' || c[i] == '-') && c[i - 1] != '(') {
				Node* node = new Node;
				bool isMinus = 0;
				if (c[i] == '-')isMinus = 1;

				if (isMinus) { node->value[0] = 45; node->value[1] = '\0'; }
				else { node->value[0] = 43; node->value[1] = '\0'; }

				char* temp = new char[20];
				for (int k = 0; k < strlen(c); ++k)temp[k] = c[k]; temp[strlen(c)] = '\0';
				int j = 0;
				for (j = 0; j < i; j++) {
					substringLeft[j] = c[j];
				}
				substringLeft[j] = '\0';

				for (j = i + 1; j < strlen(temp); ++j) substringRight[j - (i + 1)] = temp[j];
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

			for (j = i + 1; j < strlen(temp); ++j) substringRight[j - (i + 1)] = temp[j];
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
			node->isVariable = 0;
			node->isCos = 1;
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
			node->isVariable = 0;
			node->isSin = 1;
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
	for (i; i < strlen(c); ++i) node->value[i] = c[i];
	node->value[strlen(c)] = '\0';
	if (c[0] == '~' || isdigit(c[0])) {
		double ins = 0;
		if (c[0] == '~') {
			c++;
			ins = (-1) * atof(c);
		}
		else ins = atof(c);
		node->data = ins;
		node->isVariable = 0;
	}

	return node;
}

int main()
{
	Tree* tree = new Tree;
	Stack* stringstack = new Stack;
	cout << "Enter expression without spaces and using only floats, variables(1 character each), +, -, *, /, cos and sin!\n";
	cout << "Expression: ";
	char* expr = getString();
	char* temp = new char[100];
	strcpy(temp, expr);
	tree->root = ExpressionTree(expr, stringstack);
	int level = 0;
	tree->printPostorder(tree->root); cout << endl << endl;
	cout << "Tree itself: \n\n";
	tree->print_tree(tree->root, level);
	system("pause");
	double ins = 0;
	variableToFloat(temp, ins, tree);
	tree->printPostorder(tree->root); cout << endl << endl;
	cout << "Result = " << eval(tree->root) << endl;
	delete[] tree, stringstack, expr, temp;
	return 0;
}