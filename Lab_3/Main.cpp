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
					cout << setw(4) << cur->info.data;
					cur = cur->next;
				}
				else {
					cout << setw(4) << '0';
				}
			}
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

void main()
{
	bool isRunning = 1;
	int** Matrix_1 = Matrix_creator();
	int** Matrix_2 = Matrix_creator();
	int key = 0;

	Matrix_1 = Read_from_file("matrix_file_1.txt");
	Matrix_2 = Read_from_file("matrix_file_2.txt");
	NodeList* matr_1 = new NodeList;
	NodeList* matr_2 = new NodeList;
	NodeList** matr_sq_1 = new NodeList * [n];
	NodeList** matr_sq_2 = new NodeList * [n];
	NodeList** summ_sq = new NodeList * [n];
	NodeList* summ = new NodeList;

	while (isRunning) {
		key = menu();
		switch (key) {
		case 0: {
			NodeList* matr_1 = Linked_storage(Matrix_1);
			NodeList* matr_2 = Linked_storage(Matrix_2);
			cout << "Linked-storaged matrix from file:\n\n";
			Print_matrix_linked(matr_1);
			cout << endl;
			system("pause");
			break;
		}
		case 1: {
			NodeList** matr_sq_1 = new NodeList * [n];
			matr_sq_1 = Sequential_linked_storage(Matrix_1);
			NodeList** matr_sq_2 = new NodeList * [n];
			matr_sq_2 = Sequential_linked_storage(Matrix_2);
			cout << "Sequential-linked-storaged matrix from file:\n\n";
			Print_matrix_sequential(matr_sq_1);
			cout << endl;
			system("pause");
			break;
		}
		case 2: {
			NodeList* matr_1 = Linked_storage(Matrix_1);
			NodeList* matr_2 = Linked_storage(Matrix_2);
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
			for (int i = 0; i < n; ++i) {
				delete Matrix_1[i], Matrix_2[i], matr_sq_1[i], matr_sq_2[i], summ_sq[i];
			}
			delete matr_1, matr_2, Matrix_1, Matrix_2, matr_sq_1, matr_sq_2, summ_sq;
			isRunning = 0;
		}
		}
	}
	return;
}

