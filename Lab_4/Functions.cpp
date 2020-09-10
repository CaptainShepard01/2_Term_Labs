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

char* getString()
{
	char* string = new char[100];
	cin.getline(string, 100);
	return string;
}

char* stringCorrector(char* src)
{
	char* out = new char[100];
	for (int i = 0; i < strlen(src); ++i)out[i] = src[i];

	for (int i = 0; i < strlen(out); ++i) {
		if (out[i] == ' ') {
			for (int j = i; j < strlen(out); ++j) {
				out[j] = out[j + 1];
			}
			out[strlen(out) - 1] = '\0';
		}
		if (!isalpha(out[i]) && !isdigit(out[i]) && out[i] != ' ' && out[i] != '\0' && out[i] != '+' && out[i] != '-' && out[i] != '*' && out[i] != '/') {
			cout << "Wrong string!\n";
			system("pause");
			return NULL;
		}
	}

	return out;
}

double eval(Node* root)
{
	// empty tree  
	if (!root)
		return 0;

	// leaf node i.e, a double  
	/*if (isalpha(root->value[0]) && root->value[1] == '\0') {

	}*/
	if (!root->left && !root->right)
		return (root->data);

	// Evaluate left subtree  
	double l_val = eval(root->left);

	// Evaluate right subtree  
	double r_val = eval(root->right);

	// Check which operator to apply  
	if (root->value[0] == '+')
		return l_val + r_val;

	if (root->value[0] == '-')
		return l_val - r_val;

	if (root->value[0] == '~')
		return -(r_val);

	if (root->value[0] == '*')
		return l_val * r_val;

	if (root->value[0] == '/')
		return l_val / r_val;

	if (root->value[0] == 's')
		return sin(r_val);

	if (root->value[0] == 'c')
		return cos(r_val);
}

bool isSin(char f, char s, char t)
{
	if (f == 's' && s == 'i' && t == 'n')return 1;
	return 0;
}

bool isCos(char f, char s, char t)
{
	if (f == 'c' && s == 'o' && t == 's')return 1;
	return 0;
}

bool variableToFloat(char* v, double& ins, Tree*& tree)
{
	system("cls");
	int i = 0, k = 0;
	char tmp = 'o';
	while (v[i] != '\0') {
		cin.clear();
		if (isSin(v[i], v[i + 1], v[i + 2]) || isCos(v[i], v[i + 1], v[i + 2]))i = i + 3;
		if (isalpha(v[i])) {
			tree->printPostorder(tree->root); cout << endl << endl;
			cout << "Variable: " << v[i] << endl;
			cout << "Enter value: ";
			cin.clear();
			cin >> ins;
			tree->variable_redefiner(tree->root, v[i], ins);
			tmp = v[i];
			k = strlen(v);
			for (int j = 0; j < k; ++j) {
				if (v[j] == tmp) {
					for (int l = 0; l < k; ++l)v[l] = v[l + 1];
					v[k - 1] = '\0';
					k--;
					j = 0;
				}
			}
			system("cls");
		}
		i++;
	}
	system("cls");
	return 0;
}