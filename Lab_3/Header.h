#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>
#include "List.h"

using namespace std;
struct Element;
struct Node;
struct NodeList;

int** Matrix_creator(int n);
void Write_in_file(const char* filename, int n);
void Print_normal_matrix(int** matrix, int n);
int** Read_from_file(const char* filename, int n);
NodeList* Linked_storage(int** Matr, int n);
NodeList** Sequential_linked_storage(int** Matr, int n);
void Print_sequential_storage(NodeList** nodelist, int n);
NodeList* Summ_2_matrix(NodeList* first, NodeList* second, int n);
NodeList** Summ_2_matrix_sequential(NodeList** first, NodeList** second, int n);
NodeList** Sequential_linked_storage_reverse(int** Matr, int n);
NodeList** Matr_multiplication(NodeList** first, NodeList** second, int n);
void Print_matrix_linked(NodeList* matrix, int n);
void Print_matrix_sequential(NodeList** matrix, int n);
void Print_matrix_sequential_reverse(NodeList** matrix, int n);