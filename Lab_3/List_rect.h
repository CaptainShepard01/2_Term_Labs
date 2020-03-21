#pragma once
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <conio.h>


using namespace std;

struct Element_rect {
	int data = 0, row = 0, column = 0;
};

struct Node_rect {
	Element_rect info;
	Node_rect* next_right = NULL;
	Node_rect* next_down = NULL;
};

struct NodeList_rect {
	Node_rect* head_up= NULL;
	Node_rect* head_left = NULL;

	void addLast_right(Element_rect i) {
		Node_rect* node = new Node_rect;
		if (head_up == NULL) {
			node->info = i;
			node->next_right = NULL;
			node->next_down = NULL;
			head_left = node; 
			head_up = node;
		}
		if (head_left == NULL) {
			node->info = i;
			node->next_right = NULL;
			node->next_down = NULL;
			head_left = node;
		}
		else {
			node = head_left;
			while (node->next_right != NULL) {
				node = node->next_right;
			}
			node->info = i;
			node->next_right = NULL;
			node->next_down = NULL;
		}
	}

	void addLast_down(Element_rect i) {
		Node_rect* node = new Node_rect;
		node->info = i;
		node->next_right = NULL;
		node->next_down = NULL;
		if (head_up == NULL) {
			head_left = node;
			head_up = node;
		}
		if (head_left == NULL) {
			head_left = node;
		}
		else {
			head_left->next_down = node;
		}
	}

	void Print()
	{
		Node_rect* cur = head;
		while (cur) {
			cout << cur->info.data << ' ';
			cur = cur->next;
		}
	}
};