int menu() {
	int key = 0;
	int code;
	do {
		system("cls");
		key = (key + 5) % 5;
		if (key == 0) cout << "-> Linked_storage" << endl;
		else  cout << "   Linked_storage" << endl;
		if (key == 1) cout << "-> Sequential_linked_storage" << endl;
		else  cout << "   Sequential_linked_storage" << endl;
		if (key == 2) cout << "-> Summ_2_matrix" << endl;
		else  cout << "   Summ_2_matrix" << endl;
		if (key == 3) cout << "-> Summ_2_matrix_sequential" << endl;
		else  cout << "   Summ_2_matrix_sequential" << endl;
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

// labka9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/*#include <iostream>
#include <fstream>
using namespace std;
struct matrE {
	int x;
	int y;
	double s;
	matrE* next;
};
struct matr {
	matrE* start;
	matrE* end;
};
// posl-zvyaz
struct matrE1 {
	double s;
	int count;
	matrE1* next;
};
struct matr1 {
	matrE1* start;
	matrE1* end;
};
/// posl
matr readM(string filename) { // def
	ifstream f(filename, ios::beg);
	int y;

	matr m; m.start = NULL;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			f >> y;  //cout << y << ' ';

			if (y != 0) {
				if (m.start == NULL) {
					matrE* e = new matrE;
					e->next = NULL;//
					e->x = i;
					e->y = j;
					e->s = y;
					//cout << e->s; system("pause");
					e->next = NULL;
					m.start = e;
					m.end = e;
				}
				else {
					matrE* e = new matrE;
					e->next = NULL;
					e->x = i;
					e->y = j;
					e->s = y;
					e->next = NULL;
					m.end->next = e;
					m.end = e;
				}
			}
		}
	}
	return m;
}
matr1 readM1(string filename) {
	ifstream f(filename);
	int b, p = 0, k = 0; matr1 m; m.start = NULL; m.end = NULL;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			f >> b; //cout << b;
			if (b == p) {
				k++;
			}
			else {
				//	cout << p << ' ' << k;
					//system("pause");
				if (m.start == NULL) {
					matrE1* e = new matrE1;
					e->count = k;
					e->next = NULL;
					e->s = p;
					m.start = e;
					m.end = e;
				}
				else {
					matrE1* e = new matrE1;
					e->count = k;
					e->next = NULL;
					e->s = p;
					m.end->next = e;
					m.end = e;
				}
				k = 1;
				p = b;
			}
		}
	}
	return m;
}
void printM(matr m) {
	matrE* k = m.start;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			if (k != NULL && k->x == i && k->y == j) {
				cout << k->s << ' ';
				k = k->next;
			}
			else {
				//cout << "0 ";
			}
		}
		cout << endl;
	}
}
void printM1(matr1 m) {
	matrE1* k = m.start;
	//int i = 0;
	while (k != NULL) {
		for (int i = 0; i < k->count; i++)
		{
			cout << k->s << ' ';
			i++;
			if (i == 100) {
				i = 0; cout << endl;
			}
		}
		k = k->next;
	}
}
matr addM(matr a, matr b) {
	matr c; c.start = NULL; c.end = NULL;
	//matrE *x = a.start,  *y = b.start, *e=new matrE;
	/*
	while (x != NULL || y != NULL) {
		//cout << 'l';
		if (y==NULL || x->x < y->x ) {
			if (c.start == NULL)
			{
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				x = x->next;
				cout << '1';
			}
			else {
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				x = x->next;
				cout << '1';

			}
		}
		else if (x==NULL || x->x > y->x  ) {
			if (c.start == NULL)
			{
				e->s = y->s;
				e->x = y->x;
				e->y = y->y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				y = y->next;
				cout << '2';

			}
			else {

				e->s = y->s;
				e->x = y->x;
				e->y = y->y;				e->next = NULL;
				c.end->next = e;
				c.end = e;
				y = y->next;
				cout << '2';

			}
		}
		else if (x->y > y->y) {
			if (c.start == NULL)
			{
				e = y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				y = y->next;
				cout << '3';

			}
			else {
				e = y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				y = y->next;
				cout << '3';

			}
		}
		else if (x->y < y->y) {
			if (c.start == NULL)
			{
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.start = e;
				c.end = e;
				x = x->next;
				cout << '4';

			}
			else {
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->next = NULL;
				c.end->next = e;
				c.end = e;
				x = x->next;
				cout << '4';
			}
		}
		else {
			//cout << 'l';
			if (c.start == NULL)
			{
				e->s = x->s;
				e->x = x->x;
				e->y = x->y;
				e->s += y->s;
				//cout << e->s; system("pause");
				e->next = NULL;

				c.start = e;
				c.end = e;
				cout << endl;
				printM(c);
				x = x->next;
				y = y->next;
				//cout << '5';

			}
			else {
				//cout << 'k';
				e->s= x->s;
				e->x = x->x;
				e->y = x->y;
				e->s += y->s;
				e->next = NULL;

				c.end->next = e;
				c.end = e;/// shoto ne tak
				printM(c);
				system("pause");
				x = x->next;
				y = y->next;
				//cout << '6';
				//cout << c.end->s; system("pause");
			}
		}
		*/
		//printM(c); 
			//double m[100][100], /*mm[100][100]*/m1[100][100];

		/*for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++)
				{
					m[i][j] = 0;
					//mm[i][j] = 0;
					m1[i][j] = 0;
				}
			}
			matrE* e = b.start;
			while (e != NULL) {
				m[e->x][e->y] = e->s;
				e = e->next;
			}
			e = a.start;
			while (e != NULL) {
				m1[e->x][e->y] = e->s;
				e = e->next;
			}
			// = new matrE;
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++)
				{
					if (m[i][j] != 0 || m1[i][j] != 0) {
						matrE* k = new matrE;
						k->x = i;
						k->y = j;
						k->s = m[i][j] + m1[i][j];
						k->next = NULL;
						if (c.start == NULL) {
							c.start = k;
							c.end = k;
							//cout << "k";

						}
						else {
							c.end->next = k;
							c.end = k;
						}
						//printM(c); system("pause");

					}
				}
			}
			return c;
		}
		matr multM(matr a, matr b) {
			double m[100][100], mm[100][100], m1[100][100];
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++)
				{
					m[i][j] = 0;
					mm[i][j] = 0;
					m1[i][j] = 0;
				}
			}
			cout << 'k';

			matrE* e = b.start;
			while (e != NULL) {
				m[e->x][e->y] = e->s;
				e = e->next;
			}
			e = a.start;
			while (e != NULL) {
				m1[e->x][e->y] = e->s; e = e->next;
			}
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					for (int g = 0; g < 100; g++) {
						mm[i][j] += m[i][g] * m1[g][j];
					}
				}
			}
			matr mn; mn.start = NULL, mn.end = NULL;
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					for (int g = 0; g < 100; g++) {
						//cin >> y;
						if (m[i][g] != 0 && m1[g][j] != 0)
						{
							mm[i][j] += m[i][g] * m1[g][j];
						}
					}
				}
			}
			for (int i = 0; i < 100; i++) {
				for (int j = 0; j < 100; j++) {
					if (mm[i][j] != 0) cout << mm[i][j] / 2 << ' ';
				}cout << endl;
			}
			return mn;
		}
		*/



