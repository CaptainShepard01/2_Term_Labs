#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "List.h"
#include "Header.h"
//#include "List_rect.h"

using namespace std;

int menu();

int main()
{
	int n = 100;
	int key = 0;
	bool isRunning = 1;
	int** Matrix_1 = Matrix_creator(n);
	int** Matrix_2 = Matrix_creator(n);
	
	Matrix_1 = Read_from_file("matrix_file_1.txt", n);
	Matrix_2 = Read_from_file("matrix_file_2.txt", n);
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
			matr_1 = Linked_storage(Matrix_1, n);
			matr_2 = Linked_storage(Matrix_2, n);
			cout << "Linked-storaged matrix from file:\n\n";
			Print_matrix_linked(matr_1, n);
			cout << endl;
			system("pause");
			break;
		}
		case 1: {
			matr_sq_1 = Sequential_linked_storage(Matrix_1, n);
			matr_sq_2 = Sequential_linked_storage(Matrix_2, n);
			cout << "Sequential-linked-storaged matrix from file:\n\n";
			Print_matrix_sequential(matr_sq_1, n);
			cout << endl;
			system("pause");
			break;
		}
		case 2: {
			matr_1 = Linked_storage(Matrix_1, n);
			matr_2 = Linked_storage(Matrix_2, n);
			summ = Summ_2_matrix(matr_1, matr_2, n);
			cout << "Linked-storaged matrix-summ of two matrixes:\n\n";
			Print_matrix_linked(summ, n);
			cout << endl;
			system("pause");
			break;
		}
		case 3: {
			matr_sq_1 = Sequential_linked_storage(Matrix_1, n);
			matr_sq_2 = Sequential_linked_storage(Matrix_2, n);
			summ_sq = Summ_2_matrix_sequential(matr_sq_1, matr_sq_2, n);
			cout << "Sequential-linked-storaged matrix-summ of two matrixes:\n\n";
			Print_matrix_sequential(summ_sq, n);
			cout << endl;
			system("pause");
			break;
		}
		case 4: {
			matr_sq_1 = Sequential_linked_storage(Matrix_1, n);
			Print_matrix_sequential(matr_sq_1, n);
			cout << '*' << endl;
			matr_sq_2 = Sequential_linked_storage(Matrix_2, n);
			Print_matrix_sequential(matr_sq_2, n);
			matr_sq_2 = Sequential_linked_storage_reverse(Matrix_2, n);
			mult_sq = Matr_multiplication(matr_sq_1, matr_sq_2, n);
			cout << "Matrix-multiplication of two matrixes:\n\n";
			Print_matrix_sequential(mult_sq, n);
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