#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "List.h"
//#include "List_rect.h"

using namespace std;
const int n = 100;

int** Matrix_creator()
{
	int** Matrix = new int* [n];
	for (int i = 0; i < n; ++i) {
		Matrix[i] = new int[n];
		for (int j = 0; j < n; ++j) Matrix[i][j] = 0;
	}
	return Matrix;
}

void Write_in_file(const char* filename)
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

void Print_normal_matrix(int** matrix)
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

int** Read_from_file(const char* filename)
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

NodeList* Linked_storage(int** Matr)
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

NodeList** Sequential_linked_storage(int** Matr)
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

void Print_sequential_storage(NodeList** nodelist)
{
	for (int i = 0; i < n; ++i) {
		nodelist[i]->Print();
	}
}

NodeList* Summ_2_matrix(NodeList* first, NodeList* second)
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

NodeList** Summ_2_matrix_sequential(NodeList** first, NodeList** second)
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

NodeList** Sequential_linked_storage_reverse(int** Matr)
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

NodeList** Matr_multiplication(NodeList** first, NodeList** second)
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

void Print_matrix_linked(NodeList* matrix)
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
		cout << "You haven't created linked-storaged matrix yet!\n";
		return;
	}
}

void Print_matrix_sequential(NodeList** matrix)
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
		cout << "You haven't created linked-sequential-storaged matrix yet!\n";
		return;
	}

}

void Print_matrix_sequential_reverse(NodeList** matrix)
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
		cout << "You haven't created linked-sequential-storaged matrix yet!\n";
		return;
	}

}

int menu();

int main()
{
	bool isRunning = 1;
	int** Matrix_1 = Matrix_creator();
	int** Matrix_2 = Matrix_creator();
	int key = 0;

	Matrix_1 = Read_from_file("matrix_file_1.txt");
	Matrix_2 = Read_from_file("matrix_file_2.txt");
	/*Print_normal_matrix(Matrix_2);
	system("pause");*/
	NodeList* matr_1 = new NodeList;
	NodeList* matr_2 = new NodeList;
	NodeList** matr_sq_1 = new NodeList * [n];
	NodeList** matr_sq_2 = new NodeList * [n];
	NodeList** summ_sq = new NodeList * [n];
	NodeList** mult_sq = new NodeList * [n];
	NodeList* summ = new NodeList;

	while (isRunning) {
		key = menu();
		switch (key) {
		case 0: {
			matr_1 = Linked_storage(Matrix_1);
			matr_2 = Linked_storage(Matrix_2);
			cout << "Linked-storaged matrix from file:\n\n";
			Print_matrix_linked(matr_1);
			cout << endl;
			system("pause");
			break;
		}
		case 1: {
			matr_sq_1 = Sequential_linked_storage(Matrix_1);
			matr_sq_2 = Sequential_linked_storage(Matrix_2);
			cout << "Sequential-linked-storaged matrix from file:\n\n";
			Print_matrix_sequential(matr_sq_1);
			cout << endl;
			system("pause");
			break;
		}
		case 2: {
			matr_1 = Linked_storage(Matrix_1);
			matr_2 = Linked_storage(Matrix_2);
			summ = Summ_2_matrix(matr_1, matr_2);
			cout << "Linked-storaged matrix-summ of two matrixes:\n\n";
			Print_matrix_linked(summ);
			cout << endl;
			system("pause");
			break;
		}
		case 3: {
			matr_sq_1 = Sequential_linked_storage(Matrix_1);
			matr_sq_2 = Sequential_linked_storage(Matrix_2);
			summ_sq = Summ_2_matrix_sequential(matr_sq_1, matr_sq_2);
			cout << "Sequential-linked-storaged matrix-summ of two matrixes:\n\n";
			Print_matrix_sequential(summ_sq);
			cout << endl;
			system("pause");
			break;
		}
		case 4: {
			matr_sq_1 = Sequential_linked_storage(Matrix_1);
			Print_matrix_sequential(matr_sq_1);
			cout << '*' << endl;
			matr_sq_2 = Sequential_linked_storage(Matrix_2);
			Print_matrix_sequential(matr_sq_2);
			matr_sq_2 = Sequential_linked_storage_reverse(Matrix_2);		
			mult_sq = Matr_multiplication(matr_sq_1, matr_sq_2);
			cout << "Matrix-multiplication of two matrixes:\n\n";
			Print_matrix_sequential(mult_sq);
			cout << endl;
			system("pause");
			break;
		}
		case 5: {
			for (int i = 0; i < n; ++i) {
				delete Matrix_1[i], Matrix_2[i], matr_sq_1[i], matr_sq_2[i], summ_sq[i], mult_sq[i];
			}
			delete matr_1, matr_2, Matrix_1, Matrix_2, matr_sq_1, matr_sq_2, summ_sq, mult_sq;
			isRunning = 0;
		}
		}
	}
	return 0;
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 6) % 6;
		if (key == 0) cout << "-> Linked_storage" << endl;
		else  cout << "   Linked_storage" << endl;
		if (key == 1) cout << "-> Sequential_linked_storage" << endl;
		else  cout << "   Sequential_linked_storage" << endl;
		if (key == 2) cout << "-> Summ_2_matrix" << endl;
		else  cout << "   Summ_2_matrix" << endl;
		if (key == 3) cout << "-> Summ_2_matrix_sequential" << endl;
		else  cout << "   Summ_2_matrix_sequential" << endl;
		if (key == 4) cout << "-> Multiplication of two matrixes" << endl;
		else  cout << "   Multiplication of two matrixes" << endl;
		if (key == 5) cout << "-> Exit" << endl;
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