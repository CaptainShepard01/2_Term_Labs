#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "List.h"
#include "Header.h"
using namespace std;


int** Matrix_creator(int n)
{
	int** Matrix = new int* [n];
	for (int i = 0; i < n; ++i) {
		Matrix[i] = new int[n];
		for (int j = 0; j < n; ++j) Matrix[i][j] = 0;
	}
	return Matrix;
}

void Write_in_file(const char* filename, int n)
{
	int tmp = 0;
	ofstream matr_file(filename, ios::beg);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			tmp = rand() % 20 - 10;
			matr_file << tmp;
		}
		matr_file << '\n';
	}

	matr_file.close();
}

void Print_normal_matrix(int** matrix, int n)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

int** Read_from_file(const char* filename, int n)
{
	int tmp = 0;
	int** Matrix = new int* [n];
	for (int i = 0; i < n; ++i) {
		Matrix[i] = new int[n];
		for (int j = 0; j < n; ++j) Matrix[i][j] = 0;
	}


	ifstream matr_file(filename, ios::beg);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			matr_file >> Matrix[i][j];
		}
	}

	//Print_normal_matrix(Matrix);

	matr_file.close();
	return Matrix;
}

NodeList* Linked_storage(int** Matr, int n)
{
	Element tmp;
	NodeList* cur = new NodeList;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (Matr[i][j] != 0) {
				tmp.data = Matr[i][j];
				tmp.row = i;
				tmp.column = j;
				cur->addLast(tmp);
			}
		}
	}

	return cur;
}

NodeList** Sequential_linked_storage(int** Matr, int n)
{
	Element tmp;
	NodeList** cur = new NodeList * [n];
	for (int i = 0; i < n; ++i) {
		cur[i] = new NodeList;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (Matr[i][j] != 0) {
				tmp.data = Matr[i][j];
				tmp.column = j;
				tmp.row = i;    //not nessecery, because row is already stored in index massive
				cur[i]->addLast(tmp);
			}
		}
	}

	return cur;
}

void Print_sequential_storage(NodeList** nodelist, int n)
{
	for (int i = 0; i < n; ++i) {
		nodelist[i]->Print();
	}
}

NodeList* Summ_2_matrix(NodeList* first, NodeList* second, int n)
{
	Node* a = new Node, * b = new Node, * c = new Node, * p = new Node;
	NodeList* cur = new NodeList;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			a = first->head;
			b = second->head;
			c = new Node;
			cur->head = c;
			p = cur->head;
			while (a && b) {
				if (a->info.row == b->info.row && a->info.column == b->info.column) {
					c->info.column = a->info.column;
					c->info.row = a->info.row;
					c->info.data = a->info.data + b->info.data;
					a = a->next;
					b = b->next;
				}
				else if (a->info.row == b->info.row && a->info.column < b->info.column) {
					c->info.column = a->info.column;
					c->info.row = a->info.row;
					c->info.data = a->info.data;
					a = a->next;
				}
				else if (a->info.row == b->info.row && a->info.column > b->info.column) {
					c->info.column = b->info.column;
					c->info.row = b->info.row;
					c->info.data = b->info.data;
					b = b->next;
				}
				else if (a->info.row < b->info.row) {
					c->info.column = a->info.column;
					c->info.row = a->info.row;
					c->info.data = a->info.data;
					a = a->next;
				}
				else if (a->info.row > b->info.row) {
					c->info.column = b->info.column;
					c->info.row = b->info.row;
					c->info.data = b->info.data;
					b = b->next;
				}
				if (c->info.data) {
					p = c;
					c = new Node;
					p->next = c;
				}
			}
			if (b)a = b;
			while (a) {
				c->info.column = a->info.column;
				c->info.row = a->info.row;
				c->info.data = a->info.data;
				a = a->next;
				p = c;
				c = new Node;
				p->next = c;
			}
			if (c == cur->head)cur->head = NULL;
			else p->next = NULL;
			delete c;
		}
	}
	delete a, b, c, p;
	return cur;
}

NodeList** Summ_2_matrix_sequential(NodeList** first, NodeList** second, int n)
{
	Node* a = new Node, * b = new Node, * c = new Node, * p = new Node;
	NodeList** cur = new NodeList * [n];
	for (int i = 0; i < n; ++i) {
		cur[i] = new NodeList;
	}
	for (int i = 0; i < n; ++i) {
		a = first[i]->head; b = second[i]->head;
		c = new Node; cur[i]->head = c;
		p = cur[i]->head;
		while (a && b) {
			if (a->info.column == b->info.column) {
				c->info.column = a->info.column;
				c->info.data = a->info.data + b->info.data;
				a = a->next;
				b = b->next;
			}
			else if (a->info.column < b->info.column) {
				c->info.column = a->info.column;
				c->info.data = a->info.data;
				a = a->next;
			}
			else {
				c->info.column = b->info.column;
				c->info.data = b->info.data;
				b = b->next;
			}
			if (c->info.data) {
				p = c; c = new Node; p->next = c;
			}
		}
		if (b)a = b;
		while (a) {
			c->info.column = a->info.column;
			c->info.data = a->info.data;
			a = a->next;
			p = c; c = new Node; p->next = c;
		}
		if (c == cur[i]->head)cur[i]->head = NULL;
		else p->next = NULL;
		delete c;
	}
	delete a, b, c, p;
	return cur;
}

NodeList** Sequential_linked_storage_reverse(int** Matr, int n)
{
	Element tmp;
	NodeList** cur = new NodeList * [n];
	for (int i = 0; i < n; ++i) {
		cur[i] = new NodeList;
	}

	for (int j = 0; j < n; ++j) {
		for (int i = 0; i < n; ++i) {
			if (Matr[i][j] != 0) {
				tmp.data = Matr[i][j];
				tmp.column = j;
				tmp.row = i;
				cur[j]->addLast(tmp);
			}
		}
	}

	return cur;
}

NodeList** Matr_multiplication(NodeList** first, NodeList** second, int n)
{
	Element tmp;
	Node* horizontal = new Node, * vertical = new Node;
	NodeList** cur = new NodeList * [n];
	for (int i = 0; i < n; ++i) {
		cur[i] = new NodeList;
	}

	for (int i = 0; i < n; ++i) {
		tmp.data = 0;
		for (int j = 0; j < n; ++j) {
			horizontal = first[i]->head;
			vertical = second[j]->head;
			while (horizontal && vertical) {
				if (horizontal->info.column == vertical->info.row) {
					tmp.column = j;
					tmp.row = i;
					tmp.data = tmp.data + (horizontal->info.data) * (vertical->info.data);
					horizontal = horizontal->next;
					vertical = vertical->next;
				}
				else if (horizontal->info.column < vertical->info.row) {
					horizontal = horizontal->next;
				}
				else {
					vertical = vertical->next;
				}
			}
			if (tmp.data != 0) {
				cur[i]->addLast(tmp);
				tmp.data = 0;
			}
		}
	}

	delete horizontal, vertical;
	return cur;
}

void Print_matrix_linked(NodeList* matrix, int n)
{
	if (matrix->head != NULL) {
		Node* cur = new Node;
		cur = matrix->head;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (cur != NULL && cur->info.row == i && cur->info.column == j) {
					cout << setw(4) << cur->info.data;
					cur = cur->next;
				}
				else {
					cout << setw(4) << '0';
				}
			}
			cout << endl;
		}
		delete cur;
		return;
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(4) << '0';
			}
			cout << endl;
		}
		return;
	}
}

void Print_matrix_sequential(NodeList** matrix, int n)
{
	if (matrix[0]->head != NULL) {
		Node* cur = new Node;
		for (int i = 0; i < n; ++i) {
			cur = matrix[i]->head;
			for (int j = 0; j < n; ++j) {
				if (cur != NULL && cur->info.column == j) {
					cout << setw(5) << cur->info.data;
					cur = cur->next;
				}
				else {
					cout << setw(5) << '0';
				}
			}
			cout << endl;
		}
		delete cur;
		return;
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(4) << '0';
			}
			cout << endl;
		}
		return;
	}

}

void Print_matrix_sequential_reverse(NodeList** matrix, int n)
{
	if (matrix[0]->head != NULL) {
		Node* cur = new Node;
		for (int j = 0; j < n; ++j) {
			cur = matrix[j]->head;
			for (int i = 0; i < n; ++i) {
				if (cur != NULL && cur->info.row == i) {
					cout << setw(5) << cur->info.data;
					cur = cur->next;
				}
				else {
					cout << setw(5) << '0';
				}
			}
			cout << endl;
		}
		delete cur;
		return;
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cout << setw(4) << '0';
			}
			cout << endl;
		}
		return;
	}

}